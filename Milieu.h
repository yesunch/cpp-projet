//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_MILIEU_H
#define BESTIOLES_MILIEU_H

#include "Bestiole.h"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

class Milieu : public sf::Drawable
{
  public:
    explicit Milieu(sf::Vector2f const size);

    void update(sf::Time timeStep);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getSize() const;

  private:
    sf::Vector2f const size;

    Bestiole::Id nextBestioleId;
    std::vector<Bestiole> bestioles;
};

#endif // BESTIOLES_MILIEU_H
