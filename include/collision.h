#ifndef COLLISION_H
#define COLLISION_H

#include <circle.h>
#include <vector2.h>
#include <rectangle.h>

class Collision
{
public:
	/*
	* Collision between objects is checked.
	*/
	Collision() = default;
	Collision(const Collision& that) = default;
	Collision(Collision&& that) = default;
	Collision& operator=(const Collision& rhs) = default;

	bool RectangleCollidesRectangle(Rectangle& rectangle1, Rectangle& rectangle2);
};
#endif
