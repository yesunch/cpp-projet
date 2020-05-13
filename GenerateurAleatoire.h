//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_GENERATEURALEATOIRE_H
#define BESTIOLES_GENERATEURALEATOIRE_H

#include <random>

#include <SFML/Graphics/Color.hpp>

class GenerateurAleatoire
{
  public:
    static GenerateurAleatoire& getSingleton();

    template<typename T>
    T uniformInt(T min, T max)
    {
        std::uniform_int_distribution<T> urd{ min, max };
        return urd(gen);
    }

    template<typename T>
    T uniformReal(T min, T max)
    {
        std::uniform_real_distribution<T> urd{ min, max };
        return urd(gen);
    }

    sf::Color uniformColor();

  private:
    GenerateurAleatoire();
    GenerateurAleatoire(GenerateurAleatoire const&) = delete;
    GenerateurAleatoire(GenerateurAleatoire&&) = delete;

    std::mt19937 gen;
};

#endif // BESTIOLES_GENERATEURALEATOIRE_H
