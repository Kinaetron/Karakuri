#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include <vector>
#include <rectangle.h>

class FrameData
{
public:
	FrameData(const FrameData& that) = default;
	FrameData(FrameData&& that) = default;
	FrameData& operator=(const FrameData& rhs) = default;
	FrameData& operator=(FrameData&& rhs) = default;
	FrameData(Rectangle& collisionBox,
		const std::vector<Rectangle>& hitBoxes,
		const std::vector<Rectangle>& hurtBoxes);
	Rectangle CollisionBox(const Vector2<float> position) const;

private:
	Rectangle collisionBox;
	const std::vector<Rectangle>& hitBoxes;
	const std::vector<Rectangle>& hurtBoxes;
};

#endif