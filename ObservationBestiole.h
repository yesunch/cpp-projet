//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_OBSERVATIONBESTIOLE_H
#define BESTIOLES_OBSERVATIONBESTIOLE_H

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System.hpp>

using BestioleId = unsigned int;

struct ObservationBestiole
{
    float distance;
    float coeffDissimulation;
    sf::ConvexShape ellipse;
    sf::Vector2f orientation;

    bool operator<(ObservationBestiole const& autreObs) const;
};

#endif // BESTIOLES_OBSERVATIONBESTIOLE_H
