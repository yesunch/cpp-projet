//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_COLLISION_H
#define BESTIOLES_COLLISION_H

#include <SFML/System/Vector2.hpp>

struct Collision
{
    Collision(bool happened);

    bool happened;
    sf::Vector2f position;
    sf::Vector2f normale;

    explicit operator bool() const;
};

#endif // BESTIOLES_COLLISION_H
