#pragma once

/*GAME INFO*/
const char *author = "- by Rasiq Nihar Nawaz";// to displayed when the game starts
const char *version = "Ver Beta one-O-one";//posh version name

/*SHIELD COUNTER*/
int shieldTimer = 5;// the time for which the sheild will stay
int enemyFireTimer = 0;//enemy starts fighting as soon as the enemy appears

/*VOLUME SWITCH*/
double volume = 1.0;

/*DIFFICULTY SETTING*/
enum DIFFICULTY {EASY, NORM, HARD};
bool difficulty[] = {false, true, false};

/*MEMORY TRACKING*/
int objectCount = 0;

/*KEYS*/
enum KEYS {W, S, A, D, SPACE, F3};
bool keys[] = {false, false, false, false, false, false};

bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;
bool spacePressed = false;

/*SCREEN STATE*/
enum SCREENSTATE {TITLESCREEN, GAMESCREEN, HELPSCREEN, OPTIONSCREEN, MENUSCREEN};
bool screenState[] = {false, false, false, false, false};

/*WINDOW DIMENSIONS/RESOLUTION*/
unsigned short screenW = 1366;//screen width
unsigned short screenH = 768;//screen height

/*MOUSE POSITION*/
int mouseX = 0;//mouse coordinates
int mouseY = 0;

/*FADE-IN COUNTERS*/
int counter255r = 35;
int counter255g = 10;
int counter255b = 55;
int counter185r = 35;
int counter185g = 10;
int counter185b = 55;
int counterHelp185r = 35;
int counterHelp185g = 10;
int counterHelp185b = 55;
int counterHelp255r = 35;
int counterHelp255g = 10;
int counterHelp255b = 55;
int counterGame185r = 35;
int counterGame185g = 10;
int counterGame185b = 55;
