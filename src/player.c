#include "player.h"

static const float PI_2 = 2.f * M_PI;

void initPlayer(Player *player, float x, float y) {
    player->x = x;
    player->y = y;
    player->width = 10.f;
    player->height = 10.f;
    player->centerX = x + (player->width / 2);
    player->centerY = y + (player->height / 2);
    player->angle = 0.f;
    player->dx = cos(player->angle);
    player->dy = sin(player->angle);
    player->rotationSpeed = 2.f;
    player->moveSpeed = 200.f;

}

void rotatePlayer(Player *player, float deltaTime, int direction) {
    player->angle += direction * player->rotationSpeed * deltaTime;
    if (player->angle > PI_2) {player->angle = 0.f;}
    if (player->angle < 0.f) {player->angle = PI_2;}
}


static bool isWalkable(float x, float y) {
    int mapX = ((int)x / BLOCK_WIDTH);
    int mapY = ((int)y / BLOCK_HEIGHT);

    return !isWall(mapX, mapY);
}

void movePlayer(Player *player, float deltaTime, int direction) {
    player->dx = cos(player->angle) * direction * player->moveSpeed * deltaTime;
    player->dy = sin(player->angle) * direction * player->moveSpeed * deltaTime;

    int paddingX = player->dx > 0 ? 10 : 0;
    int paddingY = player->dy > 0 ? 10 : 0;

    if(isWalkable((player->x + player->dx + paddingX), player->y)) {
        player->x += player->dx;

        player->centerX = player->x + (player->width / 2);
    }

    if(isWalkable(player->x, (player->y + player->dy + paddingY))) {
        player->y += player->dy;
        player->centerY = player->y + (player->height / 2);
    }
}

