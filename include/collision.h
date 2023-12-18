#ifndef COLLISION_H
#define COLLISION_H

#include <circle.h>
#include <vector2.h>
#include <rectangle.h>

class Collision
{
public:
	/*
	* Collision between objects is checked.
	*/
	Collision() = default;
	Collision(const Collision& that) = default;
	Collision(Collision&& that) = default;
	Collision& operator=(const Collision& rhs) = default;
	/*
	* Checks to see if circle and a circle intersects.
	* \param circle1 is the first circle to check against.
	* \param circle2 is the second circle to check against.
	* 
	* \return a float vector2 with the depth of the intersection.
	*/
	Vector2<float> CirlcleIntersectsCircle(const Circle& circle1, const Circle& circle2);
	/*
	* Checks to see if rectangle and a rectangle intersects.
	* \param rectangle1 is the first rectangle to check against.
	* \param rectangle2 is the second rectangle to check against.
	*
	* \return a float vector2 with the depth of the intersection.
	*/
	Vector2<float> RectangleIntersectRectangle(const Rectangle& rectangle1, const Rectangle& rectangle2);
	/*
	* Checks to see if circle and a rectangle intersects.
	* \param circle is the circle to check against.
	* \param rectangle is the rectangle to check against.
	*
	* \return a float vector2 with the depth of the intersection.
	*/
	Vector2<float> RectangleIntersectsCircle(const Circle& ciricle, const Rectangle& rectangle);
};
#endif
