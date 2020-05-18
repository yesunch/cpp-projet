//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_GENERATEURALEATOIRE_H
#define BESTIOLES_GENERATEURALEATOIRE_H

#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class GenerateurAleatoire
{
  public:
    static GenerateurAleatoire& getSingleton();

    bool uniformBernoulli();

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

    float uniformRotation();
    sf::Vector2f uniformPoint(sf::FloatRect bords);
    sf::Vector2f uniformUnit();

    sf::Color uniformColor();

    template<typename... Args>
    auto discrete(Args&&... args)
    {
        std::discrete_distribution<> dd(std::forward<Args>(args)...);
        return dd(gen);
    }

  private:
    GenerateurAleatoire();
    GenerateurAleatoire(GenerateurAleatoire const&) = delete;
    GenerateurAleatoire(GenerateurAleatoire&&) = delete;

    std::mt19937 gen;
};

#endif // BESTIOLES_GENERATEURALEATOIRE_H
