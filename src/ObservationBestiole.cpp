
#include "../include/ObservationBestiole.h"

bool
ObservationBestiole::operator<(const ObservationBestiole& autreObs) const
{
    return distanceToBestiole < autreObs.distanceToBestiole;
}
