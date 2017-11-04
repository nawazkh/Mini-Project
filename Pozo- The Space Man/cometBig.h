#pragma once

#include "globals.h"
#include "player.h"

struct CometBig {
public:
	int x;
	int y;
	int boundX;
	int boundY;
	int speed;
	int rotation;
	bool alive;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sound;
};
	
void initCometBig(CometBig cometsBig[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound) {
	for(int i = 0; i < 20; i++) {
		cometsBig[i].alive = false;
		cometsBig[i].boundX = 68;
		cometsBig[i].boundY = 45;
		cometsBig[i].speed = 1;
		cometsBig[i].image = image;
		cometsBig[i].sound = sound;
	}
}

void startCometBig(CometBig cometsBig[]) {
	for(int i = 0; i < 20; i++) {
		if(!cometsBig[i].alive) {
			if(difficulty[EASY]) {
				if(rand() %6000 == 0) {
					cometsBig[i].alive = true;
					cometsBig[i].x = 60 + rand() % (screenW - 140);
					cometsBig[i].y = -40;
					objectCount++;
				}
			}
			else if(difficulty[NORM]) {
				if(rand() %5500 == 0) {
					cometsBig[i].alive = true;
					cometsBig[i].x = 60 + rand() % (screenW - 140);
					cometsBig[i].y = -40;
					objectCount++;
				}
			}
			else if(difficulty[HARD]) {
				if(rand() %5000 == 0) {
					cometsBig[i].alive = true;
					cometsBig[i].x = 60 + rand() % (screenW - 140);
					cometsBig[i].y = -40;
					objectCount++;
				}
			}
		}
	}
}

void updateCometBig(CometBig cometsBig[]) {
	for(int i = 0; i < 20; i++) {
		if(cometsBig[i].alive) {
			cometsBig[i].y += cometsBig[i].speed;
		}
	}
}

void collideCometBig(CometBig cometsBig[], Player &ship) {
	for(int i = 0; i < 20; i++) {
		if(cometsBig[i].alive) {
			if(cometsBig[i].x + cometsBig[i].boundX > ship.getX() - ship.getBoundX() &&
				cometsBig[i].x - cometsBig[i].boundX < ship.getX() + ship.getBoundX() &&
				cometsBig[i].y + cometsBig[i].boundY > ship.getY() - ship.getBoundY() &&
				cometsBig[i].y - cometsBig[i].boundY < ship.getY() + ship.getBoundY())
			{
				al_play_sample(cometsBig[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				ship.decrementLives();
				shieldTimer = 5;
				cometsBig[i].alive = false;
				objectCount--;
			}
			else if(cometsBig[i].y > screenH) {
				al_play_sample(cometsBig[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				ship.decrementLives();
				cometsBig[i].alive = false;
				objectCount--;
			}
		}
	}
}

void renderCometBig(CometBig cometsBig[]) {
	for(int i = 0; i < 20; i++) {
		if(cometsBig[i].alive) {
			if(keys[F3]) {
				al_draw_filled_rectangle(cometsBig[i].x - cometsBig[i].boundX, cometsBig[i].y - cometsBig[i].boundY, cometsBig[i].x + cometsBig[i].boundX, cometsBig[i].y + cometsBig[i].boundY, al_map_rgb(255,0,0));
			}
			al_draw_bitmap(cometsBig[i].image, cometsBig[i].x - cometsBig[i].boundX, cometsBig[i].y - cometsBig[i].boundY, 0);
		}
	}
}