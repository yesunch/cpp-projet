#include "Aquarium.h"
#include "ComportementGregaire.h"
#include "PopParComportementFactory.h"

#include <cmath>
#include <iostream>

int
main()
{
    auto const taille = sf::Vector2u{ 640, 480 };
    auto const timeStep = sf::seconds(1.0f / 25.0f);

    try
    {
        Aquarium aquarium{ taille, timeStep };

        PopParComportementFactory popParCompFactory{ M_PI_4, M_PI, 10.0f, 20.0f, 20.0f,
                                                     40.0f,  0.1f, 0.9f,  0.1f,  0.9f,
                                                     2.0f,   2.0f, 2.0f,  0.1f,  0.9f };
        popParCompFactory.addComportement(std::make_unique<ComportementGregaire>(), 100);

        aquarium.run(popParCompFactory);
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
