//
// Created by quentin on 14/05/2020.
//

#include "Nageoires.h"

Nageoires::Nageoires(float nu)
  : nu{ nu }
{
}

Locomotion::Ptr
Nageoires::cloner()
{
    return std::make_unique<Nageoires>(*this);
}

float
Nageoires::getFacteurVitesse() const
{
    return nu;
}
