//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_OREILLES_H
#define BESTIOLES_OREILLES_H

#include "Capteur.h"
class Oreilles : public Capteur
{
  public:
    Oreilles(float delta, float gamma);

    Ptr cloner() override;
    std::vector<ObservationBestiole> capter(const std::vector<Bestiole>& bestioles,
                                            sf::Vector2f position,
                                            sf::Vector2f orientation) const override;

    float getDelta() const;
    float getGamma() const;

  private:
    float delta;
    float gamma;
};

#endif // BESTIOLES_OREILLES_H
