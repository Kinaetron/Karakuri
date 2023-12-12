#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <vector>
#include <string>
#include "sprite_renderer.h"

class AnimationPlayer
{
public:
	AnimationPlayer(const AnimationPlayer& that) = default;
	AnimationPlayer(AnimationPlayer&& that) = default;
	AnimationPlayer& operator=(const AnimationPlayer& rhs) = default;
	AnimationPlayer& operator=(AnimationPlayer&& rhs) = default;
	AnimationPlayer(const std::string& filepath, SpriteRenderer& renderer);
	void Update(float millisecondsPerUpdate);
	void Draw();

private:
	class CellData
	{
	public:
		CellData(const CellData& that) = default;
		CellData(CellData&& that) = default;
		CellData& operator=(const CellData& rhs) = default;
		CellData& operator=(CellData&& rhs) = default;
		CellData(Texture&& texture, int duration);
		int Duration() const { return duration; }
		Texture& CellTexture() { return texture; }

	private:
		const int duration;
		Texture texture;
	};

	int frameCount;
	int frameWidth;
	int frameHeight;
	int currentFrame;
	float currentFrameTime;

	std::vector<CellData> cells;
	SpriteRenderer& renderer;
};

#endif
