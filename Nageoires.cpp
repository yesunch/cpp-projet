//
// Created by quentin on 14/05/2020.
//

#include "Nageoires.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Nageoires::Nageoires(float nu)
  : nu{ nu }
{
    static bool textureLoaded{ false };
    static sf::Texture texture;

    if (!textureLoaded)
    {
        if (!texture.loadFromFile("res/nageoires.png"))
        {
            throw std::runtime_error{ "Can't load res/nageoires.png" };
        }
    }

    sprite.setTexture(texture, true);
    sprite.setOrigin(0.5f * static_cast<sf::Vector2f>(texture.getSize()));
}

Locomotion::Ptr
Nageoires::cloner()
{
    return std::make_unique<Nageoires>(*this);
}

void
Nageoires::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

float
Nageoires::getFacteurVitesse() const
{
    return nu;
}
