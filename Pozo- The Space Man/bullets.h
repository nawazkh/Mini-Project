#pragma once

#include "globals.h"
#include "cometBig.h"
#include "cometSmall.h"
#include "enemyShipNormal.h"

struct Bullet {
public:
	int x;
	int y;
	int speed;
	bool alive;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE *explosion;
};

void initBullet(Bullet bullets[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE *explosion) {
	for(int i = 0; i < 20; i++) {
		bullets[i].alive = false;
		bullets[i].speed = 7;
		bullets[i].image = image;
		bullets[i].sample = sample;
		bullets[i].explosion = explosion;
	}
}
void fireBullet(Bullet bullets[], int xStart, int yStart) {
	for(int i = 0; i < 20; i++) {
		if(!bullets[i].alive) {
			bullets[i].x = xStart;
			bullets[i].y = yStart;
			bullets[i].alive = true;
			objectCount++;
			al_play_sample(bullets[i].sample, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			break;
		}
	}
}
void updateBullet(Bullet bullets[]) {
	for(int i = 0; i < 20; i++) {
		if(bullets[i].alive) {
			bullets[i].y -= bullets[i].speed;
		}
	}
}
void collideBullet(Bullet bullets[], CometBig cometsBig[], CometSmall cometsSmall[], EnemyShip enemyShip[], Player &ship) {
	for(int i = 0; i < 20; i++) {
		if(bullets[i].alive) {
			for(int j = 0; j < 20; j++) {
				if(cometsBig[j].alive) {
					if(cometsBig[j].x + cometsBig[j].boundX > bullets[i].x &&
						cometsBig[j].x - cometsBig[j].boundX < bullets[i].x &&
						cometsBig[j].y + cometsBig[j].boundY > bullets[i].y &&
						cometsBig[j].y - cometsBig[j].boundY < bullets[i].y)
					{
						al_play_sample(bullets[i].explosion, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						ship.incrementScoreCB();
						bullets[i].alive = false;
						cometsBig[j].alive = false;
						objectCount -= 2;
					}
				}
				if(cometsSmall[j].alive) {
					if(cometsSmall[j].x + cometsSmall[j].boundX > bullets[i].x &&
						cometsSmall[j].x - cometsSmall[j].boundX < bullets[i].x &&
						cometsSmall[j].y + cometsSmall[j].boundY > bullets[i].y &&
						cometsSmall[j].y - cometsSmall[j].boundY < bullets[i].y)
					{
						al_play_sample(bullets[i].explosion, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						ship.incrementScoreCS();
						bullets[i].alive = false;
						cometsSmall[j].alive = false;
						objectCount -= 2;
					}
				}
			}
			for(int j = 0; j < 1; j++) {
				if(enemyShip[j].getAlive()) {
					if(enemyShip[j].getX() - enemyShip[j].getBoundX() < bullets[i].x &&
						enemyShip[j].getX() + enemyShip[j].getBoundX() > bullets[i].x &&
						enemyShip[j].getY() - enemyShip[j].getBoundY() < bullets[i].y &&
						enemyShip[j].getY() + enemyShip[j].getBoundY() > bullets[i].y)
					{
						al_play_sample(bullets[i].explosion, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						ship.incrementScoreEN();
						enemyShip[j].setAlive(false);
						bullets[i].alive = false;
						objectCount -= 2;
					}
				}
			}
			if(bullets[i].y < 0) {
				bullets[i].alive = false;
				objectCount--;
			}
		}
	}
}
void renderBullet(Bullet bullets[]) {
	for(int i = 0; i < 20; i++) {
		if(bullets[i].alive) {
			if(keys[F3]) {
				al_draw_filled_rectangle(bullets[i].x - 2, bullets[i].y - 2, bullets[i].x + 2, bullets[i].y + 2, al_map_rgb(0,255,255));
			}
			al_draw_bitmap(bullets[i].image, bullets[i].x - 5, bullets[i].y, 0);
		}
	}
}