#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include <vector>
#include <rectangle.h>
#include <sprite_mirror.h>

class FrameData
{
public:
	FrameData(const FrameData& that) = default;
	FrameData(FrameData&& that) = default;
	FrameData& operator=(const FrameData& rhs) = default;
	FrameData& operator=(FrameData&& rhs) = default;
	FrameData(
		int frameWidth,
		int frameHeight,
		Rectangle collisionBox,
		const std::vector<Rectangle> hitBoxes,
		const std::vector<Rectangle> hurtBoxes);

	Rectangle CollisionBox(const Vector2<float> position) const;

	std::vector<Rectangle> Hitboxes(const Vector2<float> position, SpriteMirror mirror) const;
	std::vector<Rectangle> Hurtboxes(const Vector2<float> position, SpriteMirror mirror) const;

private:
	int frameWidth;
	int frameHeight;
	Rectangle collisionBox;
	const std::vector<Rectangle> hitBoxes;
	const std::vector<Rectangle> hurtBoxes;
};

#endif