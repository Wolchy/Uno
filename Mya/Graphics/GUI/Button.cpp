#include "Button.h"

Button::Button() : Sprite::Sprite(NULL) {
	canRRender = false;
}

Button::Button(Texture* texture, SDL_Rect bounds) : Sprite::Sprite(texture) {
	if (texture != NULL)
		canRRender = true;
	setBounds(bounds);
}

Button::Button(SDL_Rect bounds) : Sprite::Sprite(NULL) {
	canRRender = false;
	setBounds(bounds);
}

Button::Button(Texture* texture) : Sprite::Sprite(texture) {
	if (texture != NULL)
		canRRender = true;
	SDL_Rect bounds;
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = 1;
	bounds.h = 1;
	setBounds(bounds);
}

Button::Button(std::string s, Font f, SDL_Renderer * r, int x, int y) : Sprite::Sprite(NULL)
{
	canRRender = false;
	tv = new TextView(f, s, x, y, r);
	tv->update(r);
	SDL_Rect rec;
	rec.x = x;
	rec.y = y;
	rec.w = tv->tex.w;
	rec.h = tv->tex.h;
	setBounds(rec);
	tv->renderBounds = true;
}

Button::Button(std::string s, Font f, SDL_Renderer * r, Texture * t, int x, int y) : Sprite::Sprite(t)
{
	if (t != NULL)
		canRRender = true;
	tv = new TextView(f, s, x, y, r);
	tv->update(r);
	SDL_Rect rec;
	rec.x = x;
	rec.y = y;
	rec.w = tv->tex.w;
	rec.h = tv->tex.h;
	setBounds(rec);
}


void Button::renderButton(SDL_Renderer* renderer){
	if (canRRender);
		renderWithBounds(renderer);
	if(tv != NULL)
		tv->render(renderer);
}

bool Button::wasPressed(int x, int y) {
	if (bounds.x < x)
		if (bounds.x + bounds.w > x)
			if (bounds.y < y)
				if (bounds.y + bounds.h > y)
					return true;
	return false;
}

void Button::setTexture(Texture* texture) {
	if (texture != NULL)
		canRRender = true;
	else
		canRRender = false;
	tex = texture;
}
