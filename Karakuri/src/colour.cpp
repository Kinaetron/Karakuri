#include "../include/colour.h"

Colour::Colour():
	red(0),
	green(0),
	blue(0)
{
}

Colour::Colour(Vector3<unsigned short> colours)
	:red(colours.X),
	 green(colours.Y),
	 blue(colours.Z)
{
}

Colour::Colour(unsigned short red, unsigned short green, unsigned blue):
	red(red),
	green(green),
	blue(blue)
{
}

const Vector3<float> Colour::ToVector3() const {
	return Vector3<float>(red / 255.0f, green / 255.0f, blue / 255.0f);
}