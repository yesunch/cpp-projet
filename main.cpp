#include "Aquarium.h"

int
main()
{
    auto const size = sf::Vector2u{ 640, 480 };
    auto const timeStep = sf::seconds(1.0f / 60.0f);

    Aquarium aquarium{ size, timeStep };
    aquarium.run();

    return 0;
}
