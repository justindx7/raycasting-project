#include "raycaster.h"

RayCastResult castRay(Player *player, float angle) {
    RayCastResult rayCastResult;

    float dx = cos(angle);
    float dy = sin(angle);

    int mapX = (int)player->centerX / BLOCK_WIDTH;
    int mapY = (int)player->centerY / BLOCK_HEIGHT;

    // Distance to nearest whole block
    float dDistX = fabsf(BLOCK_WIDTH / dx);
    float dDistY = fabsf(BLOCK_HEIGHT / dy);

    float sideDistX, sideDistY;
    float stepX, stepY;

    if (dx < 0) {
      stepX = -1;
      sideDistX = (((float)player->centerX / BLOCK_WIDTH) - mapX) * dDistX;
    } else {
      stepX = 1;
      float tmp = (float)player->centerX / BLOCK_WIDTH;
      sideDistX = ((float)mapX + 1.f - tmp) * dDistX;
    }

    if (dy < 0) {
      stepY = -1;
      sideDistY = (((float)player->centerY / BLOCK_HEIGHT) - mapY) * dDistY;
    } else {
      stepY = 1;
      float tmp = (float)player->centerY / BLOCK_HEIGHT;
      sideDistY = ((float)mapY + 1.f - tmp) * dDistY;
    }

    rayCastResult.distance = 0;
    bool hit = false;
    while (!hit) {
      if (sideDistX < sideDistY) {
        sideDistX += dDistX;
        mapX += stepX;
        rayCastResult.distance = (sideDistX - dDistX);
        rayCastResult.side = 0;
      } else {
        sideDistY += dDistY;
        mapY += stepY;
        rayCastResult.distance = (sideDistY - dDistY);
        rayCastResult.side = 1;
      }
      hit = isWall(mapX, mapY);
    }

    rayCastResult.x = player->centerX + (dx * rayCastResult.distance);
    rayCastResult.y = player->centerY + (dy * rayCastResult.distance);

    return rayCastResult;
}
