//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_UTIL_H
#define BESTIOLES_UTIL_H

#include <algorithm>

#include <SFML/System/Vector2.hpp>

class Util
{
  public:
    static float magnitude(sf::Vector2f vec);
    static float angle(sf::Vector2f vec);
    static float dot(sf::Vector2f vec1, sf::Vector2f vec2);
    static float det(sf::Vector2f vec1, sf::Vector2f vec2);
    static float distance(sf::Vector2f vec1, sf::Vector2f vec2);
    static float angle(sf::Vector2f vec1, sf::Vector2f vec2);
    static sf::Vector2f unit(float angle);
    static sf::Vector2f normalize(sf::Vector2f vec);
    static sf::Vector2f rotate(sf::Vector2f vec, float angle);

    template<typename T>
    static T clamp(T min, T val, T max)
    {
        return std::min(std::max(min, val), max);
    }
};

#endif // BESTIOLES_UTIL_H
