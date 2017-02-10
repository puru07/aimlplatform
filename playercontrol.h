#ifndef PLAYER_CONTROL_H_INCLUDED
#define PLAYER_CONTROL_H_INCLUDED

#include "fssimplewindow.h"
#include "maplogic.h"

class PlayerControl {
private:
	int posX, posY;
	char type;
public:
	PlayerControl(char c);
	~PlayerControl(void);
	void MoveKey(int key, MapLogic *mplp);
	void FindPosition(MapLogic *mplp);
};

#endif