//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTGREGAIRE_H
#define BESTIOLES_COMPORTEMENTGREGAIRE_H

#include "Comportement.h"

class ComportementGregaire : public Comportement
{
  public:
    Ptr cloner() override;

    sf::Color getColor() const override;
    const char* getName() const override;

    void update(std::vector<ObservationBestiole> const& obsBestioles,
                Bestiole& moiMeme,
                sf::Time timeStep) override;
};

#endif // BESTIOLES_COMPORTEMENTGREGAIRE_H
