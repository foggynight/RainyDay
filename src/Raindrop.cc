#include <chrono>
#include <cstdlib>

#include "Raindrop.hh"

const int grav_acc = 1;

void Raindrop::step() {
	pos.y += speed;
	speed += acc;

	/*
	if (pos.y >= screen_h) {
		reset();
	}
	*/
}

void Raindrop::reset() {
	pos.x = rand() /* % screen_w */;
	pos.y = 0;
	speed = 0;
}
