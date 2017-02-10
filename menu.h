/* menu part header */
#ifndef MENU_H_IS_INCLUDED
#define MENU_H_IS_INCLUDED

#include "fssimplewindow.h"
#include "ysglfontdata.h"

extern int global_state;

class GameMenu{
private:
	int pos;
	void Draw(void);
	void GetKey(void);
public:
	GameMenu(void);
	~GameMenu(void);
	void Launch(void);
};

#endif