#pragma once

#include <iostream>

#include "../GUI/TextView.h"
#include "../Sprite.h"

class Button : public Sprite {
public:
	TextView* tv;
	std::string data = "";

	Button();
	Button(Texture*, SDL_Rect);
	Button(SDL_Rect);
	Button(Texture*);
	Button(std::string, Font, SDL_Renderer*, int x, int y);
	Button(std::string, Font, SDL_Renderer*, Texture*, int x, int y);


	void renderButton(SDL_Renderer*);
	bool wasPressed(int, int);
	void setTexture(Texture*);

private:
	bool canRender = false;
};