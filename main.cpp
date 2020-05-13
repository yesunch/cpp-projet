#include "Aquarium.h"

#include <iostream>

int
main()
{
    auto const taille = sf::Vector2u{ 640, 480 };
    auto const timeStep = sf::seconds(1.0f / 60.0f);

    try
    {
        Aquarium aquarium{ taille, timeStep };
        aquarium.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
