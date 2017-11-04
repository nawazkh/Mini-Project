#include "globals.h"

class GameBackground {
private:
	int x;
	int y;
	int speed;
	int backgroundType;

	ALLEGRO_BITMAP *image;

public:
	GameBackground():
	  x(0), y(768), speed(0), image(0), backgroundType(0) {}
	~GameBackground()
	{
		GameBackground::x = 0;
		GameBackground::y = 0;
		GameBackground::speed = 0;
		GameBackground::image = 0;
		GameBackground::backgroundType = 0;
	}

	void init(ALLEGRO_BITMAP *image, int speed, int backgroundType) { // 1(stars), 2(nebulas)
		GameBackground::image = image;
		GameBackground::speed = speed;
		GameBackground::backgroundType = backgroundType;
	}

	void update() {
		GameBackground::y += GameBackground::speed;
		if(GameBackground::y > 0)
		{
			if(GameBackground::backgroundType == 1)
				GameBackground::y = -768*2;
			else if(GameBackground::backgroundType == 2)
				GameBackground::y = -768*4;
		}
	}

	void render() {
		al_draw_bitmap(image, GameBackground::x, GameBackground::y, 0);
	}
};