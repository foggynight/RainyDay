#include <chrono>
#include <cstdlib>

#include "globals.h"
#include "Raindrop.h"

Raindrop::Raindrop()
{
	pos = Point(rand() % screen_w);
	speed = start_speed;
}

void Raindrop::step(float delta, float acc)
{
	pos.y += speed * delta;

	if (pos.y >= screen_h) {
		reset();
	}

	float offset = rand()%acceleration_offset - acceleration_offset/3;
	float new_speed = speed + (acc + offset) * delta;

	if (new_speed <= 0.0F) {
		new_speed = speed;
	}
	else if (new_speed > max_speed) {
		new_speed = max_speed;
	}

	speed = new_speed;
}

void Raindrop::reset()
{
	pos.x = rand() % screen_w;
	pos.y = 0.0F;
	speed = start_speed;
}
