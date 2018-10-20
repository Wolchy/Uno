#include "Mouse.h"

Mouse::Mouse() {}

void Mouse::moved(int xx, int yy) {
	x = xx;
	y = yy;
}

void Mouse::buttonDown(Uint8) {}
void Mouse::buttonUp(Uint8) {}