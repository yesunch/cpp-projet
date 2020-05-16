//
// Created by quentin on 13/05/2020.
//

#include "Bestiole.h"
#include "Espece.h"
#include "GenerateurAleatoire.h"
#include "Util.h"
#include "Yeux.h"

#include <cmath>

#include <SFML/Graphics.hpp>

Bestiole::Bestiole(Bestiole::Id id, Espece espece, Comportement::Ptr comp)
  : id{ id }
  , espece{ std::move(espece) }
  , comportement{ std::move(comp) }
  , ellipse{ Bestiole::NB_POINTS }
  , dureeDeVie{ espece.dureeDeVie }
{
    buildEllipse();

    auto color = sf::Color::Black;

    if (comportement)
    {
        color = comportement->getColor();
    }

    ellipse.setFillColor(color);

    /*
    if (this->espece.dissimulation)
    {
        auto color = ellipse.getFillColor();
        color.a = 255 - 255.0f * this->espece.dissimulation->getCoeffDissimulation();
        ellipse.setFillColor(color);
    }
     */
}

void
Bestiole::buildEllipse()
{
    auto const nbPoints = ellipse.getPointCount();
    auto const angleStep = 2.0f * M_PI / nbPoints;

    for (size_t i = 0; i < nbPoints; ++i)
    {
        auto point = Util::unit(i * angleStep);
        point.x *= 0.5f * espece.longueur;
        point.y *= 0.5f * espece.epaisseur;

        ellipse.setPoint(i, point);
    }
}

void
Bestiole::update(std::vector<ObservationBestiole> const& bestiolesObservees,
                 sf::FloatRect bordsMilieu,
                 const std::function<void()>& seCloner,
                 const std::function<void()>& mourrir,
                 sf::Time timeStep)
{
    auto deltaPos = getVelocity() * timeStep.asSeconds();
    ellipse.move(deltaPos);

    if (comportement)
    {
        comportement->update(bestiolesObservees, *this, timeStep);
        ellipse.setFillColor(comportement->getColor());
    }

    ellipse.move(deltaPos);

    if (dureeDeVie > sf::Time::Zero)
    {
        dureeDeVie -= timeStep;
        if (roundf(dureeDeVie.asSeconds()) != roundf((dureeDeVie + timeStep).asSeconds()))
        {
            auto& genAlea = GenerateurAleatoire::getSingleton();
            if (genAlea.uniformReal(0.0f, 1.0f) < Bestiole::PROBABILITE_CLONAGE)
            {
                seCloner();
            }
        }
    }
    else
    {
        mourrir();
    }
}

void
Bestiole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (espece.capteur)
    {
        target.draw(*espece.capteur, states);
    }

    sf::Transformable accessoireTransform;
    accessoireTransform.setPosition(getPosition());
    accessoireTransform.rotate(getRotation() * 180.0f * M_1_PI);
    accessoireTransform.scale(0.015f * espece.longueur, 0.03f * espece.epaisseur);

    if (espece.dissimulation)
    {
        auto ellipseDissimulation = ellipse;
        ellipseDissimulation.scale(1.25f, 1.25f);
        ellipseDissimulation.setFillColor(sf::Color::Transparent);
        ellipseDissimulation.setOutlineThickness(0.1f * espece.epaisseur);
        ellipseDissimulation.setOutlineColor({ 0, 0, 0, 50 });
        target.draw(ellipseDissimulation, states);
    }

    target.draw(ellipse, states);

    if (espece.locomotion)
    {
        target.draw(*espece.locomotion, states.transform * accessoireTransform.getTransform());
    }

    if (espece.protection)
    {
        target.draw(*espece.protection, states.transform * accessoireTransform.getTransform());
    }
}

bool
Bestiole::contains(sf::Vector2f point0) const
{
    auto const ellipseTransform = ellipse.getTransform();
    auto const nbPoints = ellipse.getPointCount();
    for (int i = 0; i < static_cast<int>(nbPoints) - 1; ++i)
    {
        auto const point1 = ellipseTransform.transformPoint(ellipse.getPoint(i));
        auto const point2 = ellipseTransform.transformPoint(ellipse.getPoint(i + 1));

        auto const vec1 = point1 - point0;
        auto const vec2 = point2 - point0;
        auto const det = Util::det(vec1, vec2);

        if (det < 0)
        {
            return false;
        }
    }

    return true;
}

