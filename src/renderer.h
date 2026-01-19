#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "constants.h"
#include "map.h"
#include <math.h>
#include "player.h"
#include "raycaster.h"


bool initRenderer(SDL_Renderer **renderer, SDL_Window **window);
void render(SDL_Renderer *renderer, Player *player);
void destroyRenderer(SDL_Renderer *renderer, SDL_Window *window);

#endif
