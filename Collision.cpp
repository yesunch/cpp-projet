//
// Created by quentin on 14/05/2020.
//

#include "Collision.h"

Collision::Collision(bool happened)
  : happened{ happened }
{
}

Collision::operator bool() const
{
    return happened;
}
