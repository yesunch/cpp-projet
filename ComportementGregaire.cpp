//
// Created by quentin on 14/05/2020.
//

#include "ComportementGregaire.h"
#include "Util.h"

Comportement::Ptr
ComportementGregaire::cloner()
{
    return std::make_unique<ComportementGregaire>();
}

sf::Color
ComportementGregaire::getColor() const
{
    return sf::Color::Green;
}

float
ComportementGregaire::updateRotation(std::vector<ObservationBestiole> const& obsBestioles,
                                     float currentRotation,
                                     sf::Time timeStep)
{
    if (obsBestioles.empty())
    {
        return currentRotation;
    }

    sf::Vector2f sum;
    for (auto const& obsBestiole : obsBestioles)
    {
        sum += obsBestiole.orientation;
    }

    auto const deltaRotation = Util::angle(Util::unit(currentRotation), sum) * timeStep.asSeconds();
    return currentRotation + deltaRotation;
}