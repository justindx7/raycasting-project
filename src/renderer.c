#include "renderer.h"
#include "raycaster.h"

bool initRenderer(SDL_Renderer **renderer, SDL_Window **window) {
    // init SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;    
    }
    // create window and renderer
    if (!SDL_CreateWindowAndRenderer(NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0, window, renderer)) {
        printf("Error creating Window/Renderer: %s\n", SDL_GetError());
        return false;    
    }
    if(!SDL_SetRenderVSync(*renderer,1)){
        printf("VSync not supported: %s\n", SDL_GetError());
        return false;    
    }
    return true;
}

static void renderRay(SDL_Renderer *renderer, float startX, float startY,float endX, float endY) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
  SDL_RenderLine(renderer, startX, startY, endX, endY);
}

static void renderWallSlice(SDL_Renderer *renderer, Player *player, RayCastResult *ray, float rayAngle, int i) {
    //fix fisheye effect
    float distance = ray->distance * cos(player->angle - rayAngle);

    // draw fake perspective if blocks are futher away draw them as a smaller line
    int lineHeight = (int)((BLOCK_HEIGHT * WINDOW_HEIGHT) / distance);
    // if blocks are right infront of the player they can only be as big as the screen size
    if (lineHeight > WINDOW_HEIGHT) {
      lineHeight = WINDOW_HEIGHT;
    }

    int lineStart = (WINDOW_HEIGHT / 2) - (lineHeight / 2);
    int lineEnd = (WINDOW_HEIGHT / 2) + (lineHeight / 2);
    if(ray->side) {
        SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    }
    SDL_RenderLine(renderer, i, lineStart, i, lineEnd);
}

static void renderRays(SDL_Renderer *renderer, Player *player) {
  int rayAmount = WINDOW_WIDTH;
  float angleIncr = FOV / rayAmount;
  float startAngle = player->angle - (FOV / 2.f);
  for (int i = 0; i < rayAmount; i++) {

    float rayAngle = startAngle + (i * angleIncr);
    RayCastResult ray = castRay(player, rayAngle);

    renderWallSlice(renderer, player, &ray, rayAngle, i);
    //renderRay(renderer,player->centerX,player->centerY, ray.x,ray.y);
  }
}

static void renderMap(SDL_Renderer *renderer) {
  for (uint8_t i = 0; i < lvlArraySize; i++) {
    if (level[i]) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    int blockX = (i % LEVEL_WIDTH) * BLOCK_WIDTH;
    int blockY = (i / LEVEL_WIDTH) * BLOCK_HEIGHT;
    SDL_FRect rect = {blockX, blockY, (BLOCK_WIDTH) - 1, (BLOCK_HEIGHT) - 1};
    SDL_RenderFillRect(renderer, &rect);
  }
}

static void renderPlayer(SDL_Renderer *renderer, Player *player) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_FRect playerRect = {player->x, player->y, player->width, player->height};
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_RenderLine(renderer, player->centerX, player->centerY, player->centerX + player->dx * 5, player->centerY + player->dy * 5);
}

void render(SDL_Renderer *renderer, Player *player) {
    SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
    SDL_RenderClear(renderer);
    renderRays(renderer,player);
    //renderMap(renderer);
    //renderPlayer(renderer,player);

    SDL_RenderPresent(renderer);
}


void destroyRenderer(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
