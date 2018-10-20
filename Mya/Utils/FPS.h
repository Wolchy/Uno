#pragma once

#include <iostream>
#include <time.h>

#include <SDL.h>

class FPS {
public:

	time_t start;
	int frames = 0;
	int fps = 0;

	FPS();

	void update();
};