//
// Created by quentin on 14/05/2020.
//

#include "../../include/comportement/ComportementGregaire.h"
#include "../../include/Bestiole.h"
#include "../../include/Util.h"

Comportement::Ptr
ComportementGregaire::cloner()
{
    return std::make_unique<ComportementGregaire>();
}

/**
 * Get the color of ComportementGregaire which is green. It means all of the bestioles with Gregaire
 * behavior are magenta.
 * @return
 */
sf::Color
ComportementGregaire::getColor() const
{
    return sf::Color::Magenta;
}

/**
 * Get the name of the gregaire behavior
 * @return
 */
const char*
ComportementGregaire::getName() const
{
    return "grégaire";
}

/**
 * Change the direction into the average direction of bestioles observed.
 * @param obsBestioles
 * @param moiMeme
 * @param timeStep
 */
void
ComportementGregaire::update(std::vector<ObservationBestiole> const& obsBestioles,
                             Bestiole& moiMeme,
                             sf::Time timeStep)
{
    if (obsBestioles.empty())
    {
        return;
    }

    // Get the average direction of the bestioles detected
    sf::Vector2f sum;
    for (auto const& obsBestiole : obsBestioles)
    {
        sum += obsBestiole.velocity;
    }

    // Calculate te angle between the bestiole current direction and the average direction of the
    // bestioles observed
    auto const deltaRotation = Util::angle(moiMeme.getOrientation(), sum);
    moiMeme.rotate(deltaRotation * timeStep.asSeconds());
}
