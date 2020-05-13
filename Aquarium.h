//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_AQUARIUM_H
#define BESTIOLES_AQUARIUM_H

#include "Milieu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>

class Aquarium
{
  public:
    Aquarium(sf::Vector2u taille, sf::Time timeStep);

    void run();

  private:
    sf::Time const timeStep;
    sf::RenderWindow window;
    Milieu milieu;
};

#endif // BESTIOLES_AQUARIUM_H
