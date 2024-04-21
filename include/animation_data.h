#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

#include <string>
#include <vector>
#include "texture.h"
#include "cell_data.h"
#include "frame_data.h"

namespace spdlog {
	class logger;
}

class AnimationData
{
public:
	AnimationData(const AnimationData& that) = default;
	AnimationData(AnimationData&& that) = default;
	AnimationData& operator=(const AnimationData& rhs) = default;
	AnimationData& operator=(AnimationData&& rhs) = default;

	/*
	* 2D animation player.
	*
	* \param filepath to the aseprite file you want to play.
	*/
	AnimationData(const std::string& filepath);

	/*
	* 2D animation data.
	*
	* \param filepath to the aseprite file you want to play.
	* \param filepath to the json file with the collision data.
	*/
	AnimationData(const std::string& animationPath, const std::string& colliderPath);

	/*
	* Allows you to see if the animation needs to be looped.
	*/
	const bool IsLooping() const { return isLooping; }

	/*
	* See the numbers of frames a animation has.
	*/
	const int FrameCount() const { return frameCount; }

	/*
	* Get a cell of animation.
	*/
	CellData& Cell(int index) { return cells[index]; }


	/*
	* Get a frame of the animation.
	*/
	FrameData& Frame(int index) { return frameDataList[index]; }

private:
	void InitializeAnimation(const std::string& filepath);

	bool isLooping;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int currentFrame;
	float currentFrameTime;

	std::vector<FrameData> frameDataList;
	std::vector<CellData> cells;
	std::shared_ptr<spdlog::logger> logger;
};

#endif // !ANIMATION_DATA_H