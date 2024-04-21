#include "frame_data.h"

FrameData::FrameData(Rectangle& collisionBox,
	const std::vector<Rectangle>& hitBoxes,
	const std::vector<Rectangle>& hurtBoxes):
	collisionBox(collisionBox),
	hitBoxes(hitBoxes),
	hurtBoxes(hurtBoxes)
{
}

Rectangle FrameData::CollisionBox(const Vector2<float> position) const
{
	return Rectangle(collisionBox.Width(),
					 collisionBox.Height(),
				     Vector2<float>(collisionBox.Position().X + position.X, 
									collisionBox.Position().Y + position.Y));
}
