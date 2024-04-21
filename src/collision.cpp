#include "collision.h"
#include <limits>

bool Collision::RectangleCollidesRectangle(Rectangle& rectangle1, Rectangle& rectangle2)
{
	return rectangle1.Left() < rectangle2.Right() &&
		   rectangle1.Right() > rectangle2.Left() &&
		   rectangle1.Top() < rectangle2.Bottom() &&
		   rectangle1.Bottom() > rectangle2.Top();
}