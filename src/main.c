#include <stdint.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "map.h"
#include "player.h"
#include "raycaster.h"
#include "renderer.h"


// Pointers to our window and renderer
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool running = false;
int lastFrame = 0;

RotationDirection rotDir = ROT_NONE;
MoveDirection moveDir = MOVE_NONE;
Player player;


bool init(void) {
    if(!initRenderer(&renderer, &window)) {return false;}
    initPlayer(&player, WINDOW_WIDTH >> 1, (WINDOW_HEIGHT >> 1) - 20);
    return true;
}

void processInput(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    // handle quitting window
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN) {
      // if escape is pressed quit
      switch (event.key.key) {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_W:
            moveDir = MOVE_UP;
            break;
        case SDLK_S:
            moveDir = MOVE_DOWN;
            break;
        case SDLK_A:
            rotDir = ROT_LEFT;
            break;
        case SDLK_D:
            rotDir = ROT_RIGHT;
            break;
      }
    }

    if (event.type == SDL_EVENT_KEY_UP) {
      // if escape is pressed quit
      switch (event.key.key) {
        case SDLK_W:
        case SDLK_S:
            moveDir = MOVE_NONE;
            break;

        case SDLK_A:
        case SDLK_D:
            rotDir = ROT_NONE;
            break;
      }
    }

  }
}

void update(void) {
    float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.f;
    lastFrame = SDL_GetTicks();

    if(rotDir != ROT_NONE) {
        rotatePlayer(&player, deltaTime, (int)rotDir);
    }

    if(moveDir != MOVE_NONE) {
        movePlayer(&player, deltaTime, (int)moveDir);
    }
}

void destroy(void) {
    destroyRenderer(renderer,window);
}

int main(void) {
  running = init();

  while (running) {
    processInput();
    update();
    render(renderer, &player);
  }

  destroy();
  return 0;
}
