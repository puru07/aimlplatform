/* This file contains gamemenu class */
#include "menu.h"

GameMenu::GameMenu(void) {
	pos = 400;
}

GameMenu::~GameMenu(void) {
	pos = 400;
}

void GameMenu::Launch(void) {
	pos = 400;
	while (global_state == 1) {
		/* begin logic part*/
		FsPollDevice();

		/* key detection */
		GetKey();

		/* begin drawing part */
		Draw();

		/* Sleep for a sum of time */
		FsSleep(25);
	}
}

void GameMenu::Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);

	glRasterPos2d(100, 320);
	YsGlDrawFontBitmap16x24("AI Machine Learning Platform:");
	glRasterPos2d(100, 400);
	YsGlDrawFontBitmap16x24("Create your map");
	glRasterPos2d(100, 450);
	YsGlDrawFontBitmap16x24("Player Mode");
	glRasterPos2d(100, 500);
	YsGlDrawFontBitmap16x24("Demonstrate Robot");

	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(90, pos - 30);
	glVertex2i(400, pos - 30);

	glVertex2i(400, pos - 30);
	glVertex2i(400, pos + 10);

	glVertex2i(400, pos + 10);
	glVertex2i(90, pos + 10);

	glVertex2i(90, pos + 10);
	glVertex2i(90, pos - 30);
	glEnd();

	FsSwapBuffers();
}

void GameMenu::GetKey(void) {
	int key = FsInkey();
	if (FSKEY_ESC == key)
	{
		global_state = 0;
	}
	if (FSKEY_RIGHT == key || FSKEY_DOWN == key)
	{
		if (pos < 500) {
			pos = pos + 50;
		}
	}
	if (FSKEY_LEFT == key || FSKEY_UP == key)
	{
		if (pos > 400) {
			pos = pos - 50;
		}
	}
	if (FSKEY_ENTER == key) {
		switch (pos) {
		case 400:
			global_state = 2;
			break;
		case 450:
			global_state = 3;
			break;
		case 500:
			global_state = 4;
			break;
		default:
			global_state = 0;
			break;
		}
	}
}