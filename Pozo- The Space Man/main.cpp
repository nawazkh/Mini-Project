#include <iostream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "globals.h"
#include "buttons.h"
#include "screenState.h"
#include "nebulaBig.h"
#include "tutorialShoot.h"
#include "player.h"
#include "bullets.h"
#include "bulletEnemy.h"
#include "cometBig.h"
#include "cometSmall.h"
#include "healthup.h"
#include "enemyShipNormal.h"
#include "backgroundAnim.h"

int main(int argc, char **argv) {

	/*SHELL VARIABLES*/
	unsigned short addonCheck = 0;
	unsigned long animCounter = 0;

	bool running = false;
	bool rendering = false;

	int gameFPS = 0;
	int frames = 0;
	float gameTime = 0;
	int seconds = 0;
	int minutes = 0;
	int framesElapsed = 0;

	NebulaBig nebulaBigC;
	TutorialShoot tutorialShootC;

	Buttons *bPlay = new Buttons();
	Buttons *bHelp = new Buttons();
	Buttons *bOptn = new Buttons();
	Buttons *bBack = new Buttons();
	Buttons *bExit = new Buttons();
	Buttons *bMenu = new Buttons();
	Buttons *bExit2 = new Buttons();
	Buttons *bVolumeP = new Buttons();
	Buttons *bVolumeM = new Buttons();
	Buttons *bDifficultyP = new Buttons();
	Buttons *bDifficultyM = new Buttons();

	Bullet bullets[20];
	//BulletEnemy bulletEnemy[20];

	CometBig cometsBig[20];
	CometSmall cometsSmall[20];
	HealthUp healthUp[1];

	EnemyShip enemyShip[1];

	Player ship;

	GameBackground bgStars;
	GameBackground bgNebulas;

	/*INITIALIZE ALLEGRO 5*/
	al_init();
	if(!al_init()) {
		al_show_native_message_box(0, "ERROR", "Failed to initialize Allegro 5!", "Press OK to terminate.", 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	/*ALLEGRO VARIABLES*/
	ALLEGRO_DISPLAY *display = 0;
	ALLEGRO_EVENT_QUEUE *eventQueue = 0;
	ALLEGRO_TIMER *timer = 0;
	ALLEGRO_BITMAP *mouseBMP;
	ALLEGRO_FONT *mainFont, *smallFont, *titleFont, *bigFont= NULL;
	ALLEGRO_BITMAP *player, *playerDamaged, *playerLeft, *playerRight, *playerShield, *enemyNormal;
	ALLEGRO_BITMAP *cometBigBMP, *cometSmallBMP, *livesIconRotated;
	ALLEGRO_BITMAP *bulletPlayer, *bulletEnemyBMP;
	ALLEGRO_BITMAP *nebulaBig, *nebulaSmall, *nebulaVerySmall;
	ALLEGRO_BITMAP *gameScreenFast, *gameScreenNebulas, *livesIcon;
	ALLEGRO_BITMAP *tutorialShoot;
	ALLEGRO_BITMAP *pozo;
	ALLEGRO_SAMPLE *introSound;
	ALLEGRO_SAMPLE *bulletSound, *explosionSound, *healthdownSound, *healthupSound;

	/*CREATE DISPLAY*/
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(screenW, screenH);
	if(!display) {
		al_show_native_message_box(0, "ERROR", "Failed to initialize the display!", "Press OK to terminate.", 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_hide_mouse_cursor(display);

	/*INSTALL ADDONS*/
	al_init_font_addon(); addonCheck++;
	al_init_ttf_addon(); addonCheck++;
	al_init_primitives_addon(); addonCheck++;
	al_init_image_addon(); addonCheck++;
	al_install_keyboard(); addonCheck++;
	al_install_mouse(); addonCheck++;
	al_install_audio(); addonCheck++;
	al_init_acodec_addon(); addonCheck++;
	if(addonCheck != 8) {
		al_show_native_message_box(0, "ERROR", "Failed to load Allegro addons!", "Press OK to terminate.", 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	/*FILE LOADING*/

	//LOADING SCREEN
	bigFont = al_load_font("otfpoc.otf", 55, 0);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(bigFont, al_map_rgb(255,255,255), screenW/2.5, screenH/2, 0, "LOADING.");
	al_flip_display();

	//LOADING IMAGES
	titleFont = al_load_font("otfpoc.otf", 125, 0);
	mainFont = al_load_font("otfpoc.otf", 35, 0);
	smallFont = al_load_font("otfpoc.otf", 15, 0);

	ALLEGRO_PATH *imagesP = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(imagesP, "images");
	al_change_directory(al_path_cstr(imagesP, '/'));
	al_destroy_path(imagesP);

	mouseBMP = al_load_bitmap("mouse.png");
	pozo = al_load_bitmap("pozo.png");

	player = al_load_bitmap("player.png");
	playerDamaged = al_load_bitmap("playerDamaged.png");
	playerLeft = al_load_bitmap("playerLeft.png");
	playerRight = al_load_bitmap("playerRight.png");
	playerShield = al_load_bitmap("shield.png");

	enemyNormal = al_load_bitmap("enemyShip.png");

	cometBigBMP = al_load_bitmap("meteorBig.png");
	cometSmallBMP = al_load_bitmap("meteorSmall.png");

	bulletPlayer = al_load_bitmap("laserGreen.png");
	bulletEnemyBMP = al_load_bitmap("laserRed.png");

	nebulaBig = al_load_bitmap("nebulaBig.png");
	nebulaSmall = al_load_bitmap("nebulaSmall.png");
	nebulaVerySmall = al_load_bitmap("nebulaVerySmall.png");

	gameScreenFast = al_load_bitmap("movingBGlines.png");
	al_convert_mask_to_alpha(gameScreenFast, al_map_rgb(35,10,55));
	gameScreenNebulas = al_load_bitmap("movingBGnebulas.png");
	al_convert_mask_to_alpha(gameScreenNebulas, al_map_rgb(35,10,55));
	livesIcon = al_load_bitmap("life.png");
	livesIconRotated = al_load_bitmap("life180.png");

	tutorialShoot = al_load_bitmap("tutorialShoot.png");

	al_draw_text(bigFont, al_map_rgb(255,255,255), screenW/2.5, screenH/2, 0, "LOADING..");
	al_flip_display();

	//LOADING SOUNDS
	al_reserve_samples(5);

	ALLEGRO_PATH *soundsP = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(soundsP, "sounds");
	al_change_directory(al_path_cstr(soundsP, '/'));
	al_destroy_path(soundsP);

	introSound = al_load_sample("introSound.wav");

	bulletSound = al_load_sample("bulletSound.wav");
	explosionSound = al_load_sample("explosionSound.wav");
	healthdownSound = al_load_sample("healthdownSound.wav");
	healthupSound = al_load_sample("healthupSound.wav");

	al_draw_text(bigFont, al_map_rgb(255,255,255), screenW/2.5, screenH/2, 0, "LOADING...");
	al_flip_display();

start:
	bPlay->setHover(false);
	objectCount = 0;
	shieldTimer = 5;
	enemyFireTimer = 0;

	/*FADE-IN COUNTERS*/
	counter255r = 35;
	counter255g = 10;
	counter255b = 55;
	counter185r = 35;
	counter185g = 10;
    counter185b = 55;
	counterHelp185r = 35;
	counterHelp185g = 10;
	counterHelp185b = 55;
	counterHelp255r = 35;
	counterHelp255g = 10;
	counterHelp255b = 55;

	/*GAME OBJECT INITIALIZATION*/
	nebulaBigC.init(nebulaBig);
	tutorialShootC.init(tutorialShoot);

	bPlay->init(screenW/2, screenH/2+100, 65, 18, bigFont);
	bHelp->init(screenW/2, screenH/2+140, 65, 18, bigFont);
	bOptn->init(screenW/2, screenH/2+180, 65, 18, bigFont);
	bBack->init(screenW/2, screenH-80, 65, 18, bigFont);
	bExit->init(screenW/2, screenH/2+220, 65, 18, bigFont);
	bMenu->init(screenW/2, screenH/2+40, 65, 18, bigFont);
	bExit2->init(screenW/2, screenH/2+80, 65, 18, bigFont);
	bVolumeP->init(screenW/2+90, screenH/3, 18, 18, bigFont);
	bVolumeM->init(screenW/2-90, screenH/3, 18, 18, bigFont);
	bDifficultyP->init(screenW/2+100, screenH/3+175, 18, 18, bigFont);
	bDifficultyM->init(screenW/2-100, screenH/3+175, 18, 18, bigFont);

	initBullet(bullets, bulletPlayer, bulletSound, explosionSound);
	bulletEnemy->init(bulletEnemy, bulletEnemyBMP, bulletSound, explosionSound, healthdownSound);

	initCometBig(cometsBig, cometBigBMP, healthdownSound);
	initCometSmall(cometsSmall, cometSmallBMP, healthdownSound);
	healthUp->init(healthUp, livesIconRotated, healthupSound);

	enemyShip->init(enemyShip, enemyNormal, explosionSound);

	ship.init(player, playerLeft, playerRight, playerDamaged, playerShield, livesIcon);

	bgStars.init(gameScreenFast, 6, 1);
	bgNebulas.init(gameScreenNebulas, 2, 2);

	/*EQ, TIMER AND REGISTER SOURCES*/
	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0/120);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	/*FINAL PREPERATIONS, START TIMER*/
	running = true;
	ScreenStateC *screenStateC = new ScreenStateC();
	screenStateC->setToState(1);

	srand(time(NULL));

	al_start_timer(timer);
	gameTime = al_current_time();
	al_play_sample(introSound, volume, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

	while(running) {
		if(screenState[TITLESCREEN] && !screenState[GAMESCREEN]) {
			ALLEGRO_EVENT titleEvent;
			al_wait_for_event(eventQueue, &titleEvent);

			if(titleEvent.type == ALLEGRO_EVENT_MOUSE_AXES) {
				mouseX = titleEvent.mouse.x;
				mouseY = titleEvent.mouse.y;
			}

			if(titleEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if(!screenState[HELPSCREEN] && !screenState[OPTIONSCREEN] && !screenState[GAMESCREEN]) {
					if(bPlay->getHover()) {
						if(titleEvent.mouse.button & 1) {
							screenStateC->setToState(2);
						}
					}
					if(bHelp->getHover()) {
						if(titleEvent.mouse.button & 1) {
							screenStateC->setToState(3);
						}
					}
					if(bOptn->getHover()) {
						if(titleEvent.mouse.button & 1) {
							screenStateC->setToState(4);
						}
					}
					if(bExit->getHover()) {
						if(titleEvent.mouse.button & 1) {
							screenState[TITLESCREEN] = false;
							running = false;
						}
					}
				}
				else if(screenState[HELPSCREEN]) {
					if(bBack->getHover() & 1) {
						screenStateC->setToState(1);
					}
				}
				else if(screenState[OPTIONSCREEN]) {
					if(bBack->getHover() & 1) {
						screenStateC->setToState(1);
					}
					if(bVolumeP->getHover() & 1) {
						if(volume == 0.0) {
							volume = 0.2;
						}
						else if(volume == 0.2) {
							volume = 0.4;
						}
						else if(volume == 0.4) {
							volume = 0.6;
						}
						else if(volume == 0.6) {
							volume = 0.8;
						}
						else if(volume == 0.8) {
							volume = 1.0;
						}
					}
					if(bVolumeM->getHover() & 1) {
						if(volume == 0.2) {
							volume = 0.0;
						}
						else if(volume == 0.4) {
							volume = 0.2;
						}
						else if(volume == 0.6) {
							volume = 0.4;
						}
						else if(volume == 0.8) {
							volume = 0.6;
						}
						else if(volume == 1.0) {
							volume = 0.8;
						}
					}
					if(bDifficultyP->getHover() & 1) {
						if(difficulty[EASY]) {
							difficulty[EASY] = false;
							difficulty[NORM] = true;
							difficulty[HARD] = false;
						}
						else if(difficulty[NORM]) {
							difficulty[EASY] = false;
							difficulty[NORM] = false;
							difficulty[HARD] = true;
						}
					}
					if(bDifficultyM->getHover() & 1) {
						if(difficulty[NORM]) {
							difficulty[EASY] = true;
							difficulty[NORM] = false;
							difficulty[HARD] = false;
						}
						else if(difficulty[HARD]) {
							difficulty[EASY] = false;
							difficulty[NORM] = true;
							difficulty[HARD] = false;
						}
					}
				}
			}

			if(titleEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}

			if(titleEvent.type == ALLEGRO_EVENT_KEY_UP) {
				switch(titleEvent.keyboard.keycode) {
				case ALLEGRO_KEY_F3:
					if(keys[F3])
						keys[F3] = false;
					else if(!keys[F3])
						keys[F3] = true;
					break;
				}
			}

			if(titleEvent.type == ALLEGRO_EVENT_TIMER) {
				rendering = true;

				if(screenState[HELPSCREEN]) {
					tutorialShootC.update();

					if(tutorialShootC.getFinal()) {
						if(counterHelp185r < 185)
							counterHelp185r++;
						if(counterHelp185g < 185)
							counterHelp185g++;
						if(counterHelp185b < 185)
							counterHelp185b++;

						if(counterHelp255r < 255)
							counterHelp255r++;
						if(counterHelp255g < 255)
							counterHelp255g++;
						if(counterHelp255b < 255)
							counterHelp255b++;
					}
				}

				if(nebulaBigC.getFinal()) {
					if(counter185r < 185)
						counter185r++;
					if(counter185g < 185)
						counter185g++;
					if(counter185b < 185)
						counter185b++;

					if(counter255r < 255)
						counter255r++;
					if(counter255g < 255)
						counter255g++;
					if(counter255b < 255)
						counter255b++;

					if(counter255g == 254);
					bPlay->hoverDetect();
					bHelp->hoverDetect();
					bOptn->hoverDetect();
					bBack->hoverDetect();
					bExit->hoverDetect();
					bVolumeP->hoverDetect();
					bVolumeM->hoverDetect();
					bDifficultyP->hoverDetect();
					bDifficultyM->hoverDetect();
				}

				nebulaBigC.update();

				framesElapsed++;
				seconds = framesElapsed/120;

				if(seconds >= 60) {
					minutes++;
					seconds = 0;
					framesElapsed = 0;
				}

				frames++;
				if(al_current_time() - gameTime >= 1) {
					gameTime = al_current_time();
					gameFPS = frames;
					frames = 0;
				}
			}

			if(rendering && al_is_event_queue_empty(eventQueue)) {
				rendering = false;

				al_clear_to_color(al_map_rgb(35,10,55));

				if(!screenState[HELPSCREEN] && !screenState[OPTIONSCREEN]) {
					nebulaBigC.render();

					al_draw_text(titleFont, al_map_rgb(counter255r,counter255g,counter255b), screenW/2-30, screenH/7+20, 1, "POZO");
					al_draw_text(titleFont, al_map_rgb(counter255r,counter255g,counter255b), screenW/2, screenH/4+50, 1, "The Space Man");
					al_draw_text(bigFont, al_map_rgb(counter255r,counter255g,counter255b), screenW/2, screenH/2.0+300, ALLEGRO_ALIGN_CENTRE, author);
					al_draw_text(smallFont, al_map_rgb(counter255r,counter255g,counter255b), screenW/1.56, screenH/3+70, 1, version);
					al_draw_bitmap(pozo,100,100,0);

					/*DEBUG MODE*/
					if(keys[F3]) {
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 5, ALLEGRO_ALIGN_LEFT, "FPS: %i", gameFPS);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 17, ALLEGRO_ALIGN_LEFT, "Time: %i min, %i sec", minutes, seconds);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 29, ALLEGRO_ALIGN_LEFT, "Frames: %i", framesElapsed);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 41, ALLEGRO_ALIGN_LEFT, "Mouse X: %i", mouseX);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 53, ALLEGRO_ALIGN_LEFT, "Mouse Y: %i", mouseY);
						al_draw_filled_rectangle(bPlay->getX() - bPlay->getBoundX(), bPlay->getY(), bPlay->getX() + bPlay->getBoundX(), bPlay->getY() + bPlay->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bHelp->getX() - bHelp->getBoundX(), bHelp->getY(), bHelp->getX() + bHelp->getBoundX(), bHelp->getY() + bHelp->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bOptn->getX() - bOptn->getBoundX(), bOptn->getY(), bOptn->getX() + bOptn->getBoundX(), bOptn->getY() + bOptn->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bExit->getX() - bExit->getBoundX(), bExit->getY(), bExit->getX() + bExit->getBoundX(), bExit->getY() + bExit->getBoundY()*2, al_map_rgb(0,255,20));
					}

					bPlay->render(1);
					bHelp->render(2);
					bOptn->render(3);
					bExit->render(5);
				}
				else if(screenState[HELPSCREEN] && !screenState[OPTIONSCREEN]) {
					tutorialShootC.render();

					al_draw_text(bigFont, al_map_rgb(counterHelp255r,counterHelp255g,counterHelp255b), screenW/5, 40, 0, "INTRO");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/6, 0, "POZO-The Space man is a space invaders type game,");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/6+35, 0, "in which the                is to get the highest");
					al_draw_text(mainFont, al_map_rgb(counterHelp255r,counterHelp255g,counterHelp255b), screenW/30, screenH/6+35, 0, "                  objective");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/6+70, 0, "possible score.           are earned by destroying");
					al_draw_text(mainFont, al_map_rgb(counterHelp255r,counterHelp255g,counterHelp255b), screenW/30+5, screenH/6+70, 0, "                 Points");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/6+105, 0, "comets and enemy space ships.");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/6+140, 0, "Enemy commoness scales with difficulty setting.");

					al_draw_text(bigFont, al_map_rgb(counterHelp255r,counterHelp255g,counterHelp255b), screenW/5, screenH/2-25, 0, "POWER UPS");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/2+70, 0, "During the game you might pick up health power");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/2+105, 0, "ups which will replenish your lives. The higher");
					al_draw_text(mainFont, al_map_rgb(counterHelp185r,counterHelp185g,counterHelp185b), screenW/30, screenH/2+140, 0, "the difficulty, the rarer the power ups!");

					/*DEBUG MODE*/
					if(keys[F3]) {
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 5, ALLEGRO_ALIGN_LEFT, "FPS: %i", gameFPS);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 17, ALLEGRO_ALIGN_LEFT, "Time: %i min, %i sec", minutes, seconds);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 29, ALLEGRO_ALIGN_LEFT, "Frames: %i", framesElapsed);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 41, ALLEGRO_ALIGN_LEFT, "Mouse X: %i", mouseX);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 53, ALLEGRO_ALIGN_LEFT, "Mouse Y: %i", mouseY);
						al_draw_filled_rectangle(bBack->getX() - bBack->getBoundX(), bBack->getY(), bBack->getX() + bBack->getBoundX(), bBack->getY() + bBack->getBoundY()*2, al_map_rgb(0,255,20));
					}

					bBack->render(4);
				}
				else if(!screenState[HELPSCREEN] && screenState[OPTIONSCREEN]) {
					/*DEBUG MODE*/
					if(keys[F3]) {
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 5, ALLEGRO_ALIGN_LEFT, "FPS: %i", gameFPS);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 17, ALLEGRO_ALIGN_LEFT, "Time: %i min, %i sec", minutes, seconds);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 29, ALLEGRO_ALIGN_LEFT, "Frames: %i", framesElapsed);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 41, ALLEGRO_ALIGN_LEFT, "Mouse X: %i", mouseX);
						al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 53, ALLEGRO_ALIGN_LEFT, "Mouse Y: %i", mouseY);
						al_draw_filled_rectangle(bBack->getX() - bBack->getBoundX(), bBack->getY(), bBack->getX() + bBack->getBoundX(), bBack->getY() + bBack->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bVolumeP->getX() - bVolumeP->getBoundX(), bVolumeP->getY(), bVolumeP->getX() + bVolumeP->getBoundX(), bVolumeP->getY() + bVolumeP->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bVolumeM->getX() - bVolumeM->getBoundX(), bVolumeM->getY(), bVolumeM->getX() + bVolumeM->getBoundX(), bVolumeM->getY() + bVolumeM->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bDifficultyP->getX() - bDifficultyP->getBoundX(), bDifficultyP->getY(), bDifficultyP->getX() + bDifficultyP->getBoundX(), bDifficultyP->getY() + bDifficultyP->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bDifficultyM->getX() - bDifficultyM->getBoundX(), bDifficultyM->getY(), bDifficultyM->getX() + bDifficultyM->getBoundX(), bDifficultyM->getY() + bDifficultyM->getBoundY()*2, al_map_rgb(0,255,20));
					}

					al_draw_text(bigFont, al_map_rgb(255,255,255), screenW/2, screenH/3-60, ALLEGRO_ALIGN_CENTRE, "Volume");
					if(volume == 0.0)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "0%");
					else if(volume == 0.2)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "20%");
					else if(volume == 0.4)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "40%");
					else if(volume == 0.6)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "60%");
					else if(volume == 0.8)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "80%");
					else if(volume == 1.0)
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+5, ALLEGRO_ALIGN_CENTRE, "100%");

					al_draw_text(bigFont, al_map_rgb(255,255,255), screenW/2, (screenH/3+175)-60, ALLEGRO_ALIGN_CENTRE, "Difficulty");
					if(difficulty[EASY])
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+180, ALLEGRO_ALIGN_CENTRE, "EASY");
					else if(difficulty[NORM])
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+180, ALLEGRO_ALIGN_CENTRE, "NORM");
					else if(difficulty[HARD])
						al_draw_text(mainFont, al_map_rgb(255,255,255), screenW/2, screenH/3+180, ALLEGRO_ALIGN_CENTRE, "HARD");

					bBack->render(4);
					bVolumeP->render(7);
					bVolumeM->render(8);
					bDifficultyP->render(9);
					bDifficultyM->render(10);
				}

				al_draw_bitmap(mouseBMP, mouseX, mouseY, 0);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
		}

		/**********************************************************
						G A M E         L O O P
		**********************************************************/

		if(screenState[GAMESCREEN] && !screenState[TITLESCREEN]) {

			ALLEGRO_EVENT gameEvent;
			al_wait_for_event(eventQueue, &gameEvent);

			if(gameEvent.type == ALLEGRO_EVENT_MOUSE_AXES) {
				mouseX = gameEvent.mouse.x;
				mouseY = gameEvent.mouse.y;
			}

			if(gameEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if(screenState[MENUSCREEN]) {
					if(bExit2->getHover()) {
							if(gameEvent.mouse.button & 1) {
								screenState[GAMESCREEN] = false;
								running = false;
							}
					}
					if(bMenu->getHover()) {
							if(gameEvent.mouse.button & 1) {
								screenStateC->setToState(1);
								goto start;
							}
					}
				}
			}

			if(gameEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}

			if(gameEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch(gameEvent.keyboard.keycode) {
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					spacePressed = true;
					break;
				case ALLEGRO_KEY_W:
					keys[W] = true;
					if(!wPressed)
						wPressed = true;
					break;
				case ALLEGRO_KEY_S:
					keys[S] = true;
					if(!sPressed)
						sPressed = true;
					break;
				case ALLEGRO_KEY_A:
					keys[A] = true;
					if(!aPressed)
						aPressed = true;
					break;
				case ALLEGRO_KEY_D:
					keys[D] = true;
					if(!dPressed)
						dPressed = true;
					break;
				}
			}

			if(gameEvent.type == ALLEGRO_EVENT_KEY_UP) {
				switch(gameEvent.keyboard.keycode) {
				case ALLEGRO_KEY_F3:
					if(keys[F3])
						keys[F3] = false;
					else if(!keys[F3])
						keys[F3] = true;
					break;
				case ALLEGRO_KEY_ESCAPE:
					if(screenStateC->getState() != 5 && screenState[GAMESCREEN])
						screenStateC->setToState(5);
					else if(screenStateC->getState() == 5 && screenState[GAMESCREEN])
						screenStateC->setToState(2);
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					if(ship.getLives() > 0) {
						fireBullet(bullets, ship.getX(), ship.getY()-ship.getBoundY());
					}
					break;
				case ALLEGRO_KEY_W:
					keys[W] = false;
					break;
				case ALLEGRO_KEY_S:
					keys[S] = false;
					break;
				case ALLEGRO_KEY_A:
					keys[A] = false;
					break;
				case ALLEGRO_KEY_D:
					keys[D] = false;
					break;
				}
			}

			if(gameEvent.type == ALLEGRO_EVENT_TIMER) {
				rendering = true;

				if(screenState[MENUSCREEN]) {
					bExit2->hoverDetect();
					bMenu->hoverDetect();
				}

				if(wPressed && sPressed && aPressed && dPressed &&spacePressed) {
					if(counterGame185r > 35)
						counterGame185r--;
					if(counterGame185g > 10)
						counterGame185g--;
					if(counterGame185b > 55)
						counterGame185b--;
				}
				else {
					if(counterGame185r < 185)
						counterGame185r++;
					if(counterGame185g < 185)
						counterGame185g++;
					if(counterGame185b < 185)
						counterGame185b++;
				}

				if(!screenState[MENUSCREEN] && ship.getLives() > 0) {

					bgStars.update();
					bgNebulas.update();

					updateBullet(bullets);
					collideBullet(bullets, cometsBig, cometsSmall, enemyShip, ship);

					bulletEnemy->update(bulletEnemy);
					bulletEnemy->collide(bulletEnemy, ship);

					startCometBig(cometsBig);
					updateCometBig(cometsBig);
					collideCometBig(cometsBig, ship);

					startCometSmall(cometsSmall);
					updateCometSmall(cometsSmall);
					collideCometSmall(cometsSmall, ship);

					healthUp->start(healthUp);
					healthUp->update(healthUp);
					healthUp->collide(healthUp, ship);

					enemyShip->start(enemyShip);
					enemyShip->update(enemyShip, ship);
					enemyShip->collide(enemyShip, ship);

					if(shieldTimer < 120*10) {
						shieldTimer++;
						ship.setShield(0);
					}
					else if(shieldTimer == 1200) {
						ship.setShield(1);
					}

					if(keys[W]) {
						ship.moveUp();
					}
					else if(keys[S]) {
						ship.moveDown();
					}
					if(keys[A]) {
						ship.moveLeft();
					}
					else if(keys[D]) {
						ship.moveRight();
					}

					framesElapsed++;
					seconds = framesElapsed/120;

					if(seconds >= 60) {
						minutes++;
						seconds = 0;
						framesElapsed = 0;
					}
				}

				frames++;
				if(al_current_time() - gameTime >= 1) {
					gameTime = al_current_time();
					gameFPS = frames;
					frames = 0;
				}
			}

			if(rendering && al_is_event_queue_empty(eventQueue)) {
				rendering = false;

				al_clear_to_color(al_map_rgb(35,10,55));

				bgStars.render();
				bgNebulas.render();

				renderBullet(bullets);

				renderCometBig(cometsBig);
				renderCometSmall(cometsSmall);

				bulletEnemy->render(bulletEnemy);

				healthUp->render(healthUp);
				enemyShip->render(enemyShip);
				ship.render();

				if(counterGame185r > 36) {
					al_draw_text(mainFont, al_map_rgb(counterGame185r,counterGame185g,counterGame185b), screenW/2, screenH/6, 1, "Use WSAD to move");
					al_draw_text(mainFont, al_map_rgb(counterGame185r,counterGame185g,counterGame185b), screenW/2, screenH/5+30, 1, "Use SPACE to shoot");
				}

				if(ship.getLives() <= 0) {
					al_draw_text(titleFont, al_map_rgb(255,255,255), screenW/2, screenH/2-80, 1, "GAME OVER");
				}

				al_draw_filled_rectangle(5, 41, shieldTimer/10, 59, al_map_rgb(255,204,0));
				al_draw_rectangle(5, 41, 1200/10, 59, al_map_rgb(255,255,255), 2);
				al_draw_textf(smallFont, al_map_rgb(255,255,255), 5, 65, 0, "Score: %i", ship.getScore());

				/*DEBUG MODE*/
				if(keys[F3]) {
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 77, ALLEGRO_ALIGN_LEFT, "FPS: %i", gameFPS);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 89, ALLEGRO_ALIGN_LEFT, "Time: %i min, %i sec", minutes, seconds);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 101, ALLEGRO_ALIGN_LEFT, "Frames: %i", framesElapsed);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 113, ALLEGRO_ALIGN_LEFT, "Mouse X: %i", mouseX);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 125, ALLEGRO_ALIGN_LEFT, "Mouse Y: %i", mouseY);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 137, ALLEGRO_ALIGN_LEFT, "Objects: %i", objectCount);
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 149, ALLEGRO_ALIGN_LEFT, "Lives: %i", ship.getLives());
					al_draw_textf(smallFont, al_map_rgb(0,255,0), 5, 161, ALLEGRO_ALIGN_LEFT, "Shield: %i", ship.getShield());

					al_draw_bitmap(mouseBMP, mouseX, mouseY, 0);
				}

				if(screenState[MENUSCREEN]) {
					/*DEBUG MODE*/
					if(keys[F3]) {
						al_draw_filled_rectangle(bExit2->getX() - bExit2->getBoundX(), bExit2->getY(), bExit2->getX() + bExit2->getBoundX(), bExit2->getY() + bExit2->getBoundY()*2, al_map_rgb(0,255,20));
						al_draw_filled_rectangle(bMenu->getX() - bMenu->getBoundX(), bMenu->getY(), bMenu->getX() + bMenu->getBoundX(), bMenu->getY() + bMenu->getBoundY()*2, al_map_rgb(0,255,20));
					}

					if(ship.getLives() > 0)
						al_draw_text(titleFont, al_map_rgb(255,255,255), screenW/2, screenH/2-80, 1, "PAUSED");
					else if(ship.getLives() <= 0)
						al_draw_text(titleFont, al_map_rgb(255,255,255), screenW/2, screenH/2-80, 1, "GAME OVER");

					bExit2->render(5);
					bMenu->render(6);

					al_draw_bitmap(mouseBMP, mouseX, mouseY, 0);
				}

				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
		}
	}

	delete screenStateC;
	delete bPlay;
	delete bHelp;
	delete bOptn;
	delete bBack;
	delete bExit;
	delete bMenu;
	delete bExit2;
	delete bVolumeP;
	delete bVolumeM;
	delete bDifficultyP;
	delete bDifficultyM;

	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);
	al_destroy_bitmap(mouseBMP);
	al_destroy_font(mainFont);
	al_destroy_font(smallFont);
	al_destroy_font(titleFont);
	al_destroy_font(bigFont);

	al_destroy_bitmap(player);
	al_destroy_bitmap(playerDamaged);
	al_destroy_bitmap(playerLeft);
	al_destroy_bitmap(playerRight);
	al_destroy_bitmap(playerShield);
	al_destroy_bitmap(bulletPlayer);
	al_destroy_bitmap(nebulaBig);
	al_destroy_bitmap(nebulaSmall);
	al_destroy_bitmap(nebulaVerySmall);
	al_destroy_bitmap(livesIcon);

	al_destroy_sample(bulletSound);
	al_destroy_sample(introSound);

	return 0;
}
