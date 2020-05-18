//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_POPULATIONFACTORY_H
#define BESTIOLES_POPULATIONFACTORY_H

#include "../Bestiole.h"

#include <vector>

class PopulationFactory
{
  public:
    virtual std::vector<Bestiole> creerPopulation(sf::FloatRect bords) = 0;

    virtual Bestiole creerBestiole(sf::FloatRect bords) = 0;
    virtual Bestiole clonerBestiole(Bestiole const& bestiole) = 0;

    virtual ~PopulationFactory() = default;

  protected:
    Bestiole::Id nextBestioleId{ 0 };
};

#endif // BESTIOLES_POPULATIONFACTORY_H
