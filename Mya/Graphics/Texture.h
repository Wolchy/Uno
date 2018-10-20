#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Texture {
public:
	SDL_Texture* texture;
	int w = 1, h = 1;
	std::string id = "null";
	bool a = false;

	Texture();
	Texture(std::string, SDL_Renderer*);
	Texture(SDL_Surface*, SDL_Renderer*);

	SDL_Texture* getTexture();
	void destroy();
};