#include "playmode.h"

PlayMode::PlayMode(void) {
	userp = nullptr;
	enemyp = nullptr;
	filecount = 0;
	maplogicp = nullptr;
	ClearUp();
}

PlayMode::~PlayMode(void) {
	ClearUp();
}

void PlayMode::ClearUp(void) {
	state = 0;
	block_size = 10;
	if (maplogicp != nullptr) {
		free(maplogicp);
	}
	maplogicp = nullptr;
	if (userp != nullptr) {
		free(userp);
	}
	userp = nullptr;
	if (enemyp != nullptr) {
		free(enemyp);
	}
	enemyp = nullptr;
}

void PlayMode::Launch(void) {
	ClearUp();
	while (global_state == 3) {
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

void PlayMode::GetKey(void) {
	int key = FsInkey();
	if (FSKEY_ESC == key)
	{
		global_state = 1; //go back to menu;
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
		char filename[30];
		maplogicp = new MapLogic;
		sprintf(filename, "aimap%d.txt", filecount);
		if (!(maplogicp->LoadFromFile(filename))) {
			free(maplogicp);
			maplogicp = nullptr;
		}
		else {
			block_size = maplogicp->GetBlockSize();
			userp = new PlayerControl('p');
			enemyp = new PlayerControl('e');
			userp->FindPosition(maplogicp);
			enemyp->FindPosition(maplogicp);
			state = 1;
		}
	}
}

void PlayMode::Draw(void) {
	char filebuf[30];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	glRasterPos2d(100, 320);
	YsGlDrawFontBitmap16x24("Please select Map file:");

	glColor3ub(255, 0, 0);
	sprintf(filebuf, "filename: Z< aimap%d.txt >X", filecount);
	glRasterPos2d(100, 400);
	YsGlDrawFontBitmap16x24(filebuf);

	glColor3ub(0, 0, 0);
	glRasterPos2d(100, 450);
	YsGlDrawFontBitmap16x24("-Press ENTER to start-");

	FsSwapBuffers();
}

void PlayMode::GetKey2(void) {
	int key = FsInkey();
	if (FSKEY_ESC == key)
	{
		global_state = 1; //go back to menu;
	}
	userp->MoveKey(key, maplogicp);
}

void PlayMode::Draw2(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	maplogicp->Draw();

	glColor3ub(0, 0, 0);

	glRasterPos2d(610, 25);
	YsGlDrawFontBitmap8x12("Instructions:");
	glRasterPos2d(610, 50);
	YsGlDrawFontBitmap8x12("Direction-Move");
	glRasterPos2d(610, 70);
	YsGlDrawFontBitmap8x12("ESC-Exit");
	glRasterPos2d(610, 90);
	YsGlDrawFontBitmap8x12("SPACE-Pause");
	glRasterPos2d(610, 110);
	YsGlDrawFontBitmap8x12("Q-Show Player Path");
	glRasterPos2d(610, 130);
	YsGlDrawFontBitmap8x12("W-Invisible Enemy");
	glRasterPos2d(610, 150);
	YsGlDrawFontBitmap8x12("A-Show Enemy Path");
	glRasterPos2d(610, 170);
	YsGlDrawFontBitmap8x12("S-Reset Game");

	glRasterPos2d(610, 525);
	YsGlDrawFontBitmap8x12("State Log:");

	glBegin(GL_LINES);
	glVertex2i(600, 0);
	glVertex2i(600, 800);

	glVertex2i(600, 200);
	glVertex2i(800, 200);

	glVertex2i(600, 500);
	glVertex2i(800, 500);

	glEnd();

	FsSwapBuffers();
}