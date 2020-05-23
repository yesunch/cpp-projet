
#ifndef BESTIOLES_NAGEOIRES_H
#define BESTIOLES_NAGEOIRES_H

#include "../Locomotion.h"

#include <SFML/Graphics/Sprite.hpp>

class Nageoires : public Locomotion
{
  public:
    Nageoires(float nu);
    Ptr cloner() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float getFacteurVitesse() const override;

  private:
    float nu;

    sf::Sprite sprite;
};

#endif // BESTIOLES_NAGEOIRES_H
