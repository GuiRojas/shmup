#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#include "bullet.h"

#define PI 3.141592653589793238463

Bullet::Bullet(float x, float y, int w, int h, float spdx, float spdy, std::string img_path){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->spdy = spdy;
	this->spdx = spdx;
	this->img_path = img_path;
	this->img = NULL;
	this->frames = 0;
	this->shouldRotate = true;
	rotate();
}

void Bullet::free(){
	SDL_DestroyTexture(this->img);
	this->x = NULL;
	this->y = NULL;
	this->d = NULL;
	this->w = NULL;
	this->h = NULL;
	this->spdx = NULL;
	this->spdy = NULL;
	this->img = NULL;
	this->shouldRotate = NULL;
}

void Bullet::init(SDL_Renderer* renderer){
	SDL_Surface* loadedSurface = IMG_Load(this->img_path.c_str());
	if( loadedSurface == NULL ){
		printf("Unable to load bullet image %s! SDL_image Error: %s\n", this->img_path.c_str(), IMG_GetError());
		return;
	}
	this->img = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if(this->img == NULL){
		printf( "Unable to optimize bullet image %s! SDL Error: %s\n", this->img_path.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);

	this->move = [this]{
	};
}

int Bullet::getX(){
	return (int)this->x;
}
int Bullet::getY(){
	return (int)this->y;
}
int Bullet::getW(){
	return this->w;
}
int Bullet::getH(){
	return this->h;
}
int Bullet::getD(){
	return this->d;
}
std::string Bullet::getImgPath(){
	return this->img_path;
}

void Bullet::render(SDL_Renderer* renderer){
	update();
	rotate();
	this->frames++;

	SDL_Rect renderQuad = {
		this->x,
		this->y,
		this->w,
		this->h
	};

	SDL_RenderCopyEx(renderer, this->img, NULL, &renderQuad, this->d, NULL, SDL_FLIP_NONE);
}

void Bullet::update(){
	this->x += this->spdx;
	this->y += this->spdy;
}

void Bullet::rotate(){
	if(!this->shouldRotate){
		return;
	}

	if(this->x == 0 && this->y == 0){
		return;
	}
	double r = atan2(-this->spdy, -this->spdx);
	this->d = r*(180.0/PI)-90;
}

void Bullet::fromAngle(float spd){
	float a = (this->d*PI)/180;

	this->spdx = spd*cos(a);
	this->spdy = -spd*sin(a);
}