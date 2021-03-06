
#include "../include/Espece.h"

Espece
Espece::cloner() const
{
    return { .longueur = longueur,
             .epaisseur = epaisseur,
             .dureeDeVie = dureeDeVie,
             .capteur = capteur ? capteur->cloner() : nullptr,
             .locomotion = locomotion ? locomotion->cloner() : nullptr,
             .protection = protection ? protection->cloner() : nullptr,
             .dissimulation = dissimulation ? dissimulation->cloner() : nullptr };
}
