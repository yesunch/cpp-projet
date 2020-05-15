//
// Created by quentin on 15/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTPEUREUX_H
#define BESTIOLES_COMPORTEMENTPEUREUX_H

#include "Comportement.h"

class ComportementPeureux : public Comportement
{
  public:
    static constexpr auto SEUIL_FUITE = 2;
    static constexpr auto DUREE_FUITE = 1.0f;

    ComportementPeureux() = default;
    Ptr cloner() override;

    sf::Color getColor() const override;

    float updateRotation(std::vector<ObservationBestiole> const& obsBestioles,
                         float currentRotation,
                         sf::Time timeStep) override;

  private:
    sf::Time timeOut;
};

#endif // BESTIOLES_COMPORTEMENTPEUREUX_H
