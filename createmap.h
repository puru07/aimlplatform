#ifndef CREATEMAP_H_IS_INCLUDED
#define CREATEMAP_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "maplogic.h"

#define DEF_MAP_SIZE 10
#define MAX_MAP_SIZE 30
#define MIN_MAP_SIZE 5

extern int global_state;

class CreateMap {
private:
	int pos;
	int sizeX, sizeY;
	int flagX, flagY;
	int filecount;
	int state;
	int block_size;
	void ClearUp(void);
	void GetKey(void);
	void Draw(void);
	void GetKey2(void);
	void Draw2(void);
	MapLogic *maplogicp;
	char msg[30];
	char msg2[30];
	char posmsg[30];
	char msg3[30];
public:
	CreateMap(void);
	~CreateMap(void);
	void Launch(void);
};

#endif