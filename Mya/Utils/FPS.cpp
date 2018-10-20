#include "FPS.h"

FPS::FPS() {
	start = time(0);
}

void FPS::update() {
	if (difftime(time(0), start) >= 1) {
		fps = frames;
		frames = 0;
		start = time(0);
	}
}