Collision
Bestiole::testCollision(sf::ConvexShape const& shape) const
{
    auto const bords = this->ellipse.getGlobalBounds();
    auto const ellipseNbPoints = shape.getPointCount();
    for (int i = 0; i < static_cast<int>(ellipseNbPoints); ++i)
    {
        auto const shapeTransform = shape.getTransform();
        auto const pointShape = shapeTransform.transformPoint(shape.getPoint(i));
        if (bords.contains(pointShape) && this->contains(pointShape))
        {
            Collision collision{ true };
            collision.position = pointShape;

            auto previousPointIndex = i - 1;
            if (previousPointIndex < 0)
            {
                previousPointIndex = ellipseNbPoints - 1;
            }

            auto nextPointIndex = i + 1;
            if (static_cast<int>(ellipseNbPoints) - 1 < nextPointIndex)
            {
                nextPointIndex = 0;
            }

            auto const previousPoint =
                shapeTransform.transformPoint(shape.getPoint(previousPointIndex));
            auto const nextPoint = shapeTransform.transformPoint(shape.getPoint(nextPointIndex));
            auto const tangente = Util::normalize(nextPoint - previousPoint);

            collision.normale = { tangente.y, -tangente.x };
            return collision;
        }
    }

    return Collision{ false };
}

ObservationBestiole
Bestiole::etreObservee(float distanceObserveur, float angleObserveur) const
{
    auto coeffDissimulation = 0.0f;
    if (espece.dissimulation)
    {
        coeffDissimulation = espece.dissimulation->getCoeffDissimulation();
    }

    return { distanceObserveur, angleObserveur, coeffDissimulation, ellipse, getVelocity() };
}

sf::Vector2f
Bestiole::getPosition() const
{
    return ellipse.getPosition();
}

BestioleId
Bestiole::getId() const
{
    return id;
}

float
Bestiole::getVitesse() const
{
    auto vitesse = Bestiole::VITESSE_DE_BASE;

    auto const& locomotion = espece.locomotion;
    if (locomotion)
    {
        vitesse *= locomotion->getFacteurVitesse();
    }

    auto const& protection = espece.protection;
    if (protection)
    {
        vitesse /= protection->getFacteurVitesse();
    }

    return vitesse;
}

float
Bestiole::getRotation() const
{
    return ellipse.getRotation() * M_PI / 180.0f;
}

sf::Vector2f
Bestiole::getVelocity() const
{
    auto const vitesse = getVitesse();
    auto const rotation = getRotation();
    auto const velocity = vitesse * Util::unit(rotation);
    return velocity;
}

sf::ConvexShape const&
Bestiole::getShape() const
{
    return ellipse;
}

Capteur::Ptr const&
Bestiole::getCapteur() const
{
    return espece.capteur;
}

float
Bestiole::getCoeffResistance() const
{
    auto resistance = 1.0f;
    if (espece.protection)
    {
        resistance = espece.protection->getCoeffResistance();
    }

    return resistance;
}

Espece
Bestiole::clonerEspece() const
{
    return espece.cloner();
}

Comportement::Ptr
Bestiole::clonerComportement() const
{
    return comportement->cloner();
}

void
Bestiole::setPosition(sf::Vector2f position)
{
    ellipse.setPosition(position);
}

sf::Vector2f
Bestiole::getOrientation() const
{
    auto const angle = getRotation();
    return Util::unit(angle);
}

void
Bestiole::setRotation(float angle)
{
    ellipse.setRotation(angle * 180.0f * M_1_PI);
}

void
Bestiole::setOrientation(sf::Vector2f orientation)
{
    setRotation(Util::angle(orientation));
}

void
Bestiole::rotate(float angle)
{
    setRotation(getRotation() + angle);
}
