//
// Created by quentin on 14/05/2020.
//

#ifndef BESTIOLES_CAPTEUR_H
#define BESTIOLES_CAPTEUR_H

#include <memory>

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "ObservationBestiole.h"

class Bestiole;

class Capteur
{
  public:
    using Ptr = std::unique_ptr<Capteur>;
    virtual Ptr cloner() = 0;

    virtual std::vector<ObservationBestiole> capter(std::vector<Bestiole> const& bestioles,
                                                    sf::Vector2f position,
                                                    sf::Vector2f orientation) const = 0;

    virtual ~Capteur() = default;
};

#endif // BESTIOLES_CAPTEUR_H
