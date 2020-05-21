//
// Created by quentin on 13/05/2020.
//

#include "../include/Milieu.h"
#include "../include/GenerateurAleatoire.h"
#include "../include/Util.h"
#include "../include/comportement/ComportementGregaire.h"

#include <map>

#include <SFML/Graphics.hpp>

Milieu::Milieu(sf::FloatRect bords)
  : bords{ bords }
  , nextBestioleId{ 0 }
  , tempsAvantProchaineNaissance{ sf::seconds(1.0f / TAUX_NATALITE) }
{
}

void
Milieu::initialiserPopulation(PopulationFactory& populationFactory)
{
    bestioles = populationFactory.creerPopulation(bords);
}

/**
 * Update all of the bestioles one timeStep forward.
 * Decrease the waiting time for next round of bestiole creation. Check each bestiole whether it
 * needs to be cloned or it's already dead. Clone or delete the bestioles if they need to be
 * processed.
 *
 * @param populationFactory
 * @param timeStep
 */
void
Milieu::update(PopulationFactory& populationFactory, sf::Time timeStep)
{
    // Make new birth bestiole waits one timeStep
    if (tempsAvantProchaineNaissance > sf::Time::Zero)
    {
        tempsAvantProchaineNaissance -= timeStep;
    }
    else
    {
        tempsAvantProchaineNaissance = sf::seconds(1.0f / TAUX_NATALITE);
        bestioles.emplace_back(populationFactory.creerBestiole(bords));
    }

    std::map<BestioleId, std::vector<ObservationBestiole>> bestiolesObservees;
    std::vector<BestioleId> bestiolesSupprimees;
    std::vector<BestioleId> bestiolesClonees;

    // get observable neighbors for each bestiole by its own capteur
    for (auto& bestiole : bestioles)
    {
        auto const& capteur = bestiole.getCapteur();
        if (capteur)
        {
            bestiolesObservees.insert(
                { bestiole.getId(),
                  capteur->capter(bestioles, bestiole.getPosition(), bestiole.getOrientation()) });
        }
    }

    // Give seCloner and mourrir functions to each bestiole, let it use them by its need
    for (auto& bestiole : bestioles)
    {
        auto const seCloner = [&bestiolesClonees, id = bestiole.getId()]() {
            bestiolesClonees.push_back(id);
        };

        auto const mourrir = [&bestiolesSupprimees, id = bestiole.getId()]() {
            bestiolesSupprimees.push_back(id);
        };

        bestiole.update(bestiolesObservees[bestiole.getId()], bords, seCloner, mourrir, timeStep);
    }

    handleCollisions(timeStep, bestiolesSupprimees);
    // Clone the bestioles which have the same Id with the Id saved in vector<BestioleId>
    // bestiolesClonees
    for (auto const idBestioleAcloner : bestiolesClonees)
    {
        // Find the corresponding bestiole in the list of bestiole which needs to be cloned
        auto bestioleIt = std::find_if(
            bestioles.cbegin(), bestioles.cend(), [idBestioleAcloner](Bestiole const& b) {
                return b.getId() == idBestioleAcloner;
            });

        // Clone the bestiole and insert it into the bestiole list
        if (bestioleIt != bestioles.cend())
        {
            bestioles.emplace_back(populationFactory.clonerBestiole(*bestioleIt));
        }
    }
    
    // Sort bestioles, remove_if puts all bestioles which exist in bestiolesSupprimees at the end of the bestioles vector
    // newLastBestioleIt is an iterator to the beginning of the needed to be deleted bestiole of the vector
    auto const newLastBestioleIt = std::remove_if(
        bestioles.begin(), bestioles.end(), [&bestiolesSupprimees](Bestiole const& b) {
            auto idIt =
                std::find(bestiolesSupprimees.cbegin(), bestiolesSupprimees.cend(), b.getId());
            return idIt != bestiolesSupprimees.cend();
        });

    // delete those bestioles between newLastBestioleIt and the end of bestioles.cend() 
    // (bestiolesSupprimees) has been sorted in this range
    bestioles.erase(newLastBestioleIt, bestioles.cend());
}

/**
 * Process the case of collision between two bestioles. Add the dead bestiole into the dead
 * bestioles list if there's one get killed in the collision
 * @param timeStep
 * @param bestiolesSupprimees
 */
void
Milieu::handleCollisions(sf::Time timeStep, std::vector<BestioleId>& bestiolesSupprimees)
{
    for (auto it1 = bestioles.begin(); it1 != bestioles.end(); ++it1)
    {
        auto pos1 = it1->getPosition();
        auto vel1 = it1->getVelocity();
        auto const bounds1 = it1->getShape().getGlobalBounds();
        // Check if there's a collision between the bestiole and the global boundary
        // Collision on the left side of global bounday
        if (bounds1.left < bords.left)
        {
            pos1.x = bords.left + 0.5f * bounds1.width + 1.0f;
            vel1.x = fabs(vel1.x);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            continue;
        }
        // Collision on the right side of global bounday
        if (bords.left + bords.width < bounds1.left + bounds1.width)
        {
            pos1.x = bords.left + bords.width - 0.5f * bounds1.width - 1.0f;
            vel1.x = -fabs(vel1.x);
            it1->setPosition(pos1);
            it1->setOrientation(vel1);
            continue;
        }
        // Collision on the top of global bounday
        if (bounds1.top < bords.top)
        {
            pos1.y = bords.top + 0.5f * bounds1.height + 1.0f;
            vel1.y = fabs(vel1.y);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            continue;
        }
        // Collision on the bottom of global bounday
        if (bords.top + bords.height < bounds1.top + bounds1.height)
        {
            pos1.y = bords.top + bords.height - 0.5f * bounds1.height - 1.0f;
            vel1.y = -fabs(vel1.y);
            it1->setPosition(pos1);
            it1->setRotation(Util::angle(vel1));
            continue;
        }
        // Check if there's a collision among bestioles
        for (auto it2 = bestioles.begin(); it2 != it1; ++it2)
        {
            // If the collision happens, reset the new position and rotation of two bestioles
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

                pos1 += col.normale * col.overlap;
                pos2 -= col.normale * col.overlap;

                auto& genAlea = GenerateurAleatoire::getSingleton();

                auto const detruire1 = genAlea.uniformReal(0.0f, 1.0f);
                if (detruire1 < Bestiole::VULNERABILITE_CHOC / it1->getCoeffResistance())
                {
                    bestiolesSupprimees.push_back(it1->getId());
                }

                auto const detruire2 = genAlea.uniformReal(0.0f, 1.0f);
                if (detruire2 < Bestiole::VULNERABILITE_CHOC / it2->getCoeffResistance())
                {
                    bestiolesSupprimees.push_back(it2->getId());
                }

                it1->setPosition(pos1);
                it2->setPosition(pos2);
                it1->setRotation(Util::angle(vel1));
                it2->setRotation(Util::angle(vel2));

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
