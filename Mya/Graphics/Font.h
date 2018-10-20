#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class Font {
public:
	TTF_Font* font;

	Font(std::string);
	Font();
private:
};
