#pragma once

#include "globals.h"
#include "player.h"

class BulletEnemy {
private:
	int x;
	int y;
	int speed;
	bool alive;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE *explosion;
	ALLEGRO_SAMPLE *loseLife;

public:
	void init(BulletEnemy bulletEnemy[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE *explosion, ALLEGRO_SAMPLE *loseLife) {
		for(int i = 0; i < 20; i++) {
			bulletEnemy[i].alive = false;
			bulletEnemy[i].speed = 7;
			bulletEnemy[i].image = image;
			bulletEnemy[i].sample = sample;
			bulletEnemy[i].explosion = explosion;
			bulletEnemy[i].loseLife = loseLife;
		}
	}

	void fire(BulletEnemy bulletEnemy[], int x, int y, bool shipAlive) {
		for(int i = 0; i < 20; i++) {
			if(!bulletEnemy[i].alive) {
				al_play_sample(bulletEnemy[i].sample, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				bulletEnemy[i].alive = true;
				bulletEnemy[i].x = x;
				bulletEnemy[i].y = y;
				objectCount++;
				break;
			}
		}
	}
	
	void update(BulletEnemy bulletEnemy[]) {
		for(int i = 0; i < 20; i++) {
			if(bulletEnemy[i].alive) {
				bulletEnemy[i].y += bulletEnemy[i].speed;
			}
		}
	}

	void collide(BulletEnemy bulletEnemy[], Player &ship) {
		for(int i = 0; i < 20; i++) {
			if(bulletEnemy[i].alive) {
				if(bulletEnemy[i].x > ship.getX() - ship.getBoundX() &&
					bulletEnemy[i].x < ship.getX() + ship.getBoundX() &&
					bulletEnemy[i].y > ship.getY() - ship.getBoundY() &&
					bulletEnemy[i].y < ship.getY() + ship.getBoundY())
				{
					if(ship.getShield() == 0) {
						al_play_sample(bulletEnemy[i].explosion, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						bulletEnemy[i].alive = false;
						ship.decrementLives();
					}
					else if(ship.getShield() == 1) {
						al_play_sample(bulletEnemy[i].loseLife, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						bulletEnemy[i].alive = false;
						shieldTimer = 5;
					}
					objectCount--;
				}
				else if(bulletEnemy[i].y > screenH) {
					bulletEnemy[i].alive = false;
					objectCount--;
				}
			}
		}
	}

	void render(BulletEnemy bulletEnemy[]) {
		for(int i = 0; i < 20; i++) {
			if(bulletEnemy[i].alive) {
				al_draw_bitmap(bulletEnemy[i].image, bulletEnemy[i].x - 5, bulletEnemy[i].y - 33, 0);
				if(keys[F3]) {
					al_draw_filled_rectangle(bulletEnemy[i].x - 2, bulletEnemy[i].y - 2, bulletEnemy[i].x + 2, bulletEnemy[i].y + 2, al_map_rgb(0,255,0));
				}
			}
		}
	}
};