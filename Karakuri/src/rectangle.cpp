#include "collision.h"
#include "../include/circle.h"
#include "../include/rectangle.h"

Rectangle::Rectangle(float width, float height, glm::vec2 position) :
	width(width),
	height(height),
	position(position),
	collision(new Collision())
{
}

glm::vec2 Rectangle::IntersectsRectangle(Rectangle& rectangle)
{
	float halfWidthA = this->Width() / 2.0f;
	float halfHeightA = this->Height() / 2.0f;

	float halfWidthB = rectangle.Width() / 2.0f;
	float halfHeightB = rectangle.Height() / 2.0f;

	glm::vec2 centreA = glm::vec2(this->Left() + halfWidthA, this->Top() + halfHeightA);
	glm::vec2 centreB = glm::vec2(rectangle.Left() + halfWidthB, rectangle.Top() + halfHeightB);

	float distanceX = centreA.x - centreB.x;
	float distanceY = centreA.y - centreB.y;

	float minDistanceX = halfWidthA + halfWidthB;
	float minDistanceY = halfHeightA + halfHeightB;

	if (abs(distanceX) >= minDistanceX || abs(distanceY) >= minDistanceY) {
		return glm::vec2(0, 0);
	}

	float depthX = distanceX > 0.0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
	float depthY = distanceY > 0.0 ? minDistanceY - distanceY : -minDistanceY - distanceY;

	return glm::vec2(depthX, depthY);
}

glm::vec2 Rectangle::IntersectsCircle(Circle& circle) {
	return collision->RectangleIntersectsCircle(*this, circle);
}