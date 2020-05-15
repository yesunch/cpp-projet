//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_CAMOUFLAGE_H
#define BESTIOLES_CAMOUFLAGE_H

#include "Dissimulation.h"

class Camouflage : public Dissimulation
{
  public:
    Camouflage(float phi);

    Ptr cloner() override;

    float getCoeffDissimulation() const override;

  private:
    float phi;
};

#endif // BESTIOLES_CAMOUFLAGE_H
