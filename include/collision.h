#ifndef COLLISION_H
#define COLLISION_H

#include <api.h>
#include <circle.h>
#include <circle.h>
#include <vector2.h>
#include <rectangle.h>

class KARAKURI_API Collision
{
public:
	Vector2<float> CirlcleIntersectsCircle(const Circle& circle1, const Circle& circle2);
	Vector2<float> RectangleIntersectRectangle(const Rectangle& rectangle1, const Rectangle& rectangle2);
	Vector2<float> RectangleIntersectsCircle(const Circle& ciricle, const Rectangle& rectangle);
};
#endif
