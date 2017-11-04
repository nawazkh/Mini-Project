#pragma once

class NebulaCore {
protected:
	int x;
	int y;
	int speed;
	bool final;

	ALLEGRO_BITMAP *image;

public:
	void init(ALLEGRO_BITMAP *image);
	void update();
	void render();

	int getFinal();
};