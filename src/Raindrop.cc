#include <chrono>
#include <cstdlib>

#include "globals.cc"
#include "Raindrop.hh"

Raindrop::Raindrop() {
	pos = Point(rand() % screen_w);
	speed = 0.5F;
	acc = 981.0F;
}

void Raindrop::step(float delta) {
	pos.y += speed * delta;
	speed += acc * delta;

	if (pos.y >= screen_h) {
		reset();
	}
}

void Raindrop::reset() {
	pos.x = rand() % screen_w;
	pos.y = 0.0F;
	speed = 0.0F;
}
