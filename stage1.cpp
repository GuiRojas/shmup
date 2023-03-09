#include <utility>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "drop.h"

#define PI 3.141592653589793238463

typedef std::pair<int,Enemy*> pr;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;


std::vector<pr> load_stage1(SDL_Renderer* renderer, std::vector<Bullet*> *bullets, Player *player){
	std::vector<pr> ret;

	// basic guys
	{
		#define s1_basic_shoot(tx) [tx, bullets](SDL_Renderer* rnd){\
			std::vector<Bullet*> b;\
			Bullet* ba = new Bullet(tx->x-30, tx->y+30, 30, 30, 0, 7, "img/mano.png");\
			Bullet* bb = new Bullet(tx->x+130, tx->y+30, 30, 30, 0, 7, "img/mano.png");\
			ba->init(rnd);\
			bb->init(rnd);\
			b.push_back(ba);\
			b.push_back(bb);\
			return b;\
		};
	
		#define s1_basic_move(tx, frame_div) [tx, renderer, bullets]{\
			if(tx->x>=SCREEN_WIDTH){\
				tx->shouldDie = true;\
			}else if(tx->frames>=60*5){\
				tx->y-=tx->spdy;\
				tx->spdy * 1.2;\
				if(tx->y<=-200){\
					tx->shouldDie = true;\
				}\
			}else if(tx->y <= SCREEN_HEIGHT*0.2){\
				tx->y+=tx->spdy;\
				tx->spdy * 0.9;\
			}else if(tx->frames%frame_div==0){ \
				std::vector<Bullet*> b = tx->shoot(renderer);\
				for (int i = 0; i < b.size(); ++i){\
					bullets->push_back(b[i]);\
				}\
			}\
		};
	
		Enemy* t1 = new Enemy(SCREEN_WIDTH/2-50,-100,100,100, 0, 10,  30, "img/mano.png");
		t1->init(renderer);
		t1->shoot = s1_basic_shoot(t1);
		t1->move = s1_basic_move(t1, 30);
		ret.push_back(std::make_pair(60, t1));
	
		Enemy* t2 = new Enemy(SCREEN_WIDTH*0.33-50,-100,100,100, 0, 10,  30, "img/mano.png");
		t2->init(renderer);
		t2->shoot = s1_basic_shoot(t2);
		t2->move = s1_basic_move(t2, 30);
		ret.push_back(std::make_pair(60*3, t2));
	
		Enemy* t3 = new Enemy(SCREEN_WIDTH*0.66-50,-100,100,100, 0, 10,  30, "img/mano.png");
		t3->init(renderer);
		t3->shoot = s1_basic_shoot(t3);
		t3->move = s1_basic_move(t3, 30);
		ret.push_back(std::make_pair(60*4, t3));
	}

	// less basic guys
	{
		#define s1_less_basic_shoot(tx) [tx, bullets, player](SDL_Renderer* rnd){\
			double r = atan2(-(tx->x-player->getX()), -(tx->y-player->getY()))*(180.0/PI)-90;\
			std::vector<Bullet*> b;\
			for (int i = -1; i < 2; ++i){\
				double adj = (1.0/PI)*(i*30);\
				Bullet* ba = new Bullet(tx->x+15, tx->y+45, 30, 30, 0, 0, "img/mano.png");\
				ba->init(rnd);\
				ba->d = r+adj;\
				ba->fromAngle(6);\
				b.push_back(ba);\
			}\
			return b;\
		};

		Enemy* tb1 = new Enemy(SCREEN_WIDTH*0.4-50,-100,100,100, 0, 10,  25, "img/mano.png");
		tb1->init(renderer);
		tb1->shoot = s1_less_basic_shoot(tb1);
		tb1->move = s1_basic_move(tb1, 30);
		ret.push_back(std::make_pair(60*7, tb1));

		Enemy* tb2 = new Enemy(SCREEN_WIDTH*0.6-50,-100,100,100, 0, 10,  25, "img/mano.png");
		tb2->init(renderer);
		tb2->shoot = s1_less_basic_shoot(tb2);
		tb2->move = s1_basic_move(tb2, 30);
		ret.push_back(std::make_pair(60*8, tb2));

	}

	// many guided guys
	{
		#define s1_single_guided_shoot(tx) [tx, bullets, player](SDL_Renderer* rnd){\
			std::vector<Bullet*> b;\
			Bullet* ba = new Bullet(tx->x+15, tx->y+45, 30, 30, 0, 0, "img/mano.png");\
			ba->init(rnd);\
			ba->d = atan2(-(tx->x-player->getX()), -(tx->y-player->getY()))*(180.0/PI)-90;\
			ba->fromAngle(6);\
			b.push_back(ba);\
			return b;\
		};

		for (int i = 1; i < 10; ++i){
			int tbx = (SCREEN_WIDTH/10)*i;
			Enemy* ntb = new Enemy(tbx-50,-100,100,100, 0, 10, 10, "img/mano.png");
			ntb->init(renderer);
			ntb->shoot = s1_single_guided_shoot(ntb);
			ntb->move = s1_basic_move(ntb, 15);
			ret.push_back(std::make_pair(60*12+(30*i), ntb));
		}
	}

	// cute lil miniboss
	{
		#define s1_accelerating_circular_shooting(tx) [tx, bullets](SDL_Renderer* rnd){\
			std::vector<Bullet*> b;\
			Bullet* ba = new Bullet(tx->x+100, tx->y+100, 30, 30, 0, 0, "img/mano.png");\
			ba->init(rnd);\
			ba->d = (tx->frames*13);\
			ba->fromAngle(0.75);\
			ba->move = [ba]{\
				ba->spdx+=ba->spdx*0.02;\
				ba->spdy+=ba->spdy*0.02;\
			};\
			b.push_back(ba);\
			return b;\
		};

		#define s1_miniboss_move(tx) [tx, renderer, bullets]{\
			if(tx->y>=SCREEN_WIDTH){\
				tx->shouldDie = true;\
			}else if(tx->frames>=60*10){\
				tx->y-=tx->spdy;\
				tx->spdy * 1.2;\
				if(tx->y<=-200){\
					tx->shouldDie = true;\
				}\
			}else if(tx->y <= SCREEN_HEIGHT*0.2){\
				tx->y+=tx->spdy;\
				tx->spdy * 0.9;\
			}else{\
				std::vector<Bullet*> b = tx->shoot(renderer);\
				for (int i = 0; i < b.size(); ++i){\
					bullets->push_back(b[i]);\
				}\
			}\
		};

		Enemy* tmnb = new Enemy(SCREEN_WIDTH/2-100,-100,200,200, 0, 10, 200, "img/mano.png");
		tmnb->init(renderer);
		tmnb->boss = true;
		tmnb->shoot = s1_accelerating_circular_shooting(tmnb);
		tmnb->move = s1_miniboss_move(tmnb);

		Drop* d = new Drop(50, 50, "img/mano.png");
		tmnb->drops.push_back(d);

		ret.push_back(std::make_pair(60*18, tmnb));

	}

	return ret;
}

