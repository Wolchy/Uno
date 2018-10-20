#pragma once

#include <iostream>
#include <SDL.h>
#undef main 
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>

#include "Graphics\GUI\Screen.h"
#include "Input\Mouse.h"
#include "Input\Keyboard.h"
#include "Utils\FPS.h"
#include "Utils\Timer.h"

class Mya {
public:
	const char* VERSION = "Mya 1.0.0";
	
	Timer deltaTimer;
	FPS fps;
	int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
	bool isServer = false;
	Mya();

	bool init(std::string);
	void update();
	void render();
	void exit();
	bool isRunning();
	void close();
	void setScreen(Screen*);
	Screen* getScreen();
	void setDebugScreen(Screen*);
	Screen* getDebugScreen();
	void setMouse(Mouse*);
	Mouse* getMouse();
	void setKeyboard(Keyboard*);
	Keyboard* getKeyboard();
	void setFullscreen(bool);
	bool getFullscreen();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

private:
	static Screen* screen;
	static Screen* debugScreen;

	static Mouse* mouse;
	static Keyboard* keyboard;

	SDL_Window* window;
	SDL_Renderer* renderer;

	static bool run;
	static bool fullscreen;
};