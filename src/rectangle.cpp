#include <cmath>
#include "collision.h"
#include <circle.h>
#include <rectangle.h>
#include <iostream>

Rectangle::Rectangle(float width, float height, Vector2<float> position) :
	width(width),
	height(height),
	position(position)
{
}