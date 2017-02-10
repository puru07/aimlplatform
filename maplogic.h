#ifndef MAPLOGIC_H_IS_INCLUDED
#define MAPLOGIC_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "aimltools.h"

class MapLogic {
private:
	int sizeX;
	int sizeY;
	int block_size;
	char *mapchar;
	void ClearUp(void);
public:
	MapLogic(void);
	~MapLogic(void);
	void LoadEmpty(int x, int y);
	void LoadRandom(int x, int y);
	int LoadFromFile(char *path);
	void SaveMap(int filecount);
	char GetCharValue(int x, int y);
	void SetCharValue(char c, int x, int y);
	void Draw(void);
	void ClearMap(void);
	int GetSizeX(void);
	int GetSizeY(void);
	int GetBlockSize(void);
	char *GetCharPointer(void);
	AIMLMap *aimlmapp;
};

#endif