//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_LOCOMOTION_H
#define BESTIOLES_LOCOMOTION_H

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

class Locomotion : public sf::Drawable
{
  public:
    using Ptr = std::unique_ptr<Locomotion>;
    virtual Ptr cloner() = 0;

    virtual float getFacteurVitesse() const = 0;

    virtual ~Locomotion() = default;
};

#endif // BESTIOLES_LOCOMOTION_H
