#pragma once

/**
 * An x-y coordinate point.
 */
class Point {
public:
	float x;
	float y;

public:
	Point(float x = 0.0F, float y = 0.0F): x(x), y(y) {}
};
