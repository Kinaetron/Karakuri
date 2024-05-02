#include "frame_data.h"

FrameData::FrameData(Rectangle collisionBox,
	const std::vector<Rectangle> hitBoxes,
	const std::vector<Rectangle> hurtBoxes):
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

std::vector<Rectangle> FrameData::Hitboxes(const Vector2<float> position, SpriteMirror mirror) const
{
	if (hitBoxes.empty()) {
		return std::vector<Rectangle>();
	}

	std::vector<Rectangle> modifiedHitboxes;

	for (int i = 0; i < hitBoxes.size(); i++)
	{
		if (mirror == SpriteMirror::None)
		{
			Rectangle modifiedHitbox = Rectangle(
				hitBoxes[i].Width(),
				hitBoxes[i].Height(),
				Vector2<float>(
				hitBoxes[i].Position().X + position.X,
				hitBoxes[i].Position().Y + position.Y));

			modifiedHitboxes.push_back(modifiedHitbox);
		}
		else if (mirror == SpriteMirror::Horizontally)
		{
			Rectangle modifiedHitbox = Rectangle(
				hitBoxes[i].Width(),
				hitBoxes[i].Height(),
				Vector2<float>(
				position.X - (hitBoxes[i].Position().X + hitBoxes[i].Width()),
				hitBoxes[i].Position().Y + position.Y));

			modifiedHitboxes.push_back(modifiedHitbox);
		}
	}

	return modifiedHitboxes;
}

std::vector<Rectangle> FrameData::Hurtboxes(const Vector2<float> position, SpriteMirror mirror) const
{
	if (hurtBoxes.empty()) {
		return std::vector<Rectangle>();
	}

	std::vector<Rectangle> modifiedHurtboxes;

	for (int i = 0; i < hurtBoxes.size(); i++)
	{
		if (mirror == SpriteMirror::None)
		{
			Rectangle modifiedHurtbox = Rectangle(
				hurtBoxes[i].Width(),
				hurtBoxes[i].Height(),
				Vector2<float>(
				hurtBoxes[i].Position().X + position.X,
				hurtBoxes[i].Position().Y + position.Y));

			modifiedHurtboxes.push_back(modifiedHurtbox);
		}
		else if (mirror == SpriteMirror::Horizontally)
		{
			Rectangle modifiedHurtbox = Rectangle(
				hurtBoxes[i].Width(),
				hurtBoxes[i].Height(),
				Vector2<float>(
				position.X - (hurtBoxes[i].Width() + hurtBoxes[i].Position().X),
				hurtBoxes[i].Position().Y + position.Y));

			modifiedHurtboxes.push_back(modifiedHurtbox);
		}
	}

	return modifiedHurtboxes;
}
