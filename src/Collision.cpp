
#include "../include/Collision.h"

Collision::Collision(bool happened)
  : happened{ happened }
{
}

Collision::operator bool() const
{
    return happened;
}
