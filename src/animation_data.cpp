#include "animation_data.h"
#include "aseprite.h"
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

AnimationData::AnimationData(const std::string& filepath):
	frameCount(0),
	frameWidth(0),
	frameHeight(0),
	currentFrame(0),
	currentFrameTime(0.0f),
	isLooping(true),
	logger(nullptr)
{
	InitializeAnimation(filepath);
}

AnimationData::AnimationData(const std::string& animationPath, const std::string& colliderPath):
	frameCount(0),
	frameWidth(0),
	frameHeight(0),
	currentFrame(0),
	currentFrameTime(0.0f),
	isLooping(true),
	logger(nullptr)
{
	InitializeAnimation(animationPath);

	if (filesystem::is_empty(colliderPath))
	{
		logger->error("Collider data didn't load from {}", colliderPath);
		return;
	}

	ifstream collider_file(colliderPath);
	json collider_data = json::parse(collider_file);

	int frameCount = collider_data["frameCount"];

	for (int i = 0; i < frameCount; i++)
	{
		if (collider_data["boxes"][i].empty()) {
			continue;
		}

		int boxCount = collider_data["boxes"][i][0]["boxCount"];

		Rectangle colliderbox;
		std::vector<Rectangle> hitboxes = std::vector<Rectangle>();
		std::vector<Rectangle> hurtboxes = std::vector<Rectangle>();

		for (int j = 1; j <= boxCount; j++)
		{
			int x = collider_data["boxes"][i][j]["x"];
			int y = collider_data["boxes"][i][j]["y"];
			int width = collider_data["boxes"][i][j]["width"];
			int height = collider_data["boxes"][i][j]["height"];
			std::string boxType = collider_data["boxes"][i][j]["boxType"];

			if (boxType == "colliderbox")
			{
				colliderbox = Rectangle(
					static_cast<float>(width),
					static_cast<float>(height),
					Vector2<float>(static_cast<float>(x), static_cast<float>(y)));
			}
			else if (boxType == "hitbox")
			{
				hitboxes.push_back(Rectangle(
					static_cast<float>(width),
					static_cast<float>(height),
					Vector2<float>(static_cast<float>(x), static_cast<float>(y))));
			}
			else if (boxType == "hurtbox")
			{
				hurtboxes.push_back(Rectangle(
					static_cast<float>(width),
					static_cast<float>(height),
					Vector2<float>(static_cast<float>(x), static_cast<float>(y))));
			}
		}

		FrameData frameData = FrameData(colliderbox, hitboxes, hurtboxes);
		frameDataList.push_back(frameData);
	}
}

void AnimationData::InitializeAnimation(const std::string& filepath)
{
	logger = spdlog::get("karakuri_logger");

	ase_t* animation = cute_aseprite_load_from_file(filepath.c_str(), NULL);

	if (animation == nullptr)
	{
		logger->error("Animation data didn't load from {}", filepath);
		return;
	}

	frameCount = animation->frame_count;
	frameWidth = animation->w;
	frameHeight = animation->h;

	for (int i = 0; i < frameCount; ++i)
	{
		ase_frame_t* frame = animation->frames + i;

		unsigned char* pixels = reinterpret_cast<unsigned char*>(frame->pixels);
		Texture cellTexture = Texture(frameWidth, frameHeight, 4, pixels);

		cells.push_back(CellData(std::move(cellTexture),
			frame->duration_milliseconds));

		if (i == 0) {
			currentFrameTime = static_cast<float>(frame->duration_milliseconds);
		}
	}

	cute_aseprite_free(animation);
}