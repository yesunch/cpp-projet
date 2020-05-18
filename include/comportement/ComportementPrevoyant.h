//
// Created by quentin on 15/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTPREVOYANT_H
#define BESTIOLES_COMPORTEMENTPREVOYANT_H

#include "Comportement.h"

class ComportementPrevoyant : public Comportement
{
  public:
    Ptr cloner() override;

    sf::Color getColor() const override;
    const char* getName() const override;

    void update(std::vector<ObservationBestiole> const& obsBestioles,
                Bestiole& moiMeme,
                sf::Time timeStep) override;
};

#endif // BESTIOLES_COMPORTEMENTPREVOYANT_H
