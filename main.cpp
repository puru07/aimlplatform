/* 24783 machine learning project
 * Team B: Zewen, Ximing, Puru, Kan
 * This program is used to collect data and demonstrate
 * the artificial intelligent algorithms.
 */
#include "main.h"

int main(void) {
	/* declare variables */
	GameMenu gamemenu;
	CreateMap createmap;
	PlayMode playmode;
	int terminate_all = 0;

	/* open window begin main loop */
	global_state = 1; // initial state menu mode
	FsOpenWindow(0, 0, 800, 600, 1);

	while (!terminate_all) {
		switch (global_state) {
		case 0:
			terminate_all = 1;
			break;
		case 1:
			gamemenu.Launch();
			break;
		case 2:
			createmap.Launch();
			break;
		case 3:
			playmode.Launch();
			break;
		case 4:
			playmode.Launch();
			break;
		default:
			terminate_all = 1;
			break;
		}
	}

	/* close window and quit the program */
	FsCloseWindow();
	return 0;
}