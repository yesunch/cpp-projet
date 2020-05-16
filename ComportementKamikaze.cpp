//
// Created by quentin on 15/05/2020.
//

#include "ComportementKamikaze.h"
#include "Util.h"

Comportement::Ptr
ComportementKamikaze::cloner()
{
    return std::make_unique<ComportementKamikaze>(*this);
}

sf::Color
ComportementKamikaze::getColor() const
{
    return sf::Color::Red;
}

const char*
ComportementKamikaze::getName() const
{
    return "kamikaze";
}

void
ComportementKamikaze::update(const std::vector<ObservationBestiole>& obsBestioles,
                             Bestiole& moiMeme,
                             sf::Time timeStep)
{
    auto const closestBestiole = std::min_element(obsBestioles.cbegin(), obsBestioles.cend());

    if (closestBestiole == obsBestioles.cend())
    {
        return;
    }

    auto const deltaRotation = closestBestiole->angleToBestiole;
    moiMeme.rotate(deltaRotation * timeStep.asSeconds());
}