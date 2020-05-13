//
// Created by quentin on 13/05/2020.
//

#include "Milieu.h"
#include "GenerateurAleatoire.h"

#include <SFML/Graphics.hpp>

Milieu::Milieu(sf::FloatRect bords)
  : bords{ bords }
  , nextBestioleId{ 0 }
{
    auto& genAlea = GenerateurAleatoire::getSingleton();

    for (int i = 0; i < 10; ++i)
    {
        bestioles.emplace_back(nextBestioleId++, Espece{});
        bestioles.back().setPosition(
            sf::Vector2f{ genAlea.uniformReal(bords.left, bords.left + bords.width),
                          genAlea.uniformReal(bords.top, bords.top + bords.height) });
        bestioles.back().setVelocity(
            sf::Vector2f{ genAlea.uniformReal(0.0f, 15.0f), genAlea.uniformReal(0.0f, 15.0f) });
    }
}

void
Milieu::update(sf::Time timeStep)
{
    std::vector<ObservationBestiole> observationsBestiole;
    std::transform(bestioles.cbegin(),
                   bestioles.cend(),
                   std::back_inserter(observationsBestiole),
                   [](Bestiole const& bestiole) { return bestiole.getObservation(); });

    for (auto& bestiole : bestioles)
    {
        bestiole.update(observationsBestiole, bords, timeStep);
    }
}

void
Milieu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rectangleShape{ { bords.width, bords.height } };
    rectangleShape.setPosition(bords.left, bords.top);
    rectangleShape.setFillColor(sf::Color::White);
    target.draw(rectangleShape);

    for (auto const& bestiole : bestioles)
    {
        target.draw(bestiole, states);
    }
}

sf::Vector2f
Milieu::getTaille() const
{
    return { bords.width, bords.height };
}
