
#include "../../include/accessoire/Carapace.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Carapace::Carapace(float omega, float eta)
  : omega{ omega }
  , eta{ eta }
{
    static bool textureLoaded{ false };
    static sf::Texture texture;

    if (!textureLoaded)
    {
        if (!texture.loadFromFile("../res/carapace.png"))
        {
            throw std::runtime_error{ "Can't load res/carapace.png" };
        }
    }

    sprite.setTexture(texture, true);
    sprite.setOrigin(0.5f * static_cast<sf::Vector2f>(texture.getSize()));
}

Protection::Ptr
Carapace::cloner()
{
    return std::make_unique<Carapace>(*this);
}

void
Carapace::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

float
Carapace::getCoeffResistance() const
{
    return eta;
}

float
Carapace::getFacteurVitesse() const
{
    return omega;
}
