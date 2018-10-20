#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string path, SDL_Renderer* renderer) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		w = loadedSurface->w;
		h = loadedSurface->h;
		std::cout << "Loaded texture: " << path.c_str() << "!" << std::endl;
		SDL_FreeSurface(loadedSurface);
	}
}

Texture::Texture(SDL_Surface* loadedSurface, SDL_Renderer* renderer) {
	if (loadedSurface == NULL) {
		std::cout << "Cannot convert a NULL SDL_Surface into SDL_Texture... Why would you even try?" << std::endl;
	}
	else {
		if (a == true) {
			SDL_DestroyTexture(texture);
			std::cout << "a";
		}

		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL) {
			std::cout << "Texture::Texture(SDL_Surface*, SDL_Renderer*) texture = NULL. It errored!" << std::endl;
		}
		w = loadedSurface->w;
		h = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		a = true;
	}
}

SDL_Texture* Texture::getTexture() {
	return texture;
}

void Texture::destroy() {
	SDL_DestroyTexture(texture);
}