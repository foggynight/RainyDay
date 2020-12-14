// Copyright (C) 2020 Robert Coffey
// Licensed under the GNU GPLv2

#include <chrono>
#include <cstdlib>

#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Raindrop.h"

Raindrop::Raindrop()
{
	pos = olc::vi2d(rand() % screen_w, 0);
	speed = start_speed;
}

void Raindrop::step(float acc, float delta)
{
	pos.y += speed * delta;

	float offset = rand()%acceleration_offset;
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
