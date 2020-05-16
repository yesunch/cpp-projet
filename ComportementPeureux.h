//
// Created by quentin on 15/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTPEUREUX_H
#define BESTIOLES_COMPORTEMENTPEUREUX_H

#include "Bestiole.h"
#include "Comportement.h"

class ComportementPeureux : public Comportement
{
  public:
    static constexpr auto SEUIL_FUITE = 2;

    ComportementPeureux() = default;
    Ptr cloner() override;

    sf::Color getColor() const override;
    const char* getName() const override;

    void update(std::vector<ObservationBestiole> const& obsBestioles,
                Bestiole& moiMeme,
                sf::Time timeStep) override;

  private:
    sf::Time timeOut;
};

#endif // BESTIOLES_COMPORTEMENTPEUREUX_H
