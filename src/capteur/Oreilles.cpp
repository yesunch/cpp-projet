//
// Created by quentin on 14/05/2020.
//

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>

#include "../../include/Bestiole.h"
#include "../../include/capteur/Oreilles.h"
#include "../../include/Util.h"

Oreilles::Oreilles(float delta, float gamma)
  : delta{ delta }
  , gamma{ gamma }
  , circleShape{ delta, 15 }
{
    circleShape.setFillColor(sf::Color::Transparent);
    circleShape.setOutlineThickness(1.0f);
    circleShape.setOrigin(delta, delta);
}

Capteur::Ptr
Oreilles::cloner()
{
    return std::make_unique<Oreilles>(*this);
}

std::vector<ObservationBestiole>
Oreilles::capter(const std::vector<Bestiole>& bestioles,
                 sf::Vector2f position,
                 sf::Vector2f orientation)
{
    auto const temp = 0.5f + 0.5f * sinf(circleShape.getRotation());
    circleShape.setOutlineColor({ 255, 0, 0, static_cast<sf::Uint8>(50.0f * temp) });
    circleShape.setScale(0.95f + 0.05f * temp, 0.95f + 0.05f * temp);
    circleShape.setPosition(position);
    circleShape.rotate(clock.restart().asSeconds() * 10.0f);

    std::vector<ObservationBestiole> observations;
    for (auto const& bestiole : bestioles)
    {
        auto const deltaPos = bestiole.getPosition() - position;
        auto const distance = Util::magnitude(deltaPos);
        auto const angle = Util::angle(orientation, deltaPos);

        if (0.0f < distance && distance < delta)
        {
            auto observation = bestiole.etreObservee(distance, angle);
            if (gamma > observation.coeffDissimulation)
            {
                observations.emplace_back(std::move(observation));
            }
        }
    }

    return std::move(observations);
}

void
Oreilles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circleShape, states);
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