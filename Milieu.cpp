//
// Created by quentin on 13/05/2020.
//

#include "Milieu.h"
#include "ComportementGregaire.h"
#include "GenerateurAleatoire.h"
#include "Util.h"

#include <SFML/Graphics.hpp>

Milieu::Milieu(sf::FloatRect bords)
  : bords{ bords }
  , nextBestioleId{ 0 }
{
}

void
Milieu::initialiserPopulation(PopulationFactory& populationFactory)
{
    bestioles = populationFactory.creerPopulation(bords);
}

void
Milieu::update(PopulationFactory& populationFactory, sf::Time timeStep)
{
    for (auto& bestiole : bestioles)
    {
        std::vector<ObservationBestiole> observations;

        auto const& capteur = bestiole.getCapteur();
        if (capteur)
        {
            observations =
                capteur->capter(bestioles, bestiole.getPosition(), bestiole.getOrientation());
        }

        auto const seCloner = []() {};
        auto const mourrir = []() {};

        bestiole.update(observations, bords, seCloner, mourrir, timeStep);
    }

    handleCollisions(timeStep);
}

void
Milieu::handleCollisions(sf::Time timeStep)
{
    for (auto it1 = bestioles.begin(); it1 != bestioles.end(); ++it1)
    {
        auto pos1 = it1->getPosition();
        auto vel1 = it1->getVelocity();
        auto const bounds1 = it1->getShape().getGlobalBounds();

        if (bounds1.left < bords.left)
        {
            pos1.x = bords.left + 0.5f * bounds1.width + 1.0f;
            vel1.x = fabs(vel1.x);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            it1->etourdirPendant(sf::seconds(1.0f));
            break;
        }
        if (bords.left + bords.width < bounds1.left + bounds1.width)
        {
            pos1.x = bords.left + bords.width - 0.5f * bounds1.width - 1.0f;
            vel1.x = -fabs(vel1.x);
            it1->setPosition(pos1);
            it1->setOrientation(vel1);
            it1->etourdirPendant(sf::seconds(1.0f));
            break;
        }
        if (bounds1.top < bords.top)
        {
            pos1.y = bords.top + 0.5f * bounds1.height + 1.0f;
            vel1.y = fabs(vel1.y);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            it1->etourdirPendant(sf::seconds(1.0f));
            break;
        }
        if (bords.top + bords.height < bounds1.top + bounds1.height)
        {
            pos1.y = bords.top + bords.height - 0.5f * bounds1.height - 1.0f;
            vel1.y = -fabs(vel1.y);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            it1->etourdirPendant(sf::seconds(1.0f));
            break;
        }

        for (auto it2 = bestioles.begin(); it2 != it1; ++it2)
        {
            if (auto col = it1->testCollision(it2->getShape()))
            {
                auto pos2 = it2->getPosition();
                auto vel2 = it2->getVelocity();

                auto const compNormale1 = col.normale * Util::dot(col.normale, vel1);
                auto const compNormale2 = col.normale * Util::dot(col.normale, vel2);

                if (Util::dot(col.normale, vel1) < 0.0f)
                {
                    vel1 -= 2.0f * compNormale1;
                }

                if (Util::dot(col.normale, vel2) > 0.0f)
                {
                    vel2 -= 2.0f * compNormale2;
                }

                pos1 += col.normale * timeStep.asSeconds();
                pos2 -= col.normale * timeStep.asSeconds();

                it1->setPosition(pos1);
                it2->setPosition(pos2);
                it1->setRotation(Util::angle(vel1));
                it2->setRotation(Util::angle(vel2));
                it1->etourdirPendant(sf::seconds(1.0f));
                it2->etourdirPendant(sf::seconds(1.0f));

                break;
            }
        }
    }
}

void
Milieu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rectangleShape{ { bords.width, bords.height } };
    rectangleShape.setPosition(bords.left, bords.top);
    rectangleShape.setFillColor(sf::Color::White);
    target.draw(rectangleShape);

    for (auto const& bestiole : bestioles)
    {
        target.draw(bestiole, states);
    }
}

sf::Vector2f
Milieu::getTaille() const
{
    return { bords.width, bords.height };
}
