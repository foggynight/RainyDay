#pragma once

/**
 * An x-y coordinate point.
 */
class Point {
public:
	float x; // x coordinate of the point.
	float y; // y coordinate of the point.

public:
	Point(float x = 0.0F, float y = 0.0F): x(x), y(y) {}
};
