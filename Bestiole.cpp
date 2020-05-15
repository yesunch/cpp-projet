//
// Created by quentin on 13/05/2020.
//

#include "Bestiole.h"
#include "Espece.h"
#include "GenerateurAleatoire.h"
#include "Oreilles.h"
#include "OreillesEtYeux.h"
#include "Util.h"
#include "Yeux.h"

#include <cmath>

#include <SFML/Graphics.hpp>

Bestiole::Bestiole(Bestiole::Id id, Espece espece, Comportement::Ptr comp)
  : id{ id }
  , espece{ std::move(espece) }
  , comportement{ std::move(comp) }
  , ellipse{ Bestiole::NB_POINTS }
  , length{ Bestiole::LENGTH }
  , thickness{ 0.5f * Bestiole::LENGTH }
  , etourdissement{}
{
    buildEllipse();

    if (comportement)
    {
        ellipse.setFillColor(comportement->getColor());
    }

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

    for (int i = 0; i < nbPoints; ++i)
    {
        auto point = Util::unit(i * angleStep);
        point.x *= 0.5f * length;
        point.y *= 0.5f * thickness;

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
    auto newRotation = getRotation();

    ellipse.move(deltaPos);

    if (comportement)
    {
        newRotation = comportement->updateRotation(bestiolesObservees, getRotation(), timeStep);
    }

    ellipse.move(deltaPos);
    setRotation(newRotation);
}

void
Bestiole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    /*
    auto const oreilles = dynamic_cast<Oreilles*>(espece.capteur.get());
    if (oreilles)
    {
        auto const delta = oreilles->getDelta();
        auto const gamma = oreilles->getGamma();

        sf::CircleShape oreilleRayon{ delta, 15 };
        oreilleRayon.setOrigin(delta, delta);
        oreilleRayon.setPosition(getPosition());
        oreilleRayon.setFillColor({ 255, 0, 0, static_cast<sf::Uint8>(255.0f * gamma) });

        target.draw(oreilleRayon);
    }

    auto const yeux = dynamic_cast<Yeux*>(espece.capteur.get());
    if (yeux)
    {
        auto const position = getPosition();
        auto const rotation = getRotation();
        auto const alpha = yeux->getAlpha();
        auto const delta = yeux->getDelta();
        auto const gamma = yeux->getGamma();

        sf::VertexArray vertexArray{ sf::TriangleFan, 15 };
        vertexArray[0].position = getPosition();
        vertexArray[0].color = { 255, 0, 0, static_cast<sf::Uint8>(255.0f * gamma) };
        for (int i = 1; i < 15; ++i)
        {
            vertexArray[i].position =
                position + delta * Util::unit(rotation - 0.5f * alpha + (i - 1) / 14.0f * alpha);
            vertexArray[i].color = { 255, 0, 0, static_cast<sf::Uint8>(255.0f * gamma) };
        }

        target.draw(vertexArray);
    }

    auto const oreillesEtYeux = dynamic_cast<OreillesEtYeux*>(espece.capteur.get());
    if (oreillesEtYeux)
    {
        auto const deltaO = oreillesEtYeux->getDeltaO();
        auto const gammaO = oreillesEtYeux->getGammaO();

        sf::CircleShape oreilleRayon{ deltaO, 15 };
        oreilleRayon.setOrigin(deltaO, deltaO);
        oreilleRayon.setPosition(getPosition());
        oreilleRayon.setFillColor({ 255, 0, 0, static_cast<sf::Uint8>(255.0f * gammaO) });
        target.draw(oreilleRayon);

        auto const position = getPosition();
        auto const rotation = getRotation();
        auto const alpha = oreillesEtYeux->getAlpha();
        auto const deltaY = oreillesEtYeux->getDeltaY();
        auto const gammaY = oreillesEtYeux->getGammaY();

        sf::VertexArray vertexArray{ sf::TriangleFan, 15 };
        vertexArray[0].position = getPosition();
        vertexArray[0].color = { 255, 0, 0, static_cast<sf::Uint8>(255.0f * gammaY) };
        for (int i = 1; i < 15; ++i)
        {
            vertexArray[i].position =
                position + deltaY * Util::unit(rotation - 0.5f * alpha + (i - 1) / 14.0f * alpha);
            vertexArray[i].color = { 255, 0, 0, static_cast<sf::Uint8>(255.0f * gammaY) };
        }

        target.draw(vertexArray);
    }
*/
    target.draw(ellipse, states);
}

bool
Bestiole::contains(sf::Vector2f point0) const
{
    auto const ellipseTransform = ellipse.getTransform();
    auto const nbPoints = ellipse.getPointCount();
    for (int i = 0; i < nbPoints - 1; ++i)
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
    for (int i = 0; i < ellipseNbPoints; ++i)
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
            if (ellipseNbPoints - 1 < nextPointIndex)
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
Bestiole::creerObservation(float distanceObserveur) const
{
    auto coeffDissimulation = 0.0f;
    if (espece.dissimulation)
    {
        coeffDissimulation = espece.dissimulation->getCoeffDissimulation();
    }

    return { distanceObserveur, coeffDissimulation, ellipse, getOrientation() };
}

sf::Vector2f
Bestiole::getPosition() const
{
    return ellipse.getPosition();
}

float
Bestiole::getVitesse() const
{
    auto vitesse = Bestiole::BASE_SPEED;

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
Bestiole::etourdirPendant(sf::Time time)
{
    etourdissement = std::max(time, etourdissement);
}
