#include "../include/Aquarium.h"
#include "../include/comportement/ComportementGregaire.h"
#include "../include/comportement/ComportementKamikaze.h"
#include "../include/comportement/ComportementPersonnaliteMultiples.h"
#include "../include/comportement/ComportementPeureux.h"
#include "../include/comportement/ComportementPrevoyant.h"
#include "../include/factory/PopParComportementFactory.h"

#include <cmath>
#include <iostream>

int
main()
{
    auto const taille = sf::Vector2u{ 640, 480 };
    auto const timeStep = sf::seconds(1.0f / 60.0f);

    try
    {
        Aquarium aquarium{ taille, timeStep };

        PopParComportementFactory popParCompFactory{ M_PI_4, M_PI,  30.0f, 70.0f, 70.0f,
                                                     100.0f, 0.25f, 0.5f,  0.5f,  0.75f,
                                                     1.5f,   1.5f,  2.0f,  0.25f, 0.75f };

        std::vector<Comportement::Ptr> comportements;
        comportements.emplace_back(std::make_unique<ComportementGregaire>());
        comportements.emplace_back(std::make_unique<ComportementPeureux>());
        comportements.emplace_back(std::make_unique<ComportementKamikaze>());
        comportements.emplace_back(std::make_unique<ComportementPrevoyant>());
        for (auto const& compPtr : comportements)
        {
            popParCompFactory.addComportement(compPtr->cloner(), 1);
        }

        popParCompFactory.addComportement(
            std::make_unique<ComportementPersonnaliteMultiples>(std::move(comportements)), 1);

        aquarium.run(popParCompFactory);
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
