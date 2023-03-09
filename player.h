#ifndef PLAYER
#define PLAYER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "bullet.h"

class Player{
	public:
		Player(int x, int y);
		~Player();

		int getX();
		int getY();
		int getW();
		int getH();
		int getSpd();
		int getHP();
		SDL_Texture* getTexture();
		SDL_Rect getHitbox();

		bool loadImg(SDL_Renderer* renderer);
		void render(SDL_Renderer* renderer);

		void takeDamage();
		void undamaged();

		void moveL();
		void moveR();
		void moveU();
		void moveD();
		void moveNot();
		std::vector<Bullet*> shoot(SDL_Renderer* renderer);

		bool focused;
		int hp;
		int power;
	private:
		int x;
		int y;
		int w;
		int h;
		int spd;
		int fspd;
		int state;

		enum imgState{
			IMG_NORMAL,
			IMG_LEFT,
			IMG_RIGHT,
			IMG_TOTAL
		};

		SDL_Texture* img;
		SDL_Texture* imgs[IMG_TOTAL];
};

#endif
