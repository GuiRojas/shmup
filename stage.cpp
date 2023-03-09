#include <utility>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include "enemy.h"
#include "bullet.h"
#include "drop.h"

#define PI 3.141592653589793238463

typedef std::pair<int,Enemy*> pr;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;


std::vector<pr> load_stage1(SDL_Renderer* renderer, std::vector<Bullet*> *bullets){
	std::vector<pr> ret;

	// Enemy* t = new Enemy(0,200,100,100, 10, 0,  5, "img/mano.png");
	// t->init(renderer);
	// t->shoot = [t, bullets](SDL_Renderer* rnd){		
	// 	std::vector<Bullet*> b;
	// 	Bullet* ba = new Bullet(t->x-15, t->y+15, 15, 15, 0, 5, "img/mano.png");
	// 	ba->init(rnd);
	// 	ba->move = [ba](){
	// 	};
	// 	b.push_back(ba);
	// 	return b;
	// };

	// t->move = [t, renderer, bullets]{
	// 	t->x+=t->spdx;
	// 	if(t->x>=SCREEN_WIDTH){
	// 		t->shouldDie = true;
	// 	}
	// 	if(t->frames%5==0){
	// 		std::vector<Bullet*> b = t->shoot(renderer);
	// 		for (int i = 0; i < b.size(); ++i){
	// 			bullets->push_back(b[i]);
	// 		}
	// 	}
	// };

	// Drop* d = new Drop(50, 50, "img/mano.png");
	// t->drops.push_back(d);

	// ret.push_back(std::make_pair(100, t));

	// Enemy* t2 = new Enemy(0,200,100,100, 15, 0, 5, "img/mano.png");
	// t2->init(renderer);
	// t2->move = [t2, renderer, bullets]{
	// 	t2->x+=t2->spdx;
	// 	if(t2->x>=SCREEN_WIDTH){
	// 		t2->shouldDie = true;
	// 	}
	// 	if(t2->frames%5==0){
	// 		std::vector<Bullet*> b = t2->shoot(renderer);
	// 		for (int i = 0; i < b.size(); ++i){
	// 			bullets->push_back(b[i]);
	// 		}
	// 	}
	// };
	// t2->shoot = [t2, bullets](SDL_Renderer* rnd){		
	// 	std::vector<Bullet*> b;
	// 	Bullet* ba = new Bullet(t2->x-15, t2->y+15, 15, 15, 0, 5, "img/mano.png");
	// 	ba->init(rnd);
	// 	ba->move = [ba](){
	// 	};
	// 	b.push_back(ba);
	// 	return b;
	// };
	// ret.push_back(std::make_pair(200, t2));

	// Enemy* t3 = new Enemy(100,300,100,100, 5, 0, 5, "img/mano.png");
	// t3->init(renderer);
	// t3->move = [t3, renderer, bullets]{
	// 	t3->x+=t3->spdx;
	// 	if(t3->x>=SCREEN_WIDTH){
	// 		t3->shouldDie = true;
	// 	}
	// 	if(t3->frames%5==0){
	// 		std::vector<Bullet*> b = t3->shoot(renderer);
	// 		for (int i = 0; i < b.size(); ++i){
	// 			bullets->push_back(b[i]);
	// 		}
	// 	}
	// };
	// t3->shoot = [t3, bullets](SDL_Renderer* rnd){		
	// 	std::vector<Bullet*> b;
	// 	Bullet* ba = new Bullet(t3->x-15, t3->y+15, 15, 15, 0, 5, "img/mano.png");
	// 	ba->init(rnd);
	// 	ba->move = [ba](){
	// 	};
	// 	b.push_back(ba);
	// 	return b;
	// };
	// ret.push_back(std::make_pair(300, t3));

	// Enemy* tb = new Enemy(600,200,100,100, 5, 0, 100, "img/mano.png");
	// tb->boss = true;
	// tb->stage = 4;
	// tb->init(renderer);
	// tb->move = [tb, renderer, bullets]{
	// 	if(tb->frames%2==0){return;}
	// 	std::vector<Bullet*> b = tb->shoot(renderer);
	// 	for (int i = 0; i < b.size(); ++i){
	// 		bullets->push_back(b[i]);
	// 	}	
	// };
	// tb->shoot = [tb](SDL_Renderer* rnd){
	// 	std::vector<Bullet*> b;

	// 	if(tb->stage == 4){
			
	// 	}else if(tb->stage == 3){
			
	// 	}else if(tb->stage == 2){
			
	// 	}else if(tb->stage == 1){
			
	// 	}else{
	// 		float o = sin(((tb->frames-90)*PI)/180)*500;
	// 		float inc = (360/6);

	// 		//printf("f %d\no %f", tb->frames, o);

	// 		for (float i = o; i<360+o; i+=inc){
	// 			float r = fmod(i, 360);
	// 			double an = (r*PI)/180;
	// 			float bx = (sin(an)*8);
	// 			float by = (cos(an)*8);

	// 			// printf("o %d\ni %f\nan %d\nbx %f\nby %f\n", o, i, an, bx, by);

	// 			Bullet* ba = new Bullet(tb->x+(tb->w/2), tb->y+(tb->h/2), 20, 20, bx, by, "img/mano.png");
	// 			ba->init(rnd);
	// 			ba->move = [ba](){
	// 			};
	// 			b.push_back(ba);		
	// 		}

	// 		return b;
	// 	}
	// };

	// ret.push_back(std::make_pair(0, tb));

	return ret;
}

