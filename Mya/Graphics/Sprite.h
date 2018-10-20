#pragma once

#include <SDL.h>
#include "Texture.h"

class Sprite {
public:
	int x = 0, y = 0;
	SDL_Rect bounds;
	Texture* tex;
	bool canRRender = false;
	bool renderBounds = false;

	Sprite(Texture*);

	void destroy();

	virtual void update();
	virtual void render(SDL_Renderer*);
	virtual void render(SDL_Renderer*, int, int);
	virtual void render(SDL_Renderer*, int, int, bool);
	virtual void renderWithBounds(SDL_Renderer*);
	void setBounds(SDL_Rect);
	SDL_Rect getBounds();
	void setAutoBounds(bool);

private:
	bool autoSetBounds;
};