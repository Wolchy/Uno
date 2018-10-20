#pragma once

#include <SDL.h>

class Keyboard {
public:
	Keyboard();

	virtual void keyDown(Uint8);
	virtual void keyUp(Uint8);

private:
};