#ifndef BULLET
#define BULLET

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <functional>

class Bullet{
	public:
		Bullet(float x, float y, int w, int h, float spdx, float spdy, std::string img_path);
		// DO NOT USE DESTRUCTOR. IT **WILL** MESS THINGS UP
		void free();
		void init(SDL_Renderer* renderer);

		std::function<void()> move;

		int getX();
		int getY();
		int getW();
		int getH();
		int getD();
		std::string getImgPath();

		void update();
		void rotate();
		void fromAngle(float spd);

		void render(SDL_Renderer* renderer);

		float x;
		float y;
		float d; // stored as degrees
		float spdx;
		float spdy;
		int frames;
		bool shouldRotate;
	private:
		int w;
		int h;


		std::string img_path;
		SDL_Texture* img;

};

#endif
