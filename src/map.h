#ifndef MAP_H
#define MAP_H
#include "constants.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


static uint8_t level[LEVEL_WIDTH * LEVEL_HEIGHT] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,
    1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};


const static int lvlArraySize = sizeof(level) / sizeof(level[-1]);


bool isWall(int mapX, int mapY);

#endif
