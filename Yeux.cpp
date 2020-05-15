//
// Created by quentin on 14/05/2020.
//

#include "Yeux.h"
#include "Bestiole.h"
#include "Util.h"

#include <cmath>

Yeux::Yeux(float alpha, float delta, float gamma)
  : alpha{ alpha }
  , delta{ delta }
  , gamma{ gamma }
{
}

Capteur::Ptr
Yeux::cloner()
{
    return std::make_unique<Yeux>(*this);
}

std::vector<ObservationBestiole>
Yeux::capter(const std::vector<Bestiole>& bestioles,
             sf::Vector2f position,
             sf::Vector2f orientation) const
{
    std::vector<ObservationBestiole> observations;
    for (auto const& bestiole : bestioles)
    {
        auto const deltaPos = bestiole.getPosition() - position;
        auto const distance = Util::magnitude(deltaPos);
        auto const angle = Util::angle(orientation, deltaPos);

        if (0.0f < distance && distance < delta && 2.0f * fabs(angle) < alpha)
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
Yeux::getAlpha() const
{
    return alpha;
}

float
Yeux::getDelta() const
{
    return delta;
}

float
Yeux::getGamma() const
{
    return gamma;
}
