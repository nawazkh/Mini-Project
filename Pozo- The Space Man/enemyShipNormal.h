#pragma once

#include "globals.h"
#include "player.h"
#include "bulletEnemy.h"

BulletEnemy bulletEnemy[20];

class EnemyShip {
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
	void init(EnemyShip enemyShip[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound) {
		for(int i = 0; i < 1; i++) {
			enemyShip[i].alive = false;
			enemyShip[i].speed = 2;
			enemyShip[i].boundX = 49;
			enemyShip[i].boundY = 25;
			enemyShip[i].image = image;
			enemyShip[i].sound = sound;
		}
	}

	void start(EnemyShip enemyShip[]) {
		for(int i = 0; i < 1; i++) {
			if(!enemyShip[i].alive) {
				if(difficulty[EASY]) {
					if(rand() % 3000 == 0) {
						enemyShip[i].alive = true;
						enemyShip[i].x = 60 + rand() % (screenW - 140);
						enemyShip[i].y = -40;
						objectCount++;
					}
				}
				else if(difficulty[NORM]) {
					if(rand() % 2250 == 0) {
						enemyShip[i].alive = true;
						enemyShip[i].x = 60 + rand() % (screenW - 140);
						enemyShip[i].y = -40;
						objectCount++;
					}
				}
				else if(difficulty[HARD]) {
					if(rand() % 1750 == 0) {
						enemyShip[i].alive = true;
						enemyShip[i].x = 60 + rand() % (screenW - 140);
						enemyShip[i].y = -40;
						objectCount++;
					}
				}
			}
		}
	}

	void update(EnemyShip enemyShip[], Player &ship) {
		for(int i = 0; i < 1; i++) {
			if(enemyShip[i].alive) {
				if(enemyShip[i].y < 120) {
					enemyShip[i].y += enemyShip[i].speed;
				}
					
				if(ship.getX() > enemyShip[i].x)
					enemyShip[i].x += enemyShip[i].speed;
				else if(ship.getX() < enemyShip[i].x)
					enemyShip[i].x -= enemyShip[i].speed;
				else if(ship.getX() == enemyShip[i].x)
					enemyShip[i].x += 0;

				if(difficulty[EASY]) {
					enemyFireTimer++;
					if(enemyFireTimer >= 200) {
						bulletEnemy->fire(bulletEnemy, enemyShip[i].x, enemyShip[i].y, enemyShip[i].alive);
						enemyFireTimer = 0;
					}
				}
				else if(difficulty[NORM]) {
					enemyFireTimer++;
					if(enemyFireTimer >= 160) {
						bulletEnemy->fire(bulletEnemy, enemyShip[i].x, enemyShip[i].y, enemyShip[i].alive);
						enemyFireTimer = 0;
					}
				}
				else if(difficulty[HARD]) {
					enemyFireTimer++;
					if(enemyFireTimer >= 120) {
						bulletEnemy->fire(bulletEnemy, enemyShip[i].x, enemyShip[i].y, enemyShip[i].alive);
						enemyFireTimer = 0;
					}
				}
			}
		}
	}

	void collide(EnemyShip enemyShip[], Player &ship) {
		for(int i = 0; i < 1; i++) {
			if(enemyShip[i].alive)
				if(enemyShip[i].x + enemyShip[i].boundX > ship.getX() - ship.getBoundX() &&
					enemyShip[i].x - enemyShip[i].boundX < ship.getX() + ship.getBoundX() &&
					enemyShip[i].y + enemyShip[i].boundY > ship.getY() - ship.getBoundY() &&
					enemyShip[i].y - enemyShip[i].boundY < ship.getY() + ship.getBoundY())
				{
					al_play_sample(enemyShip[i].sound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					enemyShip[i].alive = false;
					ship.decrementLives();
					objectCount--;
				}
		}
	}

	void render(EnemyShip enemyShip[]) {
		for(int i = 0; i < 1; i++) {
			if(enemyShip[i].alive) {
				if(keys[F3]) {
					al_draw_filled_rectangle(enemyShip[i].x - enemyShip[i].boundX, enemyShip[i].y - enemyShip[i].boundY, enemyShip[i].x + enemyShip[i].boundX, enemyShip[i].y + enemyShip[i].boundY, al_map_rgb(255,100,0));
				}
				al_draw_bitmap(enemyShip[i].image, enemyShip[i].x - enemyShip[i].boundX, enemyShip[i].y - enemyShip[i].boundY, 0);
			}
		}
	}

	int getAlive() {return EnemyShip::alive;}
	void setAlive(bool alive) {EnemyShip::alive = alive;}

	int getX() {return EnemyShip::x;}
	int getY() {return EnemyShip::y;}

	int getBoundX() {return EnemyShip::boundX;}
	int getBoundY() {return EnemyShip::boundY;}
};