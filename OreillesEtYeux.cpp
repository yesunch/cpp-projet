//
// Created by quentin on 14/05/2020.
//

#include "OreillesEtYeux.h"
#include <set>

OreillesEtYeux::OreillesEtYeux(Oreilles oreilles, Yeux yeux)
  : oreilles{ oreilles }
  , yeux{ yeux }
{
}

Capteur::Ptr
OreillesEtYeux::cloner()
{
    return std::make_unique<OreillesEtYeux>(*this);
}

std::vector<ObservationBestiole>
OreillesEtYeux::capter(const std::vector<Bestiole>& bestioles,
                       sf::Vector2f position,
                       sf::Vector2f orientation) const
{
    auto const obsOreilles = oreilles.capter(bestioles, position, orientation);
    auto const obsYeux = yeux.capter(bestioles, position, orientation);

    std::set<ObservationBestiole> observations;
    observations.insert(obsOreilles.cbegin(), obsOreilles.cend());
    observations.insert(obsYeux.cbegin(), obsYeux.cend());

    return { observations.cbegin(), observations.cend() };
}

float
OreillesEtYeux::getAlpha() const
{
    return yeux.getAlpha();
}

float
OreillesEtYeux::getDeltaO() const
{
    return oreilles.getDelta();
}

float
OreillesEtYeux::getDeltaY() const
{
    return yeux.getDelta();
}

float
OreillesEtYeux::getGammaO() const
{
    return oreilles.getGamma();
}

float
OreillesEtYeux::getGammaY() const
{
    return yeux.getGamma();
}