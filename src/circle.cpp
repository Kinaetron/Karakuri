#include "collision.h"

#include <circle.h>
#include <rectangle.h>

Circle::Circle(float radius, Vector2<float> position)
	:radius(radius),
	 position(position),
	collision(new Collision())
{
}

const Vector2<float> Circle::IntersectsCircle(Circle& circle)
{
	float radisSum = this->Radius() + circle.Radius();
	Vector2<float> distanceVector = this->Position() - circle.Position();

	 float distance = distanceVector.Length();

	 if (distance > radisSum) {
		 return Vector2<float>::Zero();
	 }

	 float depth = radisSum - distance;
	 Vector2<float> direction = (this->Position() - circle.Position()).Normalize();

	 return direction * depth;
}

const Vector2<float> Circle::IntersectRectangle(Rectangle& rectangle) {
	return collision->RectangleIntersectsCircle(rectangle, *this);
}