#include "maplogic.h"

MapLogic::MapLogic(void) {
	sizeX = 10;
	sizeY = 10;
	block_size = 10;
	mapchar = nullptr;
	aimlmapp = nullptr;
}

MapLogic::~MapLogic(void) {
	ClearUp();
}

void MapLogic::ClearUp(void) {
	if (mapchar != nullptr) {
		free(mapchar);
	}
	mapchar = nullptr;
	if (aimlmapp != nullptr) {
		free(aimlmapp);
	}
	aimlmapp = nullptr;
}

void MapLogic::LoadEmpty(int x, int y) {
	sizeX = x;
	sizeY = y;
	mapchar = (char *)malloc(sizeX*sizeY*sizeof(char) + 1);
	for (int i = 0; i < sizeX * sizeY; i++) {
		mapchar[i] = '0';
	}
	mapchar[sizeX * sizeY] = 0;
	block_size = 600 / (max(sizeX, sizeY));
}

void MapLogic::LoadRandom(int x, int y) {
	sizeX = x;
	sizeY = y;
	mapchar = (char *)malloc(sizeX*sizeY*sizeof(char)+1);

	block_size = 600 / (max(sizeX, sizeY));
}

int MapLogic::LoadFromFile(char *path) {
	aimlmapp = new AIMLMap(path);

	if (!aimlmapp->readMAP()){
		delete aimlmapp;
		aimlmapp = nullptr;
		return 0;
	}
	sizeX = aimlmapp->getColumn();
	sizeY = aimlmapp->getRow();

	mapchar = (char *)malloc(sizeX*sizeY*sizeof(char)+1);
	char *p = aimlmapp->getMap();
	for (int i = 0; i < sizeX * sizeY; i++) {
		mapchar[i] = p[i];
	}
	mapchar[sizeX * sizeY] = 0;

	delete aimlmapp;
	aimlmapp = nullptr;

	block_size = 600 / (max(sizeX, sizeY));
	return 1;
}

void MapLogic::ClearMap(void) {
	for (int i = 0; i < sizeX * sizeY; i++) {
		mapchar[i] = '0';
	}
}

void MapLogic::SaveMap(int filecount) {
	char filename[30];
	sprintf(filename, "aimap%d.txt", filecount);

	aimlmapp = new AIMLMap;
	aimlmapp->writeName(filename);
	aimlmapp->putMap(sizeY, sizeX, GetCharPointer());
	aimlmapp->writeToFile();

	delete aimlmapp;
	aimlmapp = nullptr;
}

char MapLogic::GetCharValue(int x, int y) {
	if (mapchar == nullptr || x >= sizeX || y >= sizeY) {
		printf("get char value err!\n");
		return 0;
	}
	return mapchar[y * sizeX + x];
}

void MapLogic::SetCharValue(char c, int x, int y) {
	if (mapchar == nullptr || x >= sizeX || y >= sizeY) {
		printf("set char value err!\n");
		return;
	}
	mapchar[y * sizeX + x] = c;
}

void MapLogic::Draw(void) {
	if (mapchar == nullptr) {
		printf("draw map err\n");
		return;
	}
	glBegin(GL_QUADS);
	for (int j = 0; j < sizeY; j++) {
		for (int i = 0; i < sizeX; i++) {
			switch (mapchar[i + j *sizeX]) {
			case '0':
				break;
			case '1':
				glColor3ub(0, 0, 255);
				glVertex2i(
					0 + i * block_size,
					0 + j * block_size);
				glVertex2i(
					0 + i * block_size,
					block_size + j * block_size);
				glVertex2i(
					block_size + i * block_size,
					block_size + j * block_size);
				glVertex2i(
					block_size + i * block_size,
					0 + j * block_size);
				break;
			case 'p':
				glColor3ub(0, 0, 255);
				break;
			case 'e':
				glColor3ub(0, 0, 255);
				break;
			case 's':
				glColor3ub(255, 255, 0);
				glVertex2i(
					0 + i * block_size +5,
					0 + j * block_size +5);
				glVertex2i(
					0 + i * block_size +5,
					block_size + j * block_size -5);
				glVertex2i(
					block_size + i * block_size -5,
					block_size + j * block_size -5);
				glVertex2i(
					block_size + i * block_size -5,
					0 + j * block_size +5);
				break;
			case 'm':
				glColor3ub(255, 0, 255);
				glVertex2i(
					0 + i * block_size + 5,
					0 + j * block_size + 5);
				glVertex2i(
					0 + i * block_size + 5,
					block_size + j * block_size - 5);
				glVertex2i(
					block_size + i * block_size - 5,
					block_size + j * block_size - 5);
				glVertex2i(
					block_size + i * block_size - 5,
					0 + j * block_size + 5);
				break;
			}
		}
	}
	glEnd();

	glColor3ub(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xff00);
	glBegin(GL_LINES);
	for (int j = 0; j <= sizeY; j++) {
		glVertex2i(
			0,
			0 + j * block_size);
		glVertex2i(
			sizeX * block_size,
			0 + j * block_size);
	}
	for (int i = 0; i <= sizeX; i++) {
		glVertex2i(
			0 + i * block_size,
			0);
		glVertex2i(
			0 + i * block_size,
			sizeY * block_size);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

int MapLogic::GetSizeX(void) {
	return sizeX;
}

int MapLogic::GetSizeY(void) {
	return sizeY;
}

int MapLogic::GetBlockSize(void) {
	return block_size;
}

char *MapLogic::GetCharPointer(void){
	return mapchar;
}