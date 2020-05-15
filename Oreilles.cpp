//
// Created by quentin on 14/05/2020.
//

#include "Oreilles.h"
#include "Bestiole.h"
#include "Util.h"

Oreilles::Oreilles(float delta, float gamma)
  : delta{ delta }
  , gamma{ gamma }
{
}

Capteur::Ptr
Oreilles::cloner()
{
    return std::make_unique<Oreilles>(*this);
}

std::vector<ObservationBestiole>
Oreilles::capter(const std::vector<Bestiole>& bestioles,
                 sf::Vector2f position,
                 sf::Vector2f orientation) const
{
    std::vector<ObservationBestiole> observations;
    for (auto const& bestiole : bestioles)
    {
        auto const distance = Util::distance(bestiole.getPosition(), position);
        if (0.0f < distance && distance < delta)
        {
            auto observation = bestiole.creerObservation(distance);
            if (gamma > observation.coeffDissimulation)
            {
                observations.emplace_back(std::move(observation));
            }
        }
    }

    return std::move(observations);
}

float
Oreilles::getDelta() const
{
    return delta;
}

float
Oreilles::getGamma() const
{
    return gamma;
}
