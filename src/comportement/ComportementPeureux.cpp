//
// Created by quentin on 15/05/2020.
//

#include <cmath>

#include "../../include/GenerateurAleatoire.h"
#include "../../include/Util.h"
#include "../../include/comportement/ComportementPeureux.h"

Comportement::Ptr
ComportementPeureux::cloner()
{
    return std::make_unique<ComportementPeureux>(*this);
}

sf::Color
ComportementPeureux::getColor() const
{
    return sf::Color::Green;
}

const char*
ComportementPeureux::getName() const
{
    return "peureux";
}

void
ComportementPeureux::update(const std::vector<ObservationBestiole>& obsBestioles,
                            Bestiole& moiMeme,
                            sf::Time timeStep)
{
    if (timeOut > sf::Time::Zero)
    {
        timeOut -= timeStep;
        return;
    }

    if (obsBestioles.size() >= SEUIL_FUITE)
    {
        auto& genAlea = GenerateurAleatoire::getSingleton();
        timeOut = sf::seconds(genAlea.uniformReal(1.0f, 2.0f));
        moiMeme.setOrientation(-moiMeme.getOrientation());
    }

    return;
}
