//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_NAGEOIRES_H
#define BESTIOLES_NAGEOIRES_H

#include "Locomotion.h"

class Nageoires : public Locomotion
{
  public:
    Nageoires(float nu);
    Ptr cloner() override;

    float getFacteurVitesse() const override;

  private:
    float nu;
};

#endif // BESTIOLES_NAGEOIRES_H
