#include "collision.h"
#include "../include/circle.h"
#include "../include/glm/gtc/matrix_transform.hpp"

Circle::Circle(float radius, glm::vec2 position)
	:radius(radius),
	 position(position),
	collision(new Collision())
{
}

const glm::vec2 Circle::IntersectsCircle(Circle& circle)
{
	float radisSum = this->Radius() + circle.Radius();
	glm::vec2 distanceVector = this->Position() - circle.Position();

	 float distance = glm::length(distanceVector);

	 if (distance > radisSum) {
		 return glm::vec2(0, 0);
	 }

	 float depth = radisSum - distance;
	 glm::vec2 direction = glm::normalize((this->Position() - circle.Position()));

	 return direction * depth;
}

const glm::vec2 Circle::IntersectRectangle(Rectangle& rectangle) {
	return collision->RectangleIntersectsCircle(rectangle, *this);
}