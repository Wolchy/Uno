#include "Font.h"

Font::Font(std::string fontPath) {
	font = TTF_OpenFont(fontPath.c_str(), 28);
	if (font == NULL)
		std::cout << "Failed to load font: " << fontPath << "! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
	else
		std::cout << "Loaded font: " << fontPath << "!" << std::endl;
}

Font::Font() {
	font = NULL;
}