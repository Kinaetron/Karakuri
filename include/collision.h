#ifndef COLLISION_H
#define COLLISION_H

#include <circle.h>
#include <circle.h>
#include <vector2.h>
#include <rectangle.h>

class Collision
{
public:
	Collision() = default;
	Collision(const Collision& that) = default;
	Collision(Collision&& that) = default;
	Collision& operator=(const Collision& rhs) = default;
	Vector2<float> CirlcleIntersectsCircle(const Circle& circle1, const Circle& circle2);
	Vector2<float> RectangleIntersectRectangle(const Rectangle& rectangle1, const Rectangle& rectangle2);
	Vector2<float> RectangleIntersectsCircle(const Circle& ciricle, const Rectangle& rectangle);
};
#endif
