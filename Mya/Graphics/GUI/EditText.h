#pragma once

#include "Button.h"

class EditText {
public:
	Button * butt;
	bool selected = false;

	EditText(std::string, Font, SDL_Renderer*, int x, int y);

	void wasPressed(int, int);
	void handleKey(Uint8, SDL_Renderer*);
};