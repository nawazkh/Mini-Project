#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "titleAnim.h"

class NebulaBig : public NebulaCore {
public:
	void init(ALLEGRO_BITMAP *image) {
		NebulaBig::x = 355;
		NebulaBig::y = -405;
		NebulaBig::speed = 3;
		NebulaBig::image = image;
		NebulaBig::final = false;
	}

	void update() {
		if(NebulaBig::y < 0)
		{
			NebulaBig::y += NebulaBig::speed;
		}
		else if(NebulaBig::y == 0)
		{
			NebulaBig::final = true;
		}
			
	}

	void render() {
		al_draw_bitmap(image, NebulaBig::x, NebulaBig::y, 0);
	}

	int getFinal() {return NebulaBig::final;}
};