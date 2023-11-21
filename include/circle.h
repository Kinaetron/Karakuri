#ifndef CIRCLE_H
#define CIRCLE_H

#include "api.h"
#include "vector2.h"
#include <memory>

class KARAKURI_API Circle
{
public:
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