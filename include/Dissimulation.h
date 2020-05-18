//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_DISSIMULATION_H
#define BESTIOLES_DISSIMULATION_H

#include <memory>

class Dissimulation
{
  public:
    using Ptr = std::unique_ptr<Dissimulation>;
    virtual Ptr cloner() = 0;

    virtual float getCoeffDissimulation() const = 0;

    virtual ~Dissimulation() = default;
};

#endif // BESTIOLES_DISSIMULATION_H
