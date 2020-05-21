//
// Created by quentin on 15/05/2020.
//

#include "../../include/comportement/ComportementKamikaze.h"
#include "../../include/Util.h"

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

    // if closestBestiole points to the past-the-end element in obsBestioles
    if (closestBestiole == obsBestioles.cend())
    {
        return;
    }
    // turn current bestiole to closestBestiole 
    auto const deltaRotation = closestBestiole->angleToBestiole;
    moiMeme.rotate(deltaRotation * timeStep.asSeconds());
}