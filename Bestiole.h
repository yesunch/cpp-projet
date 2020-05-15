//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_BESTIOLE_H
#define BESTIOLES_BESTIOLE_H

#include "Collision.h"
#include "Comportement.h"
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

    static constexpr auto NB_POINTS = 15;
    static constexpr auto LENGTH = 16.0f;
    static constexpr auto BASE_SPEED = 10.0f;

  public:
    Bestiole(Id id, Espece espece, Comportement::Ptr comp);
    void buildEllipse();

    void update(std::vector<ObservationBestiole> const& bestiolesObservees,
                sf::FloatRect bordsMilieu,
                const std::function<void()>& seCloner,
                const std::function<void()>& mourrir,
                sf::Time timeStep);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getPosition() const;
    sf::Vector2f getOrientation() const;
    float getVitesse() const;
    float getRotation() const;
    sf::Vector2f getVelocity() const;
    sf::ConvexShape const& getShape() const;

    Capteur::Ptr const& getCapteur() const;

    Espece clonerEspece() const;
    Comportement::Ptr clonerComportement() const;

    bool contains(sf::Vector2f point) const;
    Collision testCollision(sf::ConvexShape const& shape) const;

    ObservationBestiole creerObservation(float distanceObserveur) const;

    void setPosition(sf::Vector2f position);
    void setRotation(float angle);
    void setOrientation(sf::Vector2f orientation);

    void etourdirPendant(sf::Time time);

  private:
    Id const id;
    Espece espece;
    Comportement::Ptr comportement;

    float length;
    float thickness;
    sf::ConvexShape ellipse;

    sf::Time etourdissement;
};

#endif // BESTIOLES_BESTIOLE_H
