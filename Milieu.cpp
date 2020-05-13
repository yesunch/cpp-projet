//
// Created by quentin on 13/05/2020.
//

#include "Milieu.h"

#include <SFML/Graphics.hpp>

Milieu::Milieu(sf::Vector2f size)
  : size{ size }
  , nextBestioleId{ 0 }
{
    for (int i = 0; i < 10; ++i)
    {
        bestioles.emplace_back(nextBestioleId++, Espece{});
        bestioles.back().setPosition(sf::Vector2f(rand() % int(size.x), rand() % int(size.y)));
        bestioles.back().setVelocity(sf::Vector2f(rand() % 15, rand() % 15));
    }
}

void
Milieu::update(sf::Time timeStep)
{
    for (auto& bestiole : bestioles)
    {
        bestiole.update({}, timeStep);
    }
}

void
Milieu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rectangleShape{ size };
    rectangleShape.setFillColor(sf::Color::White);
    target.draw(rectangleShape);

    for (auto const& bestiole : bestioles)
    {
        target.draw(bestiole, states);
    }
}

sf::Vector2f
Milieu::getSize() const
{
    return size;
}
