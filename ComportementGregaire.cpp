//
// Created by quentin on 14/05/2020.
//

#include "ComportementGregaire.h"
#include "Bestiole.h"
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

const char*
ComportementGregaire::getName() const
{
    return "grégaire";
}

void
ComportementGregaire::update(std::vector<ObservationBestiole> const& obsBestioles,
                             Bestiole& moiMeme,
                             sf::Time timeStep)
{
    if (obsBestioles.empty())
    {
        return;
    }

    sf::Vector2f sum;
    for (auto const& obsBestiole : obsBestioles)
    {
        sum += obsBestiole.velocity;
    }

    auto const deltaRotation = Util::angle(moiMeme.getOrientation(), sum);
    moiMeme.rotate(deltaRotation * timeStep.asSeconds());
}
