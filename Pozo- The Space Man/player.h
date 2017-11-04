#pragma once

#include "globals.h"

class Player {//variables of player
private:
	int x;
	int y;
	int xBound;
	int yBound;
	int speed;
	int lives;
	int shield;
	int score;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *imageL;
	ALLEGRO_BITMAP *imageR;
	ALLEGRO_BITMAP *imageDam;
	ALLEGRO_BITMAP *imageShl;
	ALLEGRO_BITMAP *imageLives;

public:
	void init(ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *imageL, ALLEGRO_BITMAP *imageR, ALLEGRO_BITMAP *imageDam, ALLEGRO_BITMAP *imageShl, ALLEGRO_BITMAP *imageLives) {
		Player::x = screenW/2;
		Player::y = screenH/1.1;
		Player::xBound = 49;
		Player::yBound = 40;
		Player::speed = 5;
		Player::lives = 3;
		Player::shield = 1;
		Player::score = 0;
		Player::image = image;
		Player::imageL = imageL;
		Player::imageR = imageR;
		Player::imageDam = imageDam;
		Player::imageShl = imageShl;
		Player::imageLives = imageLives;
		objectCount++;
	}

	void render() {
		if(keys[F3]) {
			al_draw_filled_rectangle(Player::x + Player::xBound, Player::y + Player::yBound, Player::x - Player::xBound, Player::y - Player::yBound, al_map_rgb(0,255,255));
		}
		if(Player::shield > 0) {
			al_draw_bitmap(Player::imageShl, Player::x-75, Player::y-70, 0);
		}
		if(Player::lives > 1) {
			if((!keys[A] && !keys[D]) || keys[A] && keys[D])
				al_draw_bitmap(Player::image, Player::x - Player::xBound, Player::y - Player::yBound, 0);
			else if(keys[A] && !keys[D])
				al_draw_bitmap(Player::imageL, Player::x - Player::xBound, Player::y - Player::yBound, 0);
			else if(!keys[A] && keys[D])
				al_draw_bitmap(Player::imageR, Player::x - (Player::xBound-8), Player::y - Player::yBound, 0);
		}
		else if(Player::lives <= 1) {
			al_draw_bitmap(Player::imageDam, Player::x - Player::xBound, Player::y - Player::yBound, 0);
		}
		if(Player::lives == 3) {
			al_draw_bitmap(Player::imageLives, 5, 7, 0);
			al_draw_bitmap(Player::imageLives, 45, 7, 0);
			al_draw_bitmap(Player::imageLives, 85, 7, 0);
		}
		else if(Player::lives == 2) {
			al_draw_bitmap(Player::imageLives, 5, 7, 0);
			al_draw_bitmap(Player::imageLives, 45, 7, 0);
		}
		else if(Player::lives == 1) {
			al_draw_bitmap(Player::imageLives, 5, 7, 0);
		}
	}

	void moveUp() {
		Player::y -= Player::speed;
		if(Player::y - Player::yBound < 0) {
			Player::y = Player::yBound;
		}
	}
	void moveDown() {
		Player::y += Player::speed;
		if(Player::y + Player::yBound >= screenH) {
			Player::y = screenH - Player::yBound;
		}
	}
	void moveLeft() {
		Player::x -= Player::speed;
		if(Player::x - (Player::xBound+2) < 0) {
			Player::x = Player::xBound+2;
		}
	}
	void moveRight() {
		Player::x += Player::speed;
		if(Player::x + (Player::xBound+2) >= screenW) {
			Player::x = screenW - (Player::xBound+2);
		}
	}

	int getX() {return Player::x;}
	int getY() {return Player::y;}
	int getBoundY() {return Player::yBound;}
	int getBoundX() {return Player::xBound;}

	int getScore() {return Player::score;}
	void decrementScore() {Player::score--;}
	void incrementScoreCB() {Player::score += 10;}
	void incrementScoreCS() {Player::score += 8;}
	void incrementScoreEN() {Player::score += 25;}

	int getLives() {return Player::lives;}
	void decrementLives() {Player::lives--;}
	void incrementLives() {Player::lives++;}

	int getShield() {return Player::shield;}
	void setShield(int shield) {
		Player::shield = shield;
	}
};
