//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_POPPARCOMPORTEMENTFACTORY_H
#define BESTIOLES_POPPARCOMPORTEMENTFACTORY_H

#include <vector>

#include "Comportement.h"
#include "PopulationFactory.h"

class PopParComportementFactory : public PopulationFactory
{
  public:
    PopParComportementFactory(float alphaMin,
                              float alphaMax,

                              float deltaOmin,
                              float deltaOmax,
                              float deltaYmin,
                              float deltaYmax,

                              float gammaOmin,
                              float gammaOmax,
                              float gammaYmin,
                              float gammaYmax,

                              float nuMax,
                              float omegaMax,
                              float etaMax,

                              float phiMin,
                              float phiMax);

    void addComportement(Comportement::Ptr comp, unsigned int effectif);

    std::vector<Bestiole> creerPopulation(sf::FloatRect bords) override;

    Bestiole creerBestiole(sf::FloatRect bords) override;
    Bestiole clonerBestiole(Bestiole const& bestiole) override;

    Espece especeAleatoire() const;

  private:
    std::vector<std::pair<Comportement::Ptr, unsigned int>> effectifParComp;

    float alphaMin;
    float alphaMax;

    float deltaOmin;
    float deltaOmax;
    float deltaYmin;
    float deltaYmax;

    float gammaOmin;
    float gammaOmax;
    float gammaYmin;
    float gammaYmax;

    float nuMax;
    float omegaMax;
    float etaMax;

    float phiMin;
    float phiMax;
};

#endif // BESTIOLES_POPPARCOMPORTEMENTFACTORY_H
