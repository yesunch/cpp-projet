//
// Created by quentin on 13/05/2020.
//

#include "../include/ObservationBestiole.h"

bool
ObservationBestiole::operator<(const ObservationBestiole& autreObs) const
{
    return distanceToBestiole < autreObs.distanceToBestiole;
}
