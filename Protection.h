//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_PROTECTION_H
#define BESTIOLES_PROTECTION_H

#include <memory>

class Protection
{
  public:
    using Ptr = std::unique_ptr<Protection>;
    virtual Ptr cloner() = 0;

    virtual float getCoeffResistance() const = 0;
    virtual float getFacteurVitesse() const = 0;

    virtual ~Protection() = default;
};

#endif // BESTIOLES_PROTECTION_H
