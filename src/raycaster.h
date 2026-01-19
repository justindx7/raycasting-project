#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "player.h"
#include "constants.h"
#include <math.h>
#include "map.h"

typedef struct {
    float distance;
    float x;
    float y;
    bool side;
} RayCastResult;

RayCastResult castRay(Player *p, float angle);

#endif
