#ifndef COLLISION_H
#define COLLISION_H

#include "../include/api.h"
#include "../include/glm/glm.hpp"
#include "../include/circle.h"
#include "../include/rectangle.h"

class KARAKURI_API Collision
{
public:
	glm::vec2 RectangleIntersectsCircle(Rectangle& rectangle, Circle& ciricle);

private:
	glm::vec2 normal(glm::vec2 vector);
};
#endif
