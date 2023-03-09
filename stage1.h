#ifndef STAGE1
#define STAGE1

#include <utility>
#include <vector>
#include <SDL2/SDL.h>
#include "enemy.h"

std::vector<std::pair<int,Enemy*>> load_stage1(SDL_Renderer* gRenderer, std::vector<Bullet*> *bullets, Player *player);

#endif