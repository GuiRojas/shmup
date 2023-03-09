#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <functional>
#include "enemy.h"
#include "bullet.h"
#include "drop.h"


Enemy::Enemy(float x, float y, int w, int h, float sx, float sy, int hp, std::string img_path){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->spdx = sx;
	this->spdy = sy;
	this->img_path = img_path;
	this->hp = hp;
	this->maxhp = hp;
	this->stage = 0;
	this->shouldDie = false;
	this->boss = false;
	this->frames = 0;
	this->drops = {};
}

void Enemy::free(){	
	SDL_DestroyTexture(this->img);
	this->x = NULL;
	this->y = NULL;
	this->w = NULL;
	this->h = NULL;
	this->spdx = NULL;
	this->spdy = NULL;
	this->img = NULL;
	this->hp = NULL;
	this->maxhp = NULL;
	this->shouldDie = NULL;
	this->boss = NULL;
	this->frames = NULL;
}

void Enemy::init(SDL_Renderer* renderer){
	SDL_Surface* loadedSurface = IMG_Load(this->img_path.c_str());
	this->img = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
}

void Enemy::render(SDL_Renderer* renderer){
	this->frames++;

	SDL_Rect renderQuad = {
		this->x,
		this->y,
		this->w,
		this->h
	};

	SDL_RenderCopy(renderer, this->img, NULL, &renderQuad);
}

int Enemy::getX(){
	return this->x;
}
int Enemy::getY(){
	return this->y;
}
int Enemy::getW(){
	return this->w;
}
int Enemy::getH(){
	return this->h;
}
int Enemy::getS(){
	return this->stage;
}
SDL_Texture* Enemy::getTexture(){
	return this->img;
}

void Enemy::takeDamage(){
	this->hp--;
	if(this->hp <= 0){
		if (this->stage>0){
			this->hp = this->maxhp;
			this->stage--;
		}else{
			this->shouldDie = true;
			for(int i = 0; i < this->drops.size(); i++){
				this->drops[i]->x = this->x;
				this->drops[i]->y = this->y;
			}
		}
	}
}
