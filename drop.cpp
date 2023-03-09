#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "drop.h"

Drop::Drop(int w, int h, std::string img_path){
	this->x = 0; // set when enemy dies
	this->y = 0; // or instantly for bosses
	this->w = w;
	this->h = h;
	this->spdx = 0;
	this->spdy = 0;
	this->img_path = img_path;
	this->frames = 0;
}

void Drop::free(){
	SDL_DestroyTexture(this->img);
	this->x = NULL;
	this->y = NULL;
	this->w = NULL;
	this->h = NULL;
	this->spdx = NULL;
	this->spdy = NULL;
	this->img = NULL;
	this->frames = NULL;
}

void Drop::init(SDL_Renderer* renderer){
	SDL_Surface* loadedSurface = IMG_Load(this->img_path.c_str());
	if( loadedSurface == NULL ){
		printf("Unable to load drop image %s! SDL_image Error: %s\n", this->img_path.c_str(), IMG_GetError());
		return;
	}
	this->img = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if(this->img == NULL){
		printf( "Unable to optimize drop image %s! SDL Error: %s\n", this->img_path.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
}

int Drop::getX(){
	return this->x;
}
int Drop::getY(){
	return this->y;
}
int Drop::getW(){
	return this->w;
}
int Drop::getH(){
	return this->h;
}
std::string Drop::getImgPath(){
	return this->img_path;
}

void Drop::render(SDL_Renderer* renderer){
	this->frames++;

	SDL_Rect renderQuad = {
		this->x,
		this->y,
		this->w,
		this->h
	};

	SDL_RenderCopy(renderer, this->img, NULL, &renderQuad);
}

void Drop::move(){
	if(this->spdy <= 6 && this->frames % 4 == 0){
		this->spdy++;
	}
	this->y+=spdy;
}