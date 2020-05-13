//
// Created by quentin on 13/05/2020.
//

#include "GenerateurAleatoire.h"

GenerateurAleatoire&
GenerateurAleatoire::getSingleton()
{
    static GenerateurAleatoire gen;
    return gen;
}

GenerateurAleatoire::GenerateurAleatoire()
  : gen{ std::random_device{}() }
{
}

sf::Color
GenerateurAleatoire::uniformColor()
{
    auto const r = uniformInt<sf::Uint8>(0, 255);
    auto const g = uniformInt<sf::Uint8>(0, 255);
    auto const b = uniformInt<sf::Uint8>(0, 255);

    return { r, g, b };
}
