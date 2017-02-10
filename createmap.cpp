#include "createmap.h"

CreateMap::CreateMap(void) {
	filecount = 0;
	maplogicp = nullptr;
	sizeX = DEF_MAP_SIZE;
	sizeY = DEF_MAP_SIZE;
	ClearUp();
}

CreateMap::~CreateMap(void) {
	ClearUp();
}

void CreateMap::ClearUp(void) {
	pos = 350;
	state = 0;
	flagX = 0;
	flagY = 0;
	block_size = 10;
	if (maplogicp != nullptr) {
		free(maplogicp);
	}
	maplogicp = nullptr;
	sprintf(msg, "Create New Map");
	sprintf(msg2, "State Log: aimap%d", filecount);
	sprintf(posmsg, "X: %d Y: %d", flagX, flagY);
	sprintf(msg3, "NULL");
}

void CreateMap::Launch(void) {
	ClearUp();
	while (global_state == 2) {
		/* begin logic part*/
		FsPollDevice();

		if (!state) {
			/* key detection */
			GetKey();
			/* begin drawing part */
			Draw();
		}
		else {
			GetKey2();
			Draw2();
		}

		/* Sleep for a sum of time */
		FsSleep(25);
	}
}

void CreateMap::Draw(void) {
	char sizebuf[30];
	char filebuf[30];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);

	glRasterPos2d(100, 270);
	YsGlDrawFontBitmap16x24("Please select create mode:");
	glRasterPos2d(100, 350);
	YsGlDrawFontBitmap16x24("Modify Exited Map");
	glRasterPos2d(100, 400);
	YsGlDrawFontBitmap16x24("Genertate manually");
	glRasterPos2d(100, 450);
	YsGlDrawFontBitmap16x24("Generate by computer");

	glColor3ub(255, 0, 0);
	sprintf(sizebuf, "size: Q< %d >W x A< %d >S", sizeX, sizeY);
	glRasterPos2d(100, 520);
	YsGlDrawFontBitmap16x24(sizebuf);

	sprintf(filebuf, "filename: Z< aimap%d.txt >X", filecount);
	glRasterPos2d(100, 560);
	YsGlDrawFontBitmap16x24(filebuf);

	glBegin(GL_LINES);
	glVertex2i(90, pos - 30);
	glVertex2i(430, pos - 30);

	glVertex2i(430, pos - 30);
	glVertex2i(430, pos + 10);

	glVertex2i(430, pos + 10);
	glVertex2i(90, pos + 10);

	glVertex2i(90, pos + 10);
	glVertex2i(90, pos - 30);
	glEnd();

	FsSwapBuffers();
}

void CreateMap::GetKey(void) {
	int key = FsInkey();
	if (FSKEY_ESC == key)
	{
		global_state = 1; //go back to menu;
	}
	if (FSKEY_RIGHT == key || FSKEY_DOWN == key)
	{
		if (pos < 450) {
			pos = pos + 50;
		}
	}
	if (FSKEY_LEFT == key || FSKEY_UP == key)
	{
		if (pos > 350) {
			pos = pos - 50;
		}
	}
	if (FSKEY_Q == key)
	{
		if (sizeX > MIN_MAP_SIZE) {
			sizeX = sizeX - 1;
		}
	}
	if (FSKEY_W == key)
	{
		if (sizeX < MAX_MAP_SIZE) {
			sizeX = sizeX + 1;
		}
	}
	if (FSKEY_A == key)
	{
		if (sizeY > MIN_MAP_SIZE) {
			sizeY = sizeY - 1;
		}
	}
	if (FSKEY_S == key)
	{
		if (sizeY < MAX_MAP_SIZE) {
			sizeY = sizeY + 1;
		}
	}
	if (FSKEY_Z == key)
	{
		if (filecount > 0) {
			filecount = filecount - 1;
		}
	}
	if (FSKEY_X == key)
	{
		if (filecount < 100) {
			filecount = filecount + 1;
		}
	}
	if (FSKEY_ENTER == key)
	{
		maplogicp = new MapLogic;
		block_size = 600 / (max(sizeX, sizeY));
		if (pos == 400) {
			maplogicp->LoadEmpty(sizeX, sizeY);
			state = 1;
		}
		else if(pos == 450){
			maplogicp->LoadRandom(sizeX, sizeY);
			state = 1;
		}
		else {
			char filename[30];
			sprintf(filename, "aimap%d.txt", filecount);
			if (!(maplogicp->LoadFromFile(filename))) {
				free(maplogicp);
				maplogicp = nullptr;
			}
			else {
				block_size = maplogicp->GetBlockSize();
				sizeX = maplogicp->GetSizeX();
				sizeY = maplogicp->GetSizeY();
				sprintf(msg2, "State Log: aimap%d", filecount);
				state = 1;
			}
		}
	}
}

