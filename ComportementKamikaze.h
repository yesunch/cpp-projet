//
// Created by quentin on 15/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTKAMIKAZE_H
#define BESTIOLES_COMPORTEMENTKAMIKAZE_H

#include "Bestiole.h"
#include "Comportement.h"

class ComportementKamikaze : public Comportement
{
  public:
    Ptr cloner() override;

    sf::Color getColor() const override;
    const char* getName() const override;

    void update(std::vector<ObservationBestiole> const& obsBestioles,
                Bestiole& moiMeme,
                sf::Time timeStep) override;
};

#endif // BESTIOLES_COMPORTEMENTKAMIKAZE_H
