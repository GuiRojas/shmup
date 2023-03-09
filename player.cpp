#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "player.h"
#include "bullet.h"

#define imgN_path "img/mano.png"
#define imgL_path "img/manoL.png"
#define imgR_path "img/manoR.png"
#define bullet_path "img/mano.png"

enum imgState{
	IMG_NORMAL,
	IMG_LEFT,
	IMG_RIGHT,
	IMG_TOTAL
};

Player::Player(int nx, int ny){
	this->hp = 3;
	this->x = nx;
	this->y = ny;
	this->w = 30;
	this->h = 60;
	this->spd = 12;
	this->fspd = 6;
	this->img = NULL;
	this->imgs[IMG_TOTAL];
	this->focused = false;
	this->power = 100;
}

Player::~Player(){
	for (int i = 0; i < IMG_TOTAL; ++i){
		SDL_DestroyTexture(this->imgs[i]);
		this->imgs[i] = NULL;
	}
	this->x = NULL;
	this->y = NULL;
	this->w = NULL;
	this->h = NULL;
	this->spd = NULL;
	this->img = NULL;
	this->power = NULL;
}

int Player::getX(){
	return this->x;
}
int Player::getY(){
	return this->y;
}
int Player::getW(){
	return this->w;
}
int Player::getH(){
	return this->h;
}
int Player::getSpd(){
	return this->spd;
}
int Player::getHP(){
	return this->hp;
}

SDL_Texture* Player::getTexture(){
	return this->img;
}

SDL_Rect Player::getHitbox(){
	int size = 15;

	SDL_Rect plHb = {
		this->getX()+(this->getW()/2)-(size/2),
		this->getY()+(this->getH()/2)-(size/2),
		size,
		size
	};
	return plHb;
}

bool Player::loadImg(SDL_Renderer* renderer){
	SDL_Surface* loadedSurface = IMG_Load(imgN_path);
	this->imgs[IMG_NORMAL] = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load(imgL_path);
	this->imgs[IMG_LEFT] = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	loadedSurface = IMG_Load(imgR_path);
	this->imgs[IMG_RIGHT] = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);

	this->img = this->imgs[IMG_NORMAL];

	return true;
}

void Player::render(SDL_Renderer* renderer){
	SDL_Rect renderQuad = {
		this->x,
		this->y,
		this->w,
		this->h
	};

	SDL_RenderCopy(renderer, this->img, NULL, &renderQuad);
}

void Player::takeDamage(){
	this->hp--;
	for (int i = 0; i < IMG_TOTAL; ++i){
		SDL_SetTextureAlphaMod(this->imgs[i], 75);
	}
	this->power-=100;
	if(this->power < 100){
		this->power = 100;
	}
}
void Player::undamaged(){
	for (int i = 0; i < IMG_TOTAL; ++i){
		SDL_SetTextureAlphaMod(this->imgs[i], 255);
	}

}

void Player::moveL(){
	if(this->focused){
		this->x -= this->fspd;
	} else {
		this->x -= this->spd;
	}
	this->img = this->imgs[IMG_LEFT];
}

void Player::moveR(){
	if(this->focused){
		this->x += this->fspd;
	} else {
		this->x += this->spd;
	}
	this->img = this->imgs[IMG_RIGHT];
}

void Player::moveU(){
	if(this->focused){
		this->y -= this->fspd;
	} else {
		this->y -= this->spd;
	}
}

void Player::moveD(){
	if(this->focused){
		this->y += this->fspd;
	} else {
		this->y += this->spd;
	}
}
void Player::moveNot(){
	this->img = this->imgs[IMG_NORMAL];
}


std::vector<Bullet*> Player::shoot(SDL_Renderer* renderer){
	std::vector<Bullet*> b;

	Bullet* ba = new Bullet(this->x-30, this->y+30, 30, 30, 0, -20, bullet_path);

	Bullet* bb = new Bullet(this->x+this->w, this->y+30, 30, 30, 0, -20, bullet_path);

	b.push_back(ba);
	b.push_back(bb);

	if (this->power>600){
		this->power=600;
		Bullet* bx = new Bullet(this->x+(this->w/2)-10, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)-60, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+40, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);		
		bx = new Bullet(this->x+(this->w/2)-90, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+70, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);

	} else if (this->power>=500){
		Bullet* bx = new Bullet(this->x+(this->w/2)-30, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+10, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+40, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)-70, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		
	} else if (this->power>=400){
		Bullet* bx = new Bullet(this->x+(this->w/2)-10, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)-60, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+40, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		
	} else if (this->power>=300){
		Bullet* bx = new Bullet(this->x+(this->w/2)-30, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
		bx = new Bullet(this->x+(this->w/2)+10, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
	} else if (this->power>=200){
		Bullet* bx = new Bullet(this->x+(this->w/2)-10, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
		b.push_back(bx);
	}

	// int xb = ((int)this->power/100)-1;
	// if(xb>0){
	// 	int chunk = (int)((this->w+100)/xb);
	// 	for(int i=0;i<xb;++i){
	// 		int xx = this->x+(i*chunk)-50;
	// 		Bullet* bx = new Bullet(xx, this->y+this->h+30, 20, 20, 0, -20, bullet_path);
	// 		bx->init(renderer);
	// 		b.push_back(bx);
	// 	}
	// }

	for(int i=0;i<b.size();++i){
		b[i]->init(renderer);
	}

	return b;
}