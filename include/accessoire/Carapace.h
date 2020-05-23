
#ifndef BESTIOLES_CARAPACE_H
#define BESTIOLES_CARAPACE_H

#include "../Protection.h"

#include <SFML/Graphics/Sprite.hpp>

class Carapace : public Protection
{
  public:
    Carapace(float omega, float eta);
    Ptr cloner() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float getCoeffResistance() const override;
    float getFacteurVitesse() const override;

  private:
    float omega;
    float eta;

    sf::Sprite sprite;
};

#endif // BESTIOLES_CARAPACE_H
