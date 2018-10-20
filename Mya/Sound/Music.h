#pragma once

#include <iostream>
#include <SDL_mixer.h>

class Music {
public:
	Music(std::string);

	void destroy();

	void play();
	void pause();
	void resume();
	void stop();

private:
	Mix_Music* music = NULL;
};