#include "playercontrol.h"

PlayerControl::PlayerControl(char c) {
	type = c;
	posX = 0;
	posY = 0;
}

PlayerControl::~PlayerControl(void) {
	posX = 0;
	posY = 0;
}

void PlayerControl::FindPosition(MapLogic *mplp){
	int x = mplp->GetSizeX();
	int y = mplp->GetSizeY();
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			if (mplp->GetCharValue(i, j) == type) {
				posX = i;
				posY = j;
			}
		}
	}
}

void PlayerControl::MoveKey(int key, MapLogic *mplp) {
	if (FSKEY_UP == key)
	{
		if (posY > 0) {
			posY--;
		}
	}
	if (FSKEY_DOWN == key)
	{
		if (posY < (mplp->GetSizeY()) - 1) {
			posY++;
		}
	}
	if (FSKEY_LEFT == key)
	{
		if (posX > 0) {
			posX--;
		}
	}
	if (FSKEY_RIGHT == key)
	{
		if (posX < (mplp->GetSizeX()) - 1) {
			posX++;
		}
	}
}