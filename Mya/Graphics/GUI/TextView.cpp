#include "TextView.h"

TextView::TextView(Font _font, std::string _string, int _x, int _y, SDL_Renderer* _renderer) {
	color = { 0, 0, 169 };
	font = _font;
	text = _string;
	x = _x;
	y = _y;
	update(_renderer);
}

void TextView::update(SDL_Renderer* r) {
	if(tex.a)
		tex.destroy();
	tex = Texture(TTF_RenderText_Solid(font.font, text.c_str(), color), r);
}

void TextView::render(SDL_Renderer* _renderer) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = tex.w;
	stretchRect.h = tex.h;

	if(text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
	if (renderBounds) {
		SDL_SetRenderDrawColor(_renderer, 0, 69, 0, 0);
		SDL_RenderDrawRect(_renderer, &stretchRect);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 69, 0);
	}
}

void TextView::render(SDL_Renderer* _renderer, int w, int h) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = w;
	stretchRect.h = h;

	if (text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
	if (renderBounds) {
		SDL_SetRenderDrawColor(_renderer, 0, 69, 0, 0);
		SDL_RenderFillRect(_renderer, &stretchRect);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 69, 0);
	}
}

void TextView::setXY(int xx, int yy)
{
	x = xx;
	y = yy;
}

void TextView::setColor(SDL_Color c) {
	color = c;
}

SDL_Color TextView::getColor()
{
	return color;
}

void TextView::setText(std::string s, SDL_Renderer* r) {
	if (s != text) {
		text = s;
		update(r);
	}
}

std::string TextView::getText() {
	return text;
}
