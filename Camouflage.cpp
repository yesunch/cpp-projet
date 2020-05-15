//
// Created by quentin on 14/05/2020.
//

#include "Camouflage.h"

Camouflage::Camouflage(float phi)
  : phi{ phi }
{
}

Dissimulation::Ptr
Camouflage::cloner()
{
    return std::make_unique<Camouflage>(*this);
}

float
Camouflage::getCoeffDissimulation() const
{
    return phi;
}
