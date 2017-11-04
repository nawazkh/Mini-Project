#pragma once

#include "globals.h"
#include "player.h"

struct CometSmall {
public:
	int x;
	int y;
	int boundX;
	int boundY;
	int speed;
	bool alive;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sound;
};
	
void initCometSmall(CometSmall cometsSmall[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound) {
	for(int i = 0; i < 20; i++) {
		cometsSmall[i].alive = false;
		cometsSmall[i].boundX = 23;
		cometsSmall[i].boundY = 20;
		cometsSmall[i].speed = 1;
		cometsSmall[i].image = image;
		cometsSmall[i].sound = sound;
	}
}

void startCometSmall(CometSmall cometsSmall[]) {
	for(int i = 0; i < 20; i++) {
		if(!cometsSmall[i].alive) {
			if(difficulty[EASY]) {
				if(rand() %8000 == 0) {
					cometsSmall[i].alive = true;
					cometsSmall[i].x = 60 + rand() % (screenW - 140);
					cometsSmall[i].y = -40;
					objectCount++;
				}
			}
			else if(difficulty[NORM]) {
				if(rand() %6000 == 0) {
					cometsSmall[i].alive = true;
					cometsSmall[i].x = 60 + rand() % (screenW - 140);
					cometsSmall[i].y = -40;
					objectCount++;
				}
			}
			else if(difficulty[HARD]) {
				if(rand() %5000 == 0) {
					cometsSmall[i].alive = true;
					cometsSmall[i].x = 60 + rand() % (screenW - 140);
					cometsSmall[i].y = -40;
					objectCount++;
				}
			}
		}
	}
}

void updateCometSmall(CometSmall cometsSmall[]) {
	for(int i = 0; i < 20; i++) {
		if(cometsSmall[i].alive) {
			cometsSmall[i].y += cometsSmall[i].speed;
		}
	}
}

void collideCometSmall(CometSmall cometsSmall[], Player &ship) {
	for(int i = 0; i < 20; i++) {
		if(cometsSmall[i].alive) {
			if(cometsSmall[i].x + cometsSmall[i].boundX > ship.getX() - ship.getBoundX() &&
				cometsSmall[i].x - cometsSmall[i].boundX < ship.getX() + ship.getBoundX() &&
				cometsSmall[i].y + cometsSmall[i].boundY > ship.getY() - ship.getBoundY() &&
				cometsSmall[i].y - cometsSmall[i].boundY < ship.getY() + ship.getBoundY())
			{
				al_play_sample(cometsSmall[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				ship.decrementLives();
				cometsSmall[i].alive = false;
				shieldTimer = 5;
				objectCount--;
			}
			else if(cometsSmall[i].y > screenH) {
				al_play_sample(cometsSmall[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				ship.decrementLives();
				cometsSmall[i].alive = false;
				objectCount--;
			}
		}
	}
}

void renderCometSmall(CometSmall cometsSmall[]) {
	for(int i = 0; i < 20; i++) {
		if(cometsSmall[i].alive) {
			if(keys[F3]) {
				al_draw_filled_rectangle(cometsSmall[i].x - cometsSmall[i].boundX, cometsSmall[i].y - cometsSmall[i].boundY, cometsSmall[i].x + cometsSmall[i].boundX, cometsSmall[i].y + cometsSmall[i].boundY, al_map_rgb(255,0,0));
			}
			al_draw_bitmap(cometsSmall[i].image, cometsSmall[i].x - cometsSmall[i].boundX, cometsSmall[i].y - cometsSmall[i].boundY, 0);
		}
	}
}