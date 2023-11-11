#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "api.h"
#include "glm/glm.hpp"

class KARAKURI_API Rectangle
{
public:
	Rectangle(float width, float height, glm::vec2 position);
	const float Width() const { return width; }
	const float Height() const { return height; }
	const glm::vec2 Position() const { return position; }
	const float Left() const { return position.x; }
	const float Right() const { return position.x + width; }
	const float Top() const { return position.y; }
	const float Bottom() const { return position.y + height; }
	const glm::vec2 Centre() const { return glm::vec2(position.x + (width / 2.0), position.y + (height / 2.0)); }
	void SetPostion(glm::vec2 position) { this->position = position; }
	glm::vec2 IntersectsRectangle(Rectangle& rectangle);
	//glm::vec2 IntersectsCircle(Circle& circle);

private:
	float width;
	float height;
	glm::vec2 position;
	class Collision* collision;
};
#endif