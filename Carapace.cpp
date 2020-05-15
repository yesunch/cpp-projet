//
// Created by quentin on 14/05/2020.
//

#include "Carapace.h"

Carapace::Carapace(float omega, float eta)
  : omega{ omega }
  , eta{ eta }
{
}

Protection::Ptr
Carapace::cloner()
{
    return std::make_unique<Carapace>(*this);
}

float
Carapace::getCoeffResistance() const
{
    return eta;
}

float
Carapace::getFacteurVitesse() const
{
    return omega;
}
