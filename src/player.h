#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <stdbool.h>
#include "constants.h"
#include "map.h"

typedef struct {
    float x;
    float y;
    float centerX;
    float centerY;
    float width;
    float height;
    float angle;
    float dx;
    float dy;
    float moveSpeed;
    float rotationSpeed;
}Player;

typedef enum {
    ROT_LEFT = -1,
    ROT_RIGHT = 1,
    ROT_NONE = 0
}RotationDirection;

typedef enum {
    MOVE_UP = 1,
    MOVE_DOWN = -1,
    MOVE_NONE = 0
}MoveDirection;

void initPlayer(Player *player, float x, float y);
void rotatePlayer(Player *player, float deltaTime, int direction);
void movePlayer(Player *player, float deltaTime, int direction);
void updatePlayer(Player *player, float deltaTime);


#endif
