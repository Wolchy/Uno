#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "../Font.h"
#include "../Texture.h"
#include "../../Mya.h"

class TextView {
public:
	int x, y;
	TextView(Font, std::string, int, int, SDL_Renderer*);

	void render(SDL_Renderer*);
	void render(SDL_Renderer*, int, int);
	void setXY(int,int);
	void setColor(SDL_Color);
	SDL_Color getColor();
	void setText(std::string, SDL_Renderer*);
	std::string getText();

	Texture tex;
	std::string text;
	Font font;
	SDL_Color color;
	bool renderBounds = false;

	void update(SDL_Renderer*);
};