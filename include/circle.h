#ifndef CIRCLE_H
#define CIRCLE_H

#include "vector2.h"

class Circle
{
public:
	Circle(const Circle& that) = default;
	Circle(Circle&& that) = default;
	Circle& operator=(const Circle& rhs) = default;
	/*
	* A 2D representation of a circle.
	* 
	* /param radius of the circle you want to create.
	* /param position of the circle you want to create.
	*/
	Circle(float radius, Vector2<float> position);

	/*
	* Set the position.
	*
	* /param position. Sets the position of the circle.
	*/
	void SetPosition(Vector2<float> position) { this->position = position; }
	/*
	* Gets the radius.
	*/
	const float Radius() const { return radius; }
	/*
	* Gets the centre position.
	*/
	const Vector2<float> Centre() const { return Vector2<float>(position.X - radius, position.Y - radius); }
	/*
	* Gets the position.
	*/
	const Vector2<float> Position() const { return position; }

private:
	float radius;
	Vector2<float> position;
};

#endif