void CreateMap::Draw2(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	maplogicp->Draw();

	glColor3ub(0, 0, 0);

	glRasterPos2d(610, 25);
	YsGlDrawFontBitmap8x12("Instructions:");
	glRasterPos2d(610, 50);
	YsGlDrawFontBitmap8x12("Q-Put Wall");
	glRasterPos2d(610, 70);
	YsGlDrawFontBitmap8x12("W-Del Item");
	glRasterPos2d(610, 90);
	YsGlDrawFontBitmap8x12("A-Add Player");
	glRasterPos2d(610, 110);
	YsGlDrawFontBitmap8x12("S-Add Enemy");
	glRasterPos2d(610, 130);
	YsGlDrawFontBitmap8x12("D-Add Score point");
	glRasterPos2d(610, 150);
	YsGlDrawFontBitmap8x12("E-Must Pass Point");
	glRasterPos2d(610, 170);
	YsGlDrawFontBitmap8x12("Z-Save File");
	glRasterPos2d(610, 190);
	YsGlDrawFontBitmap8x12("X-Clear All");

	glRasterPos2d(610, 525);
	YsGlDrawFontBitmap8x12(msg2);
	glRasterPos2d(610, 550);
	YsGlDrawFontBitmap8x12(msg);
	glRasterPos2d(610, 570);
	YsGlDrawFontBitmap8x12(posmsg); 
	glRasterPos2d(610, 590);
	YsGlDrawFontBitmap8x12(msg3);

	glBegin(GL_LINES);
	glVertex2i(600, 0);
	glVertex2i(600, 800);

	glVertex2i(600, 200);
	glVertex2i(800, 200);

	glVertex2i(600, 500);
	glVertex2i(800, 500);

	glColor3ub(255, 0, 0);
	/* draw current flag position*/
	glVertex2i(
		0 + flagX * block_size+2,
		0 + flagY * block_size+2);
	glVertex2i(
		0 + flagX * block_size+2,
		block_size + flagY * block_size-2);

	glVertex2i(
		0 + flagX * block_size+2,
		block_size + flagY * block_size-2);
	glVertex2i(
		block_size + flagX * block_size-2,
		block_size + flagY * block_size-2);

	glVertex2i(
		block_size + flagX * block_size-2,
		block_size + flagY * block_size-2);
	glVertex2i(
		block_size + flagX * block_size-2,
		0 + flagY * block_size+2);

	glVertex2i(
		block_size + flagX * block_size-1,
		0 + flagY * block_size+1);
	glVertex2i(
		0 + flagX * block_size+1,
		0 + flagY * block_size+1);

	glEnd();

	FsSwapBuffers();
}

void CreateMap::GetKey2(void) {
	int key = FsInkey();
	if (FSKEY_ESC == key)
	{
		global_state = 1; //go back to menu;
	}
	if (FSKEY_DOWN == key)
	{
		if (flagY < sizeY - 1) {
			flagY++;
			sprintf(posmsg, "X: %d Y: %d", flagX, flagY);
		}
	}
	if (FSKEY_LEFT == key)
	{
		if (flagX > 0) {
			flagX--;
			sprintf(posmsg, "X: %d Y: %d", flagX, flagY);
		}
	}
	if (FSKEY_RIGHT == key)
	{
		if (flagX < sizeX - 1) {
			flagX++;
			sprintf(posmsg, "X: %d Y: %d", flagX, flagY);
		}
	}
	if (FSKEY_UP == key)
	{
		if (flagY > 0) {
			flagY--;
			sprintf(posmsg, "X: %d Y: %d", flagX, flagY);
		}
	}
	if (FSKEY_Q == key)
	{
		maplogicp->SetCharValue('1', flagX, flagY);
		sprintf(msg, "put wall done");
	}
	if (FSKEY_W == key)
	{
		maplogicp->SetCharValue('0', flagX, flagY);
		sprintf(msg, "delete the item");
	}
	if (FSKEY_A == key)
	{
		maplogicp->SetCharValue('p', flagX, flagY);
		sprintf(msg, "add player done");
	}
	if (FSKEY_S == key)
	{
		maplogicp->SetCharValue('e', flagX, flagY);
		sprintf(msg, "add enemy done");
	}
	if (FSKEY_D == key)
	{
		maplogicp->SetCharValue('s', flagX, flagY);
		sprintf(msg, "add score point done");
	}
	if (FSKEY_E == key)
	{
		maplogicp->SetCharValue('m', flagX, flagY);
		sprintf(msg, "add must pass point");
	}
	if (FSKEY_X == key)
	{
		maplogicp->ClearMap();
		sprintf(msg, "clear the map");
	}
	if (FSKEY_Z == key)
	{
		maplogicp->SaveMap(filecount);
		sprintf(msg, "save file done!");
	}
}
