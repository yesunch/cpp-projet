//
// Created by quentin on 15/05/2020.
//

#include <cmath>

#include "ComportementPeureux.h"
#include "Util.h"

Comportement::Ptr
ComportementPeureux::cloner()
{
    return std::make_unique<ComportementPeureux>(*this);
}

sf::Color
ComportementPeureux::getColor() const
{
    return sf::Color::Magenta;
}

float
ComportementPeureux::updateRotation(const std::vector<ObservationBestiole>& obsBestioles,
                                    float currentRotation,
                                    sf::Time timeStep)
{
    if (timeOut > sf::Time::Zero)
    {
        timeOut -= timeStep;
        return currentRotation;
    }

    if (obsBestioles.size() >= SEUIL_FUITE)
    {
        timeOut = sf::seconds(DUREE_FUITE);
        return currentRotation + M_PI;
    }

    return currentRotation;
}
