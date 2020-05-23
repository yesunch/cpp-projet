
#include "../../include/capteur/Yeux.h"
#include "../../include/Bestiole.h"
#include "../../include/Util.h"

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>

Yeux::Yeux(float alpha, float delta, float gamma)
  : alpha{ alpha }
  , delta{ delta }
  , gamma{ gamma }
  , vertexArray{ sf::TriangleFan, 20 }
{
    auto const vertexCount = vertexArray.getVertexCount();

    vertexArray[0].position = {};
    vertexArray[0].color = { 255, 0, 0, 50 };
    for (size_t i = 1; i < vertexCount; ++i)
    {
        vertexArray[i].position =
            delta *
            Util::unit(-0.5f * alpha + (i - 1) / static_cast<float>(vertexCount - 2) * alpha);
        vertexArray[i].color = { 255, 255, 255, 0 };
    }
}

Capteur::Ptr
Yeux::cloner()
{
    return std::make_unique<Yeux>(*this);
}

std::vector<ObservationBestiole>
Yeux::capter(const std::vector<Bestiole>& bestioles,
             sf::Vector2f position,
             sf::Vector2f orientation)
{
    transformable.setPosition(position);
    transformable.setRotation(Util::angle(orientation) * 180.0f * M_1_PI);

    std::vector<ObservationBestiole> observations;
    for (auto const& bestiole : bestioles)
    {
        auto const deltaPos = bestiole.getPosition() - position;
        auto const distance = Util::magnitude(deltaPos);
        auto const angle = Util::angle(orientation, deltaPos);

        if (0.0f < distance && distance < delta && 2.0f * fabs(angle) < alpha)
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
Yeux::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= transformable.getTransform();
    target.draw(vertexArray, states);
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