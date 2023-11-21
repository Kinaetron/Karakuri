#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "api.h"
#include<vector2.h>

class KARAKURI_API Rectangle
{
public:
	Rectangle(float width, float height, Vector2<float> position);
	const float Width() const { return width; }
	const float Height() const { return height; }
	const Vector2<float> Position() const { return position; }
	const float Left() const { return position.X; }
	const float Right() const { return position.X + width; }
	const float Top() const { return position.Y; }
	const float Bottom() const { return position.Y + height; }
	const Vector2<float> Centre() const { return Vector2<float>(position.X + (width / 2.0), position.Y + (height / 2.0)); }
	void SetPostion(Vector2<float> position) { this->position = position; }

private:
	float width;
	float height;
	Vector2<float> position;
};
#endif