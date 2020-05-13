//
// Created by quentin on 13/05/2020.
//

#include "Aquarium.h"

#include <SFML/Window.hpp>

Aquarium::Aquarium(sf::Vector2u size, sf::Time timeStep)
  : window{ { size.x, size.y }, "Aquarium" }
  , milieu{ static_cast<sf::Vector2f>(size) }
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
