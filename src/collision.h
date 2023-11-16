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
	Vector2<float> RectangleIntersectsCircle(Rectangle& rectangle, Circle& ciricle);
};
#endif
