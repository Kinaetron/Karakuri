#include "animation_player.h"
#include <spdlog/spdlog.h>

AnimationPlayer::AnimationPlayer(SpriteRenderer& renderer):
	currentFrame(0),
	currentFrameTime(0.0f),
	animationData(nullptr),
	renderer(renderer),
	logger(nullptr),
	animationFinished(false)
{
}

void AnimationPlayer::Update(float millisecondsPerUpdate)
{
	if (animationData == nullptr) {
		return;
	}

	if (currentFrameTime > 0.01) {
		currentFrameTime -= millisecondsPerUpdate;
	}
	else
	{
		animationFinished = false;

		if (currentFrame >= animationData->FrameCount() - 1 && animationData->IsLooping()) {
			currentFrame = 0;
		}
		else if (currentFrame >= animationData->FrameCount() - 1) 
		{
			animationFinished = true;
			currentFrame = animationData->FrameCount() - 1;
		}
		else 
		{
			currentFrame++;
			currentFrameTime = static_cast<float>(animationData->Cell(currentFrame).Duration());
		}
	}
}

FrameData* AnimationPlayer::GetFrameData()
{
	if (animationData == nullptr) {
		return nullptr;
	}

	return &animationData->Frame(currentFrame);
}

void AnimationPlayer::Play(AnimationData* data)
{
	if (data == animationData) {
		return;
	}

	currentFrame = 0;
	currentFrameTime = 0.0f;

	animationData = data;
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour, SpriteMirror mirror)
{
	if (animationData == nullptr) {
		return;
	}

	renderer.Draw(animationData->Cell(currentFrame).CellTexture(), position, colour, mirror);
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, float scale)
{
	if (animationData == nullptr) {
		return;
	}

	Rectangle sourceRectangle = Rectangle(
		static_cast<float>(animationData->Cell(currentFrame).CellTexture().Width()),
		static_cast<float>(animationData->Cell(currentFrame).CellTexture().Height()),
		Vector2<float>::Zero());

	renderer.Draw(animationData->Cell(currentFrame).CellTexture(), position, sourceRectangle,  colour, mirror, rotation, origin, scale);
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, Vector2<float> scale)
{
	if (animationData == nullptr) {
		return;
	}

	Rectangle sourceRectangle = Rectangle(
		static_cast<float>(animationData->Cell(currentFrame).CellTexture().Width()),
		static_cast<float>(animationData->Cell(currentFrame).CellTexture().Height()),
		Vector2<float>::Zero());

	renderer.Draw(animationData->Cell(currentFrame).CellTexture(), position, sourceRectangle, colour, mirror, rotation, origin, scale);
}

void AnimationPlayer::Reset()
{
	currentFrame = 0;
	currentFrameTime = 0;
	animationFinished = false;
	animationData = nullptr;
}

void AnimationPlayer::Destroy()
{
	logger.reset();
}