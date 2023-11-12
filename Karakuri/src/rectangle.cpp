#include <cmath>
#include "collision.h"
#include "../include/circle.h"
#include "../include/rectangle.h"

Rectangle::Rectangle(float width, float height, Vector2<float> position) :
	width(width),
	height(height),
	position(position),
	collision(new Collision())
{
}

const Vector2<float> Rectangle::IntersectsRectangle(Rectangle& rectangle)
{
	float halfWidthA = this->Width() / 2.0f;
	float halfHeightA = this->Height() / 2.0f;

	float halfWidthB = rectangle.Width() / 2.0f;
	float halfHeightB = rectangle.Height() / 2.0f;

	Vector2<float> centreA = Vector2<float>(this->Left() + halfWidthA, this->Top() + halfHeightA);
	Vector2<float> centreB = Vector2<float>(rectangle.Left() + halfWidthB, rectangle.Top() + halfHeightB);

	float distanceX = centreA.X - centreB.X;
	float distanceY = centreA.Y - centreB.Y;

	float minDistanceX = halfWidthA + halfWidthB;
	float minDistanceY = halfHeightA + halfHeightB;

	if (std::abs(distanceX) >= minDistanceX || std::abs(distanceY) >= minDistanceY) {
		return Vector2<float>::Zero();
	}

	float depthX = distanceX > 0.0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
	float depthY = distanceY > 0.0 ? minDistanceY - distanceY : -minDistanceY - distanceY;

	return Vector2<float>(depthX, depthY);
}

const Vector2<float> Rectangle::IntersectsCircle(Circle& circle) {
	return collision->RectangleIntersectsCircle(*this, circle);
}