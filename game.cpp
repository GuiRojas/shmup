#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include <functional>

#include "enemy.h"
#include "bullet.h"
#include "player.h"

#include "stage1.h"

#define HP_HUD "img/mano.png"
#define BOSS_STAGE_HUD "img/mano.png"

//////////////////////////////////////////////
//////////////////////////////////////////////
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

// cooldowns
const int SHOOT_CD_TIME = 5;
const int DAMAGE_CD_TIME = 45;
int shoot_cd = 0;
int damage_cd = DAMAGE_CD_TIME;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

int stagePart = 0;
std::vector<std::pair<int,Enemy*>> stage;

Player player(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
std::vector<Bullet*> bullets;
std::vector<Bullet*> player_bullets;
std::vector<Enemy*> enemies;
std::vector<Drop*> drops;

int frames = 0;
bool quit = false;
//////////////////////////////////////////////
//////////////////////////////////////////////

bool collided(SDL_Rect hbA, SDL_Rect hbB){
	return SDL_HasIntersection(&hbA, &hbB) == SDL_TRUE;
}

bool collided_player(Player* player, Bullet* bullet){
	SDL_Rect plHb = player->getHitbox();

	SDL_Rect blHb = {
		bullet->getX(),
		bullet->getY(),
		bullet->getW(),
		bullet->getH()
	};

	return collided(plHb, blHb);
}

bool collided_enemy(Enemy* enemy, Bullet* bullet){
	SDL_Rect enHb = {
		enemy->getX(),
		enemy->getY(),
		enemy->getW(),
		enemy->getH()
	};

	SDL_Rect blHb = {
		bullet->getX(),
		bullet->getY(),
		bullet->getW(),
		bullet->getH()
	};

	return collided(enHb, blHb);
}

bool collided_drop(Player* player, Drop* drop){
	SDL_Rect dpHb = {
		drop->getX(),
		drop->getY(),
		drop->getW(),
		drop->getH()
	};

	SDL_Rect plHb = player->getHitbox();

	return collided(dpHb, plHb);
}

//////////////////////////////////////////////
//////////////////////////////////////////////

bool init(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL){
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	// init player
	if(!(player.loadImg(gRenderer))){
		return false;
	}

	return true;
}

void close(){
	while(bullets.size()>0){
		bullets[0]->free();
		bullets.erase(bullets.begin());
	}

	while(player_bullets.size()>0){
		player_bullets[0]->free();
		player_bullets.erase(player_bullets.begin());
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

//////////////////////////////////////////////
//////////////////////////////////////////////

void input(){
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if(keys[SDL_SCANCODE_Q]){
		quit = true;
	}

	if(keys[SDL_SCANCODE_LSHIFT]){
		player.focused = true;
	} else {
		player.focused = false;
	}

	bool shouldMoveL = keys[SDL_SCANCODE_LEFT];
	bool shouldMoveR = keys[SDL_SCANCODE_RIGHT];
	bool shouldMoveU = keys[SDL_SCANCODE_UP];
	bool shouldMoveD = keys[SDL_SCANCODE_DOWN];

	if(shouldMoveL && !shouldMoveR
		&& player.getX() - player.getSpd() >= 0){
		player.moveL();
	} else if (shouldMoveR && !shouldMoveL
		&& player.getX() + player.getW() + player.getSpd() <= SCREEN_WIDTH){
		player.moveR();
	} else if (!shouldMoveR && !shouldMoveL){
		player.moveNot();
	}
	if(shouldMoveU && !shouldMoveD
		&& player.getY() - player.getSpd() >= 0){
		player.moveU();
	} else if (shouldMoveD && !shouldMoveU
		&& player.getY() + player.getH() + player.getSpd() <= SCREEN_HEIGHT){
		player.moveD();
	}

	if(keys[SDL_SCANCODE_Z] && shoot_cd >= SHOOT_CD_TIME){
		shoot_cd = 0;
		std::vector<Bullet*> nb = player.shoot(gRenderer);
		for (int i = 0; i < nb.size(); ++i){
			player_bullets.push_back(nb[i]);
		}
	}	

	if(keys[SDL_SCANCODE_R]){
		player.power++;
	}
}

//////////////////////////////////////////////
//////////////////////////////////////////////

void load_enemies(){
	std::vector<std::pair<int,Enemy*>> nstg = load_stage1(gRenderer, &bullets, &player);
	for (int i = 0; i < nstg.size(); ++i){
		stage.push_back(nstg[i]);
	}
}

//////////////////////////////////////////////
//////////////////////////////////////////////

int main(int argc, char* args[]){
	if(!init()){
		printf("Failed to initialize!\n");
		return -1;
	}

	SDL_Event e;

	load_enemies();

	frames = 60*18;

	while(!quit){

		//printf("f %d\n", frames);
		//printf("s %d\n", stage[stagePart].first);


		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}

		if(shoot_cd < SHOOT_CD_TIME){
			shoot_cd++;
		}
		if(damage_cd < DAMAGE_CD_TIME){
			damage_cd++;
			if(damage_cd==DAMAGE_CD_TIME){
				player.undamaged();
			}
		}

		input();

		// for debugging purposes
		while(stage[stagePart].first < frames &&
			  stagePart < stage.size()){
			stagePart++;
		}

		while(stage[stagePart].first == frames &&
			  stagePart < stage.size()){
			enemies.push_back(stage[stagePart].second);
			stagePart++;
		}


		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// render enemy
		for (int i = 0; i < enemies.size(); ++i){
			if (enemies[i]->shouldDie){
				for(int j=0;j<enemies[i]->drops.size();++j){
					enemies[i]->drops[j]->init(gRenderer);
					drops.push_back(enemies[i]->drops[j]);
				}
				enemies[i]->free();
				enemies.erase(enemies.begin()+i);
				--i;
				player.power+=10;
				continue;
			}
			enemies[i]->move();
			enemies[i]->render(gRenderer);
			// boss healtbar
			if(enemies[i]->boss){
				int chunk = (int)((SCREEN_WIDTH-20)/enemies[i]->maxhp);
	            SDL_Rect bshb = {
	            	10,
	            	60,
	            	chunk*enemies[i]->hp,
	            	20
	            };
	            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);        
	            SDL_RenderFillRect(gRenderer, &bshb);

	        	SDL_Surface* bossStageSurface = IMG_Load(BOSS_STAGE_HUD);
				SDL_Texture* bossStageImg = SDL_CreateTextureFromSurface(gRenderer, bossStageSurface);
				SDL_FreeSurface(bossStageSurface);

				for (int j = 1; j <= enemies[i]->getS(); ++j){
					SDL_Rect bossStageQuad = {
						(j*50)-40,
						90,
						30,
						30
					};

					SDL_RenderCopy(gRenderer, bossStageImg, NULL, &bossStageQuad);
				} 
			}

		}

		// render enemy bullets
		for (int i = 0; i < bullets.size(); ++i){
			bullets[i]->move();
			if (collided_player(&player, bullets[i]) && damage_cd>=DAMAGE_CD_TIME)
			{
				player.takeDamage();
				damage_cd = 0;
				bullets[i]->free();
				bullets.erase(bullets.begin()+i);
				--i;
			} else if(
				bullets[i]->getX()+bullets[i]->getW()<0 ||
				bullets[i]->getX()>= SCREEN_WIDTH ||
				bullets[i]->getY()-bullets[i]->getH()<0 ||
				bullets[i]->getY()>= SCREEN_HEIGHT
			){
				bullets[i]->free();
				bullets.erase(bullets.begin()+i);
				--i;
			} else {
				bullets[i]->render(gRenderer);
			}
		}

		// render drops on screen
		for (int i = 0; i < drops.size(); ++i){
			drops[i]->move();
			if (collided_drop(&player, drops[i])){
				player.hp++;
				player.power+=70;
				drops[i]->free();
				drops.erase(drops.begin()+i);
				--i;
			} else if (
				drops[i]->getX()+drops[i]->getW()<0 ||
				drops[i]->getX()>= SCREEN_WIDTH ||
				// drops[i]->getY()-drops[i]->getH()<0 ||
				drops[i]->getY()>= SCREEN_HEIGHT
			){
				drops[i]->free();
				drops.erase(drops.begin()+i);
				--i;
			} else {
				drops[i]->render(gRenderer);
			}
		}

		// render player
		player.render(gRenderer);
		if (player.focused){
            SDL_Rect plHitbox = player.getHitbox();
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);        
            SDL_RenderFillRect(gRenderer, &plHitbox);
		}

		// render player bullets
		for (int i = 0; i < player_bullets.size(); ++i){
			player_bullets[i]->move();

			bool should_bullet_die = false;

			for (int j = 0; j < enemies.size(); ++j){
				if ( !should_bullet_die && collided_enemy(enemies[j], player_bullets[i])){
					enemies[j]->takeDamage();
					should_bullet_die = true;
				}
			}

			if(
				should_bullet_die ||
				player_bullets[i]->getX()+player_bullets[i]->getW()<0 ||
				player_bullets[i]->getX()>= SCREEN_WIDTH ||
				player_bullets[i]->getY()-player_bullets[i]->getH()<0 ||
				player_bullets[i]->getY()>= SCREEN_HEIGHT
			){
				player_bullets[i]->free();
				player_bullets.erase(player_bullets.begin()+i);
				--i;
			} else {
				player_bullets[i]->render(gRenderer);
			}
		}

		// draw a HUD
		{
			SDL_Surface* hpSurface = IMG_Load(HP_HUD);
			SDL_Texture* hpImg = SDL_CreateTextureFromSurface(gRenderer, hpSurface);
			SDL_FreeSurface(hpSurface);

			for (int i = 1; i <= player.getHP(); ++i){
				SDL_Rect hpQuad = {
					(i*60)-50,
					10,
					40,
					40
				};

				SDL_RenderCopy(gRenderer, hpImg, NULL, &hpQuad);
			}
		}

		SDL_RenderPresent(gRenderer);
		frames++;
	}

	close();
	return 0;
}
