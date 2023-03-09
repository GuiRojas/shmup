#ifndef ENEMY
#define ENEMY

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <functional>
#include "bullet.h"
#include "drop.h"

class Enemy{	
	public:
		Enemy(float x, float y, int w, int h, float sx, float sy, int hp, std::string img_path);
		void free();

		std::function<void()> move;
		std::function<std::vector<Bullet*>(SDL_Renderer*)> shoot;

		int getX();
		int getY();
		int getW();
		int getH();
		int getS();
		int getSpd();
		SDL_Texture* getTexture();

		void init(SDL_Renderer* renderer);
		void render(SDL_Renderer* renderer);

		void takeDamage();

		std::vector<Drop*> drops;

	// private stuff that needs to be public so dynamic move() function works properly
		float x;
		float y;
		int w;
		int h;
		float spdx;
		float spdy;
		int hp;
		int stage;
		int maxhp;
		int frames;

		bool boss;
		bool shouldDie;

		SDL_Texture* img;
		std::string img_path;
};



#endif
