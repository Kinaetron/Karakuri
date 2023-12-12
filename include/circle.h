#ifndef CIRCLE_H
#define CIRCLE_H

#include "vector2.h"

class Circle
{
public:
	Circle(const Circle& that) = default;
	Circle(Circle&& that) = default;
	Circle& operator=(const Circle& rhs) = default;
	Circle(float radius, Vector2<float> position);
	void SetPosition(Vector2<float> position) { this->position = position; }
	const float Radius() const { return radius; }
	const Vector2<float> Centre() const { return Vector2<float>(position.X - radius, position.Y - radius); }
	const Vector2<float> Position() const { return position; }

private:
	float radius;
	Vector2<float> position;
};

#endif