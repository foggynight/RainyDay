#pragma once

#include "Point.hh"

/**
 * Raindrop represented by a pixel.
 */
class Raindrop {
public:
	Point pos;
	int speed;
	int acc;

public:
	Raindrop(
		Point pos = Point(),
		int speed = 0,
		int acc = 0
	) : pos(pos), speed(speed), acc(acc) {}

	/** 
	 * Increase the y position by the speed value.
	 */
	void step();

	/**
	 * Reset the raindrop:
	 * - Set pos to a random position at the top of the screen
	 * - Set speed to zero
	 */
	void reset();
};
