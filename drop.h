#ifndef DROP
#define DROP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Drop{
	public:
		Drop(int w, int h, std::string img_path);
		// DO NOT USE DESTRUCTOR. IT **WILL** MESS THINGS UP
		void free();
		void init(SDL_Renderer* renderer);

		void move();

		int getX();
		int getY();
		int getW();
		int getH();
		std::string getImgPath();

		void render(SDL_Renderer* renderer);

		int x;
		int y;
		int frames;
		int spdx;
		int spdy;
	private:
		int w;
		int h;

		std::string img_path;
		SDL_Texture* img;

};

#endif
