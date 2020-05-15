//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_YEUX_H
#define BESTIOLES_YEUX_H

#include "Capteur.h"

class Yeux : public Capteur
{
  public:
    Yeux(float alpha, float delta, float gamma);

    Ptr cloner() override;
    std::vector<ObservationBestiole> capter(const std::vector<Bestiole>& bestioles,
                                            sf::Vector2f position,
                                            sf::Vector2f orientation) const override;

    float getAlpha() const;
    float getDelta() const;
    float getGamma() const;

  private:
    float alpha;
    float delta;
    float gamma;
};

#endif // BESTIOLES_YEUX_H
