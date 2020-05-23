//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_BESTIOLE_H
#define BESTIOLES_BESTIOLE_H

#include "Collision.h"
#include "Espece.h"
#include "ObservationBestiole.h"
#include "comportement/Comportement.h"

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
    static constexpr auto VITESSE_DE_BASE = 30.0f;
    static constexpr auto VULNERABILITE_CHOC = 0.2f;
    static constexpr auto PROBABILITE_CLONAGE = 0.1f;

  public:
    Bestiole(Id id, Espece espece, Comportement::Ptr comp);
    Bestiole(Bestiole&& b) = default;
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
    BestioleId getId() const;
    sf::Vector2f getVelocity() const;
    sf::ConvexShape const& getShape() const;
    float getCoeffResistance() const;
    Capteur::Ptr const& getCapteur() const;
    sf::FloatRect getGlobalBounds() const;

    Espece clonerEspece() const;
    Comportement::Ptr clonerComportement() const;

    float testOverlap(sf::Vector2f point0) const;
    Collision testCollision(sf::ConvexShape const& shape) const;

    ObservationBestiole etreObservee(float distanceObserveur, float angleObserveur) const;

    void setPosition(sf::Vector2f position);
    void setRotation(float angle);
    void setOrientation(sf::Vector2f orientation);

    void rotate(float angle);

    Bestiole& operator=(Bestiole&& b) = default;

  private:
    Id id;
    Espece espece;
    Comportement::Ptr comportement;

    sf::ConvexShape ellipse;
    sf::Time dureeDeVie;
};

#endif // BESTIOLES_BESTIOLE_H
