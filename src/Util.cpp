//
// Created by quentin on 14/05/2020.
//

#include "../include/Util.h"

#include <cassert>
#include <cmath>

/**
 * Calculate the magnitude of a vector
 * @param vec2
 * @return
 */
float
Util::magnitude(sf::Vector2f vec2)
{
    return sqrtf(dot(vec2, vec2));
}

/**
 * Calculate the angle of a vector
 * @param vec2
 * @return
 */
float
Util::angle(sf::Vector2f vec2)
{
    assert(vec2.x != 0.0f || vec2.y != 0.0f);
    return atan2f(vec2.y, vec2.x);
}

/**
 * Calculate the dot product of two vectors
 * @param vec1
 * @param vec2
 * @return
 */
float
Util::dot(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

/**
 * Calculate the determinant of the matrix composed by two vectors
 * @param vec1
 * @param vec2
 * @return
 */
float
Util::det(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

/**
 * Calculate the distance between two vectors
 * @param vec1
 * @param vec2
 * @return
 */
float
Util::distance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return magnitude(vec2 - vec1);
}

/**
 * Calculate the signed angle between two vector
 * @param vec1
 * @param vec2
 * @return
 */
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

/**
 * Transformed an angle into an unit vector in its direction
 * @param angle
 * @return
 */
sf::Vector2f
Util::unit(float angle)
{
    return { cosf(angle), sinf(angle) };
}

/**
 * Normalize a vector into an un unit vector
 * @param vec
 * @return
 */
sf::Vector2f
Util::normalize(sf::Vector2f vec)
{
    return vec /= magnitude(vec);
}

/**
 * Rotate a vector with an angle
 * @param vec
 * @param angle
 * @return
 */
sf::Vector2f
Util::rotate(sf::Vector2f vec, float angle)
{
    auto const cos = cosf(angle);
    auto const sin = sinf(angle);
    return { cos * vec.x + sin * vec.y, sin * vec.x - cos * vec.y };
}
