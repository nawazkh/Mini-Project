#pragma once

#include "globals.h"
#include "player.h"

class HealthUp {
private:
	int x;
	int y;
	int boundX;
	int boundY;
	int speed;
	bool alive;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sound;

public:
	void init(HealthUp healthUp[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound) {
		for(int i = 0; i < 1; i++) {
			healthUp[i].alive = false;
			healthUp[i].speed = 3;
			healthUp[i].boundX = 18;
			healthUp[i].boundY = 14;
			healthUp[i].image = image;
			healthUp[i].sound = sound;
		}
	}

	void start(HealthUp healthUp[]) {
		for(int i = 0; i < 1; i++) {
			if(!healthUp[i].alive) {
				if(difficulty[EASY]) {
					if(rand() % 13000 == 0) {
						healthUp[i].alive = true;
						healthUp[i].x = 60 + rand() % (screenW - 140);
						healthUp[i].y = -40;
						objectCount++;
					}
				}
				else if(difficulty[NORM]) {
					if(rand() % 16000 == 0) {
						healthUp[i].alive = true;
						healthUp[i].x = 60 + rand() % (screenW - 140);
						healthUp[i].y = -40;
						objectCount++;
					}
				}
				else if(difficulty[HARD]) {
					if(rand() % 19000 == 0) {
						healthUp[i].alive = true;
						healthUp[i].x = 60 + rand() % (screenW - 140);
						healthUp[i].y = -40;
						objectCount++;
					}
				}
			}
		}
	}

	void update(HealthUp healthUp[]) {
		for(int i = 0; i < 1; i++) {
			if(healthUp[i].alive) {
				healthUp[i].y += healthUp[i].speed;
			}
		}
	}

	void collide(HealthUp healthUp[], Player &ship) {
		for(int i = 0; i < 1; i++) {
			if(healthUp[i].alive) {
				if(healthUp[i].x + healthUp[i].boundX > ship.getX() - ship.getBoundX() &&
					healthUp[i].x - healthUp[i].boundX < ship.getX() + ship.getBoundX() &&
					healthUp[i].y + healthUp[i].boundY > ship.getY() - ship.getBoundY() &&
					healthUp[i].y - healthUp[i].boundY < ship.getY() + ship.getBoundY())
				{
					if(ship.getLives() < 3) {
						healthUp[i].alive = false;
						ship.incrementLives();
						al_play_sample(healthUp[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					objectCount--;
				}
				else if(healthUp[i].y > screenH) {
					healthUp[i].alive = false;
					objectCount--;
				}
			}
		}
	}

	void render(HealthUp healthUp[]) {
		for(int i = 0; i < 1; i++) {
			if(healthUp[i].alive) {
				if(keys[F3]) {
					al_draw_filled_rectangle(healthUp[i].x - healthUp[i].boundX, healthUp[i].y - healthUp[i].boundY, healthUp[i].x + healthUp[i].boundX, healthUp[i].y + healthUp[i].boundY, al_map_rgb(0,255,0));
				}
				//al_draw_rotated_bitmap(healthUp[i].image, healthUp[i].x, healthUp[i].y, healthUp[i].x - healthUp[i].boundX, healthUp[i].y - healthUp[i].boundY, 180 * (ALLEGRO_PI / 180), 0);
				al_draw_bitmap(healthUp[i].image, healthUp[i].x - healthUp[i].boundX, healthUp[i].y - healthUp[i].boundY, 0);
			}
		}
	}

};