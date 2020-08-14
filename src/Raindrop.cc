#include <chrono>
#include <cstdlib>

#include "globals.cc"
#include "Raindrop.hh"

#include <iostream>

const float start_speed = 100.0F;
const float max_speed = 500.0F;
const float grav_acc = 981.0F;
const int grav_offset = 300;

Raindrop::Raindrop() {
	pos = Point(rand() % screen_w);
	speed = start_speed;
	acc = grav_acc + (rand() % grav_offset) - (grav_offset / 2);
}

void Raindrop::step(float delta) {
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
