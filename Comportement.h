//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENT_H
#define BESTIOLES_COMPORTEMENT_H

#include "ObservationBestiole.h"

class Bestiole;

class Comportement
{
  public:
    using Ptr = std::unique_ptr<Comportement>;
    virtual Ptr cloner() = 0;

    virtual sf::Color getColor() const = 0;
    virtual const char* getName() const = 0;

    virtual void update(std::vector<ObservationBestiole> const& obsBestioles,
                        Bestiole& moiMeme,
                        sf::Time timeStep) = 0;

    virtual ~Comportement() = default;
};

#endif // BESTIOLES_COMPORTEMENT_H
