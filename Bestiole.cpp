//
// Created by quentin on 13/05/2020.
//

#include "Bestiole.h"
#include "Espece.h"

#include <cmath>

#include <SFML/Graphics.hpp>

Bestiole::Bestiole(Bestiole::Id id, const Espece& espece)
  : id{ id }
  , color{ { static_cast<sf::Uint32>(rand()) } }
{
}

void
Bestiole::update(std::vector<Bestiole> bestiolesProches, sf::Time timeStep)
{
    position += velocity * timeStep.asSeconds();
}

void
Bestiole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circleShape;
    circleShape.setFillColor(color);
    circleShape.setRadius(Bestiole::LENGTH);
    circleShape.setScale(1.0f, 0.5f);
    circleShape.setOrigin(0.5f * circleShape.getLocalBounds().width,
                          0.5f * circleShape.getLocalBounds().height);
    circleShape.setPosition(position);
    circleShape.setRotation(std::atan2(velocity.y, velocity.x) * 180.0f * M_1_PI);

    target.draw(circleShape, states);
}

sf::Vector2f
Bestiole::getPosition() const
{
    return position;
}

sf::Vector2f
Bestiole::getVelocity() const
{
    return velocity;
}

void
Bestiole::setPosition(sf::Vector2f position)
{
    this->position = position;
}

void
Bestiole::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
