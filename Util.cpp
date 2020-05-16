//
// Created by quentin on 14/05/2020.
//

#include "Util.h"

#include <cassert>
#include <cmath>

float
Util::magnitude(sf::Vector2f vec2)
{
    return sqrtf(dot(vec2, vec2));
}

float
Util::angle(sf::Vector2f vec2)
{
    assert(vec2.x != 0.0f || vec2.y != 0.0f);
    return atan2f(vec2.y, vec2.x);
}

float
Util::dot(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

float
Util::det(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

float
Util::distance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return magnitude(vec2 - vec1);
}

float
Util::angle(sf::Vector2f vec1, sf::Vector2f vec2)
{
    auto absAngle = acosf(dot(normalize(vec1), normalize(vec2)));
    absAngle = clamp<float>(0.0f, absAngle, M_PI);

    auto const sign = det(vec1, vec2);
    if (sign > 0)
    {
        return absAngle;
    }
    else
    {
        return -absAngle;
    }
}

sf::Vector2f
Util::unit(float angle)
{
    return { cosf(angle), sinf(angle) };
}

sf::Vector2f
Util::normalize(sf::Vector2f vec)
{
    return vec /= magnitude(vec);
}

sf::Vector2f
Util::rotate(sf::Vector2f vec, float angle)
{
    auto const cos = cosf(angle);
    auto const sin = sinf(angle);
    return { cos * vec.x + sin * vec.y, sin * vec.x - cos * vec.y };
}
