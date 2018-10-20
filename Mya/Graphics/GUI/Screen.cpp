#include "Screen.h"

#include "../../Mya.h"

Screen::Screen(std::string i){
	id = i;
}

void Screen::update(Mya){}
void Screen::render(Mya){}

void Screen::resize(Mya) {}
void Screen::keyDown(Mya,Uint8 keycode){}
void Screen::keyUp(Mya,Uint8 keycode){}
void Screen::mouseKeyUp(Mya,SDL_MouseButtonEvent &event){}
void Screen::mouseKeyDown(Mya,SDL_MouseButtonEvent &event){}

void Screen::mouseScroll(Mya, SDL_MouseWheelEvent &){}

void Screen::mouseMoved(int x, int y){
	mouseX = x;
	mouseY = y;
}

void Screen::event(Mya,SDL_Event event){}
