#ifndef COLOUR_H
#define COLOUR_H

#include <vector3.h>

class Colour
{
public:
	Colour(const Colour& that) = default;
	Colour(Colour&& that) = default;
	Colour& operator=(const Colour& rhs) = default;
	Colour(Vector3<unsigned short> colours);
	Colour(unsigned short red, unsigned short green, unsigned blue);
	const Vector3<float> ToVector3() const;

	static const Colour White() { return Colour(255, 255, 255); }
	static const Colour Black() { return Colour(0, 0, 0); }
	static const Colour Red() { return Colour(255, 0, 0); }
	static const Colour Green() { return Colour(0, 255, 0); }
	static const Colour Blue() { return Colour(0, 0, 255); }
	static const Colour Yellow() { return Colour(255, 255, 0); }
	static const Colour Orange() { return Colour(255, 165, 0); }
	static const Colour Purple() { return Colour(255, 0, 255); };
	static const Colour Teal() { return Colour(0, 255, 255); }
	static const Colour CornflowerBlue() { return   Colour(100, 149, 237); }

private:
	unsigned short red;
	unsigned short green;
	unsigned short blue;
};

#endif