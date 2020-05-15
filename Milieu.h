//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_MILIEU_H
#define BESTIOLES_MILIEU_H

#include "Bestiole.h"
#include "PopulationFactory.h"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>

class Milieu : public sf::Drawable
{
  public:
    explicit Milieu(sf::FloatRect bords);

    void initialiserPopulation(PopulationFactory& populationFactory);

    void update(PopulationFactory& populationFactory, sf::Time timeStep);
    void handleCollisions(sf::Time timeStep);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getTaille() const;

  private:
    sf::FloatRect const bords;

    BestioleId nextBestioleId;

    std::vector<Bestiole> bestioles;
};

#endif // BESTIOLES_MILIEU_H
