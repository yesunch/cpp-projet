//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_BESTIOLE_H
#define BESTIOLES_BESTIOLE_H

#include "Espece.h"
#include "ObservationBestiole.h"

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Time.hpp>

class Bestiole : public sf::Drawable
{
  public:
    using Id = unsigned int;

    static constexpr auto NB_POINTS = 30;
    static constexpr auto LENGTH = 64.0f;

  public:
    Bestiole(Id id, Espece const& espece);
    void buildEllipse();

    void update(std::vector<ObservationBestiole> const& bestiolesObservees,
                sf::FloatRect bordsMilieu,
                sf::Time timeStep);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    bool contains(sf::Vector2f point);
    bool intersects(sf::ConvexShape const& shape);

    ObservationBestiole getObservation() const;

    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

  private:
    Id const id;

    float length;
    float thickness;

    sf::ConvexShape ellipse;

    sf::Vector2f velocity;
};

#endif // BESTIOLES_BESTIOLE_H
