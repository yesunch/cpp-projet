//
// Created by quentin on 13/05/2020.
//

#include "Aquarium.h"

#include <SFML/Window.hpp>
#include <iostream>

Aquarium::Aquarium(sf::Vector2u taille, sf::Time timeStep)
  : window{ { taille.x, taille.y }, "Aquarium" }
  , milieu{ { {}, static_cast<sf::Vector2f>(taille) } }
  , timeStep{ timeStep }
{
    auto const framerateLimit = static_cast<unsigned int>(1.0f / timeStep.asSeconds());

    window.setFramerateLimit(framerateLimit);
    window.setKeyRepeatEnabled(false);
}

void
Aquarium::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }

        milieu.update(timeStep);

        window.clear();
        window.draw(milieu);
        window.display();
    }
}
