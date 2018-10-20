#include "EditText.h"

EditText::EditText(std::string s, Font f, SDL_Renderer * r, int x, int y)
{
	butt = new Button(s, f, r, x, y);
}

void EditText::wasPressed(int x, int y)
{
	if (butt->wasPressed(x, y))
		selected = true;
	else
		selected = false;
}

void EditText::handleKey(Uint8 k, SDL_Renderer* r)
{
	if (selected) {
		if (k == SDLK_BACKSPACE) {
			if (butt->tv->getText().length() > 0) {
				butt->tv->text.pop_back();
				butt->tv->update(r);
				if (butt->tv->getText().length() == 0) {
					butt->tv->tex.w = 50;
					butt->tv->tex.h = 28;
				}
			}
		}
		else if (k != SDL_SCANCODE_KP_AMPERSAND) {
			int temp = SDL_GetModState();
			temp = temp & KMOD_CAPS;
			std::locale loc;
			if (temp == KMOD_CAPS)
				butt->tv->setText(butt->tv->getText() + SDL_GetKeyName(k), r);
			else
				butt->tv->setText(butt->tv->getText() + SDL_GetKeyName(k), r);
		}
	}
}
