//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_BESTIOLE_H
#define BESTIOLES_BESTIOLE_H

#include "Espece.h"

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

class Bestiole : public sf::Drawable
{
  public:
    using Id = unsigned int;

    static constexpr auto LENGTH = 8.0f;

  public:
    Bestiole(Id id, Espece const& espece);

    void update(std::vector<Bestiole> bestiolesProches, sf::Time timeStep);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

  private:
    Id const id;

    sf::Color color;

    sf::Vector2f position;
    sf::Vector2f velocity;
};

#endif // BESTIOLES_BESTIOLE_H
