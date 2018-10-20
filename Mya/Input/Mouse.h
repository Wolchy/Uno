#pragma once

#include <SDL.h>

class Mouse {
public:
	Mouse();

	virtual void moved(int, int);
	virtual void buttonDown(Uint8);
	virtual void buttonUp(Uint8);

private:
	int x = 0, y = 0;
};