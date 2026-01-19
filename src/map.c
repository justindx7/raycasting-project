#include "map.h"


bool isWall(int mapX, int mapY) {
    int mapIndex = mapY * LEVEL_WIDTH + mapX;
      if(mapIndex >= 0 && mapIndex < lvlArraySize) {
          if(level[mapIndex]){
              return true;
          }
      } else {
          return true;
      }
    return false;
}
