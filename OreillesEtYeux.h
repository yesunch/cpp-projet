//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_OREILLESETYEUX_H
#define BESTIOLES_OREILLESETYEUX_H

#include "Oreilles.h"
#include "Yeux.h"

class OreillesEtYeux : public Capteur
{
  public:
    OreillesEtYeux(Oreilles oreilles, Yeux yeux);

    Ptr cloner() override;
    std::vector<ObservationBestiole> capter(const std::vector<Bestiole>& bestioles,
                                            sf::Vector2f position,
                                            sf::Vector2f orientation) const override;

    float getAlpha() const;
    float getDeltaO() const;
    float getDeltaY() const;
    float getGammaO() const;
    float getGammaY() const;

  private:
    Oreilles oreilles;
    Yeux yeux;
};

#endif // BESTIOLES_OREILLESETYEUX_H
