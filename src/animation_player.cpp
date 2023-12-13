#include "animation_player.h"
#include "aseprite.h"
#include <iostream>

AnimationPlayer::AnimationPlayer(const std::string& filepath, SpriteRenderer& renderer):
	renderer(renderer),
	frameCount(0),
	frameWidth(0),
	frameHeight(0),
	currentFrame(0),
	currentFrameTime(0.0f)
{
	ase_t* animation = cute_aseprite_load_from_file(filepath.c_str(), NULL);

	if (animation == nullptr)
	{
		std::cerr << "Animation data didn't load " << filepath << std::endl;
		return;
	}

	frameCount = animation->frame_count;
	frameWidth = animation->w;
	frameHeight = animation->h;

	for (int i = 0; i < animation->frame_count; ++i)
	{
		ase_frame_t* frame = animation->frames + i;

		unsigned char* pixels = reinterpret_cast<unsigned char*>(frame->pixels);
		Texture cellTexture = Texture(frameWidth, frameHeight, 4, pixels);

		cells.push_back(CellData(std::move(cellTexture),
			frame->duration_milliseconds));

		if (i == 0) {
			currentFrameTime =  static_cast<float>(frame->duration_milliseconds);
		}
	}

	cute_aseprite_free(animation);
}

void AnimationPlayer::Update(float millisecondsPerUpdate)
{
	if (currentFrameTime > 0) {
		currentFrameTime -= millisecondsPerUpdate;
	}
	else
	{
		if (currentFrame >= frameCount - 1) {
			currentFrame = 0;
		}
		else {
			currentFrame++;
		}

		currentFrameTime = static_cast<float>(cells[currentFrame].Duration());
	}
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour)
{
	renderer.Draw(cells[currentFrame].CellTexture(), position, colour);
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, float scale)
{
	Rectangle sourceRectangle = Rectangle(
		static_cast<float>(cells[currentFrame].CellTexture().Width()),
		static_cast<float>(cells[currentFrame].CellTexture().Height()),
		Vector2<float>::Zero());

	renderer.Draw(cells[currentFrame].CellTexture(), position, sourceRectangle,  colour, rotation, origin, scale);
}

void AnimationPlayer::Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, Vector2<float> scale)
{
	Rectangle sourceRectangle = Rectangle(
		static_cast<float>(cells[currentFrame].CellTexture().Width()),
		static_cast<float>(cells[currentFrame].CellTexture().Height()),
		Vector2<float>::Zero());

	renderer.Draw(cells[currentFrame].CellTexture(), position, sourceRectangle, colour, rotation, origin, scale);
}

AnimationPlayer::CellData::CellData(Texture&& texture, int duration)
	:texture(texture),
	duration(duration) { }