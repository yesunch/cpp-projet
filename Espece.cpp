//
// Created by quentin on 13/05/2020.
//

#include "Espece.h"

Espece
Espece::cloner() const
{
    return { .length = length,
             .thickness = thickness,
             .capteur = capteur->cloner(),
             .locomotion = locomotion->cloner(),
             .protection = protection->cloner(),
             .dissimulation = dissimulation->cloner() };
}
