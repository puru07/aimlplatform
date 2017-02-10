#ifndef PLAYMODE_H_IS_INCLUDED
#define PLAYMODE_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "maplogic.h"
#include "aimltools.h"
#include "playercontrol.h"

#define SLEEP_INTERVAL 200;

extern int global_state;

class PlayMode {
private:
	MapLogic *maplogicp;
	PlayerControl *userp;
	PlayerControl *enemyp;
	int state;
	int block_size;
	int filecount;
	void ClearUp(void);
	void GetKey(void);
	void Draw(void);
	void GetKey2(void);
	void Draw2(void);
public:
	PlayMode(void);
	~PlayMode(void);
	void Launch(void);
};

#endif