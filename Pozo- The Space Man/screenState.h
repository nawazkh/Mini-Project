#include "globals.h"

class ScreenStateC {
private:
	int stateID;
public:
	~ScreenStateC() {ScreenStateC::stateID = 0;}

	void setToState(int state) { // 1(title), 2(game), 3(help), 4(options)
		if(state == 1) {
			screenState[TITLESCREEN] = true;
			screenState[GAMESCREEN] = false;
			screenState[HELPSCREEN] = false;
			screenState[OPTIONSCREEN] = false;
			screenState[MENUSCREEN] = false;
			ScreenStateC::stateID = 1;
		}
		else if(state == 2) {
			screenState[TITLESCREEN] = false;
			screenState[GAMESCREEN] = true;
			screenState[HELPSCREEN] = false;
			screenState[OPTIONSCREEN] = false;
			screenState[MENUSCREEN] = false;
			ScreenStateC::stateID = 2;
		}
		else if(state == 3) {
			screenState[TITLESCREEN] = true;
			screenState[GAMESCREEN] = false;
			screenState[HELPSCREEN] = true;
			screenState[OPTIONSCREEN] = false;
			screenState[MENUSCREEN] = false;
			ScreenStateC::stateID = 3;
		}
		else if(state == 4) {
			screenState[TITLESCREEN] = true;
			screenState[GAMESCREEN] = false;
			screenState[HELPSCREEN] = false;
			screenState[OPTIONSCREEN] = true;
			screenState[MENUSCREEN] = false;
			ScreenStateC::stateID = 4;
		}
		else if(state == 5) {
			screenState[TITLESCREEN] = false;
			screenState[GAMESCREEN] = true;
			screenState[HELPSCREEN] = false;
			screenState[OPTIONSCREEN] = false;
			screenState[MENUSCREEN] = true;
			ScreenStateC::stateID = 5;
		}
	}
	
	int getState() {return ScreenStateC::stateID;}
};