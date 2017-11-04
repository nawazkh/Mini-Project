#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "titleAnim.h"
#include "globals.h"

class TutorialShoot : public NebulaCore {
public:
	void init(ALLEGRO_BITMAP *image) {
		TutorialShoot::x = 1566;
		TutorialShoot::y = screenH/7;
		TutorialShoot::speed = 7;
		TutorialShoot::image = image;
		TutorialShoot::final = false;
	}

	void update() {
		if(TutorialShoot::x > 999)
		{
			TutorialShoot::x -= TutorialShoot::speed;
		}
		else if(TutorialShoot::x <= 1000)
		{
			TutorialShoot::final = true;
		}
			
	}

	void render() {
		al_draw_rectangle(TutorialShoot::x, TutorialShoot::y, TutorialShoot::x+200, TutorialShoot::y+500, al_map_rgb(255,255,255), 2);
		al_draw_bitmap(image, TutorialShoot::x, TutorialShoot::y, 0);
	}

	bool getFinal() {return TutorialShoot::final;}
};