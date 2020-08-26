#pragma once

#include "Point.h"

/**
 * Raindrop represented by a pixel.
 */
class Raindrop {
public:
	Point pos; // Position on the raindrop.
	float speed; // Speed of the raindrop.
	float acc; // Acceleration of the raindrop.

public:
	Raindrop();

	/** 
	 * Increase the y position by the speed value, and 
	 * increase the speed by the acceleration value.
	 *
	 * @param delta Elapsed time since previous step.
	 * @param acc Acceleration of the raindrop.
	 */
	void step(float delta, float acc);

	/**
	 * Reset the raindrop:
	 * - Set pos to a random position at the top of the screen.
	 * - Set speed to starting speed constant.
	 */
	void reset();
};