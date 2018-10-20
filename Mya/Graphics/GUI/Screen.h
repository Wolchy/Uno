#pragma once

#include <iostream>
#include <SDL.h>

class Mya;

class Screen {
public:
	int mouseX, mouseY;
	std::string id;
	Screen(std::string);

	virtual void update(Mya);
	virtual void render(Mya);

	virtual void resize(Mya);
	virtual void keyDown(Mya,Uint8);
	virtual void keyUp(Mya,Uint8);
	virtual void mouseKeyUp(Mya,SDL_MouseButtonEvent&);
	virtual void mouseKeyDown(Mya,SDL_MouseButtonEvent&);
	virtual void mouseScroll(Mya, SDL_MouseWheelEvent&);
	virtual void mouseMoved(int, int);
	virtual void event(Mya,SDL_Event);

private:
};