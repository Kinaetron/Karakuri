#ifndef RECTANGLE_H
#define RECTANGLE_H

#include<vector2.h>

class Rectangle
{
public:
	Rectangle(const Rectangle& that) = default;
	Rectangle(Rectangle&& that) = default;
	Rectangle& operator=(const Rectangle& rhs) = default;
	Rectangle& operator=(Rectangle&& rhs) = default;
	Rectangle() = default;
	Rectangle(float width, float height, Vector2<float> position);
	const float Width() const { return width; }
	const float Height() const { return height; }
	const Vector2<float> Position() const { return position; }
	const float Left() const { return position.X; }
	const float Right() const { return position.X + width; }
	const float Top() const { return position.Y; }
	const float Bottom() const { return position.Y + height; }
	const Vector2<float> Centre() const { return Vector2<float>(position.X + (width / 2.0f), position.Y + (height / 2.0f)); }
	void SetPostion(float x, float y) { this->position = Vector2<float>(x, y); }
	void SetPostion(Vector2<float> position) { this->position = position; }

private:
	float width = 0;
	float height = 0;
	Vector2<float> position = Vector2<float>().Zero();
};
#endif