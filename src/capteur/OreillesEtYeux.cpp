
#include <set>

#include <SFML/Graphics/RenderTarget.hpp>

#include "../../include/capteur/OreillesEtYeux.h"

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
                       sf::Vector2f orientation)
{
    auto const obsOreilles = oreilles.capter(bestioles, position, orientation);
    auto const obsYeux = yeux.capter(bestioles, position, orientation);

    std::set<ObservationBestiole> observations;
    observations.insert(obsOreilles.cbegin(), obsOreilles.cend());
    observations.insert(obsYeux.cbegin(), obsYeux.cend());

    return { observations.cbegin(), observations.cend() };
}

void
OreillesEtYeux::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(oreilles, states);
    target.draw(yeux, states);
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
