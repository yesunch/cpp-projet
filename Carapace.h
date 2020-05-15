//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_CARAPACE_H
#define BESTIOLES_CARAPACE_H

#include "Protection.h"

class Carapace : public Protection
{
  public:
    Carapace(float omega, float eta);
    Ptr cloner() override;

    float getCoeffResistance() const override;
    float getFacteurVitesse() const override;

  private:
    float omega;
    float eta;
};

#endif // BESTIOLES_CARAPACE_H
