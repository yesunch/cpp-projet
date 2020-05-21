//
// Created by quentin on 13/05/2020.
//

#include "../include/Bestiole.h"
#include "../include/Espece.h"
#include "../include/GenerateurAleatoire.h"
#include "../include/Util.h"
#include "../include/capteur/Yeux.h"

#include <cmath>

#include <SFML/Graphics.hpp>

/**
 * Create a bestiole with certain bestiole id, espece, and behavior. Set the bestiole color
 * according to the behavior color.
 * @param id
 * @param espece
 * @param comp
 */
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

/**
 * Move the bestiole forward, invoke its comportement if there's one, and check if the bestiole is
 * still alive. If it's alive, calculate a random float and compare if with the clone probability.
 * Clone it by the lambda funtion seCloner() if necessary If it's not alive, do the lambda function
 * mourir().
 * @param bestiolesObservees
 * @param bordsMilieu
 * @param seCloner
 * @param mourrir
 * @param timeStep
 */
void
Bestiole::update(std::vector<ObservationBestiole> const& bestiolesObservees,
                 sf::FloatRect bordsMilieu,
                 const std::function<void()>& seCloner,
                 const std::function<void()>& mourrir,
                 sf::Time timeStep)
{
    if (comportement)
    {
        comportement->update(bestiolesObservees, *this, timeStep);
        ellipse.setFillColor(comportement->getColor());
    }

    auto deltaPos = getVelocity() * timeStep.asSeconds();
    ellipse.move(deltaPos);

    if (dureeDeVie > sf::Time::Zero)
    {
        dureeDeVie -= timeStep;
        if (roundf(dureeDeVie.asSeconds()) != roundf((dureeDeVie + timeStep).asSeconds()))
        {
            auto& genAlea = GenerateurAleatoire::getSingleton();
            // Get a random float between 0 and 1 and compare it with the clonage probability
            if (genAlea.uniformReal(0.0f, 1.0f) < Bestiole::PROBABILITE_CLONAGE)
            {
                // Add its id into the vector<BestioleId> bestiolesClonees
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

float
Bestiole::testOverlap(sf::Vector2f point0) const
{
    auto untransformedPos = getShape().getInverseTransform().transformPoint(point0);
    auto const realAngle = Util::angle(untransformedPos);
    auto const realLength = Util::magnitude(untransformedPos);
    auto const expectedLength = Util::magnitude(
        { 0.5f * espece.longueur * cosf(realAngle), 0.5f * espece.epaisseur * sinf(realAngle) });
    auto const result = std::max(0.0f, expectedLength - realLength);

    return result;
}

/**
 * Check if this bestiole is hit by a certain bestiole represented by its shape. If there's a
 * collision, return an object of Collision with the normal vector which indicates the direction
 * that would separate two bestioles. The normal vector is orthogonal with the vector formed with
 * the previousPoint and nextPoint of the overlapped point.
 * @param shape
 * @return collision
 */
Collision
Bestiole::testCollision(sf::ConvexShape const& shape) const
{
    auto const bords = this->ellipse.getGlobalBounds();
    auto const shapeBords = shape.getGlobalBounds();
    if (!bords.intersects(shapeBords))
    {
        return Collision{ false };
    }

    auto const ellipseNbPoints = shape.getPointCount();
    for (int i = 0; i < static_cast<int>(ellipseNbPoints); ++i)
    {
        auto const shapeTransform = shape.getTransform();
        auto const pointShape = shapeTransform.transformPoint(shape.getPoint(i));
        if (!bords.contains(pointShape))
        {
            continue;
        }

        if (auto overlap = this->testOverlap(pointShape))
        {
            Collision collision{ true };
            collision.overlap = overlap;

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

/**
 * Create an object of ObservationBestiole with relative distance and angle to the observer.
 * @param distanceObserveur
 * @param angleObserveur
 * @return
 */
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
/**
 * Get the current position of the bestiole
 * @return
 */
sf::Vector2f
Bestiole::getPosition() const
{
    return ellipse.getPosition();
}

/**
 * Get the current id of the bestiole
 * @return
 */
BestioleId
Bestiole::getId() const
{
    return id;
}
/**
 * Get the speed of the bestiole considering the locomotion and protection
 * @return
 */
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

/**
 * Get the rotation of the current bestiole
 * @return
 */
float
Bestiole::getRotation() const
{
    return ellipse.getRotation() * M_PI / 180.0f;
}
/**
 * Get the speed vector of the current bestiole
 * @return
 */
sf::Vector2f
Bestiole::getVelocity() const
{
    auto const vitesse = getVitesse();
    auto const rotation = getRotation();
    auto const velocity = vitesse * Util::unit(rotation);
    return velocity;
}
/**
 * Get the shape of the current bestiole
 * @return
 */
sf::ConvexShape const&
Bestiole::getShape() const
{
    return ellipse;
}
/**
 * Get the sensor of the current bestiole
 * @return
 */
Capteur::Ptr const&
Bestiole::getCapteur() const
{
    return espece.capteur;
}
/**
 * Get the resistance coefficient of the bestiole
 * @return
 */
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
