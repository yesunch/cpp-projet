//
// Created by quentin on 13/05/2020.
//

#include "Bestiole.h"
#include "Espece.h"
#include "GenerateurAleatoire.h"

#include <cmath>

#include <SFML/Graphics.hpp>

Bestiole::Bestiole(Bestiole::Id id, const Espece& espece)
  : id{ id }
  , ellipse(Bestiole::NB_POINTS)
  , length{ Bestiole::LENGTH }
  , thickness{ 0.5f * Bestiole::LENGTH }
{
    buildEllipse();
}

void
Bestiole::buildEllipse()
{
    auto const nbPoints = ellipse.getPointCount();
    auto const angleStep = 2.0f * M_PI / nbPoints;

    for (int i = 0; i < nbPoints; ++i)
    {
        sf::Vector2f point{ cosf(angleStep * i), sinf(angleStep * i) };
        point.x *= 0.5f * length;
        point.y *= 0.5f * thickness;

        ellipse.setPoint(i, point);
    }

    auto& genAlea = GenerateurAleatoire::getSingleton();
    ellipse.setFillColor(genAlea.uniformColor());
}

void
Bestiole::update(std::vector<ObservationBestiole> const& bestiolesObservees,
                 sf::FloatRect bordsMilieu,
                 sf::Time timeStep)
{
    ellipse.move(velocity * timeStep.asSeconds());
    ellipse.setRotation(atan2f(velocity.y, velocity.x) * 180.0f * M_1_PI);

    auto& genAlea = GenerateurAleatoire::getSingleton();
    for (auto const& obsBestiole : bestiolesObservees)
    {
        if (obsBestiole.id != id && this->intersects(obsBestiole.ellipse))
        {
            ellipse.setFillColor(genAlea.uniformColor());
            break;
        }
    }
}

void
Bestiole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ellipse, states);
}

bool
Bestiole::contains(sf::Vector2f point0)
{
    auto const ellipseTransform = ellipse.getTransform();
    auto const nbPoints = ellipse.getPointCount();
    for (int i = 0; i < nbPoints - 1; ++i)
    {
        auto const point1 = ellipseTransform.transformPoint(ellipse.getPoint(i));
        auto const point2 = ellipseTransform.transformPoint(ellipse.getPoint(i + 1));

        auto const vec1 = point1 - point0;
        auto const vec2 = point2 - point0;
        auto const det = vec1.x * vec2.y - vec1.y * vec2.x;

        if (det < 0)
        {
            return false;
        }
    }

    return true;
}

bool
Bestiole::intersects(sf::ConvexShape const& ellipse)
{
    auto const bords = this->ellipse.getGlobalBounds();
    auto const ellipseNbPoints = ellipse.getPointCount();
    for (int i = 0; i < ellipseNbPoints; ++i)
    {
        auto const ellipseTransform = ellipse.getTransform();
        auto const pointEllipse = ellipseTransform.transformPoint(ellipse.getPoint(i));
        if (bords.contains(pointEllipse) && this->contains(pointEllipse))
        {
            return true;
        }
    }

    return false;
}

ObservationBestiole
Bestiole::getObservation() const
{
    return { id, ellipse, getVelocity() };
}

sf::Vector2f
Bestiole::getPosition() const
{
    return ellipse.getPosition();
}

sf::Vector2f
Bestiole::getVelocity() const
{
    return velocity;
}

void
Bestiole::setPosition(sf::Vector2f position)
{
    ellipse.setPosition(position);
}

void
Bestiole::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}