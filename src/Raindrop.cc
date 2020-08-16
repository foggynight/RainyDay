#include <chrono>
#include <cstdlib>

#include "globals.cc"
#include "Raindrop.hh"

Raindrop::Raindrop() {
	pos = Point(rand() % screen_w);
	speed = start_speed;
}

void Raindrop::step(float delta, float acc) {
	pos.y += speed * delta;

	if (speed < max_speed) {
		speed += acc * delta;
	}

	if (pos.y >= screen_h) {
		reset();
	}
}

void Raindrop::reset() {
	pos.x = rand() % screen_w;
	pos.y = 0.0F;
	speed = start_speed;
}
