#include "Sprite.h"

Sprite::Sprite(Texture* texture) {
	if (texture != NULL)
		canRRender = true;
	else
		canRRender = false;
	tex = texture;
}

void Sprite::destroy() {
	tex->destroy();
}

void Sprite::update() {}

void Sprite::render(SDL_Renderer* renderer) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = tex->w;
	a.h = tex->h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderDrawRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::render(SDL_Renderer* renderer, int w, int h) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderDrawRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::render(SDL_Renderer* renderer, int w, int h, bool f) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		if (f)
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, 0.0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::renderWithBounds(SDL_Renderer* renderer) {
	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &bounds);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::setBounds(SDL_Rect b) {
	bounds = b;
}

SDL_Rect Sprite::getBounds() {
	return bounds;
}

void Sprite::setAutoBounds(bool b) {
	autoSetBounds = b;
}