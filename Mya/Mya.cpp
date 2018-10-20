#include "Mya.h"

Screen* Mya::screen = NULL;
Screen* Mya::debugScreen = NULL;

Mouse* Mya::mouse = NULL;
Keyboard* Mya::keyboard = NULL;

bool Mya::run = NULL;
bool Mya::fullscreen = NULL;

Mya::Mya() {}

bool Mya::init(std::string title) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		std::cout << "Error IN Mya::init, with SDL_Init: " << SDL_GetError() << std::endl;
		run = false;
	} else if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error IN Mya::init, with IMG_Init: " << IMG_GetError() << std::endl;
		run = false;
	} else if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize!SDL_ttf Error : %s\n", TTF_GetError());
		run = false;
	}
	else if (SDLNet_Init() == -1) {
		printf("SDLNet could not initialize!SDLNet Error : %s\n", SDLNet_GetError());
		run = false;
	} else {
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			std::cout << "Error IN Mya::init, with SDL_CreateWindow: " << SDL_GetError() << std::endl;
			run = false;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer) {
				std::cout << "Error IN Mya::init, with SDL_CreateRenderer: " << SDL_GetError() << std::endl;
				run = false;
			} else {
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					run = false;
				} else {
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);//I like white.
					SDL_UpdateWindowSurface(window);
					SDL_StartTextInput();
					std::cout << "Sucessfully started " << VERSION << "!" << std::endl;
					run = true;
				}
			}
		}
	}
	return run;
}

void Mya::update() {
	deltaTimer.start();
	SDL_Event e;

	if (screen != NULL)
		screen->update(*this);
	if (debugScreen != NULL)
		debugScreen->update(*this);

	fps.update();

	while (SDL_PollEvent(&e) != 0){
		if (screen != NULL)
			screen->event(*this,e);
		if (debugScreen != NULL)
			debugScreen->event(*this, e);
		if (e.type == SDL_QUIT)
			exit();
		if (e.type == SDL_KEYDOWN) {
			if (screen != NULL)
				screen->keyDown(*this, e.key.keysym.sym);
			if (debugScreen != NULL)
				debugScreen->keyDown(*this, e.key.keysym.sym);
			if (keyboard != NULL)
				keyboard->keyDown(e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP) {
			if (screen != NULL)
				screen->keyUp(*this, e.key.keysym.sym);
			if (debugScreen != NULL)
				debugScreen->keyUp(*this, e.key.keysym.sym);
			if (keyboard != NULL)
				keyboard->keyUp(e.key.keysym.sym);
		}
		if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
				if (screen != NULL)
					screen->resize(*this);
				if (debugScreen != NULL)
					debugScreen->resize(*this);
			}
		if (e.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (screen != NULL)
				screen->mouseMoved(x, y);
			if (debugScreen != NULL)
				debugScreen->mouseMoved(x, y);
			if (mouse != NULL)
				mouse->moved(x, y);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (screen != NULL)
				screen->mouseKeyDown(*this, e.button);
			if (debugScreen != NULL)
				debugScreen->mouseKeyDown(*this, e.button);
			if (mouse != NULL)
				mouse->buttonDown(e.button.button);
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			if (screen != NULL)
				screen->mouseKeyUp(*this, e.button);
			if (debugScreen != NULL)
				debugScreen->mouseKeyUp(*this,e.button);
			if (mouse != NULL)
				mouse->buttonUp(e.button.button);
		}
		if (e.type == SDL_MOUSEWHEEL) {
			if (screen != NULL)
				screen->mouseScroll(*this, e.wheel);
			if (debugScreen != NULL)
				debugScreen->mouseScroll(*this, e.wheel);
		}
	}
}

void Mya::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
	fps.frames++;
	SDL_RenderClear(renderer);
	

	if (screen != NULL)
		screen->render(*this);
	if (debugScreen != NULL)
		debugScreen->render(*this);

	SDL_RenderPresent(renderer);
}

void Mya::exit() {
	run = false;
}

bool Mya::isRunning() {
	return run;
}

void Mya::close() { 
	std::cout << "close" << std::endl;
	SDL_StopTextInput();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	Mix_Quit();
	IMG_Quit();
	SDLNet_Quit();
	SDL_Quit();
}

void Mya::setScreen(Screen* scr) {
	screen = scr;
}

Screen* Mya::getScreen() {
	return screen;
}

void Mya::setDebugScreen(Screen* scr) {
	debugScreen = scr;
}

Screen* Mya::getDebugScreen() {
	return debugScreen;
}

void Mya::setMouse(Mouse* _mouse) {
	mouse = _mouse;
}

Mouse* Mya::getMouse() {
	return mouse;
}

void Mya::setKeyboard(Keyboard* _keyboard) {
	keyboard = _keyboard;
}

Keyboard* Mya::getKeyboard() {
	return keyboard;
}

void Mya::setFullscreen(bool b) {
	if (b)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FOREIGN);
	fullscreen = b;
}

bool Mya::getFullscreen() {
	return fullscreen;
}

SDL_Window* Mya::getWindow() {
	return window;
}

SDL_Renderer* Mya::getRenderer() {
	return renderer;
}