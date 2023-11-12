#ifndef COLLISION_H
#define COLLISION_H

#include "../include/api.h"
#include "../include/circle.h"
#include "../include/vector2.h"
#include "../include/rectangle.h"

class KARAKURI_API Collision
{
public:
	Vector2<float> RectangleIntersectsCircle(Rectangle& rectangle, Circle& ciricle);
};
#endif
