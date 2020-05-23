
#include "../include/GenerateurAleatoire.h"

GenerateurAleatoire&
GenerateurAleatoire::getSingleton()
{
    static GenerateurAleatoire singleton;
    return singleton;
}

bool
GenerateurAleatoire::uniformBernoulli()
{
    return uniformInt(0, 2) == 1;
}

GenerateurAleatoire::GenerateurAleatoire()
  : gen{ std::random_device{}() }
{
}

float
GenerateurAleatoire::uniformRotation()
{
    return uniformReal<float>(0.0f, 2.0f * M_PI);
}

sf::Vector2f
GenerateurAleatoire::uniformPoint(sf::FloatRect bords)
{
    return { uniformReal(bords.left, bords.left + bords.width),
             uniformReal(bords.top, bords.top + bords.height) };
}

sf::Vector2f
GenerateurAleatoire::uniformUnit()
{
    auto const angle = uniformReal<float>(0.0f, 2.0f * M_PI);
    return { cosf(angle), sinf(angle) };
}

sf::Color
GenerateurAleatoire::uniformColor()
{
    auto const r = uniformInt<sf::Uint8>(0, 255);
    auto const g = uniformInt<sf::Uint8>(0, 255);
    auto const b = uniformInt<sf::Uint8>(0, 255);

    return { r, g, b };
}
