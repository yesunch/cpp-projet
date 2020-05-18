//
// Created by quentin on 13/05/2020.
//

#ifndef BESTIOLES_ESPECE_H
#define BESTIOLES_ESPECE_H

#include <functional>

#include "capteur/Capteur.h"
#include "Dissimulation.h"
#include "Locomotion.h"
#include "Protection.h"

struct Espece
{
    float longueur;
    float epaisseur;
    sf::Time dureeDeVie;

    Capteur::Ptr capteur;

    Locomotion::Ptr locomotion;
    Protection::Ptr protection;
    Dissimulation::Ptr dissimulation;

    Espece cloner() const;
};

#endif // BESTIOLES_ESPECE_H
