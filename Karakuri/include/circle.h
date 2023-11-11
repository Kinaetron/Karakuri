#ifndef CIRCLE_H
#define CIRCLE_H

#include "api.h"
#include "glm/glm.hpp"

class Rectangle;

class KARAKURI_API Circle
{
public:
	Circle(float radius, glm::vec2 position);
	void SetPosition(glm::vec2 position) { this->position = position; }
	const float Radius() const { return radius; }
	const glm::vec2 Centre() const { return glm::vec2(position.x - radius, position.y - radius); }
	const glm::vec2 Position() const { return position; }
	const glm::vec2 IntersectsCircle(Circle& circle);
	const glm::vec2 IntersectRectangle(Rectangle& rectangle);

private:
	float radius;
	glm::vec2 position;
	class Collision* collision;
};

#endif