/* header of main function */
#ifndef MAIN_H_IS_INCLUDED
#define MAIN_H_IS_INCLUDED

/* include required libraries */
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "createmap.h"
#include "playmode.h"

/* define global variables */
/* global_state is an integer that indicate the
 * program state.
 * 0 - quit the game
 * 1 - menu mode
 * 2 - create map mode
 * 3 - play game mode (collect data)
 * 4 - robot mode (demonstration)
 */
int global_state = 0; // initialize by 0

#endif