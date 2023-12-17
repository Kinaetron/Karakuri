#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <vector>
#include <string>
#include "sprite_renderer.h"
#include <memory>

namespace spdlog {
	class logger;
}

class AnimationPlayer
{
public:
	AnimationPlayer(const AnimationPlayer& that) = default;
	AnimationPlayer(AnimationPlayer&& that) = default;
	AnimationPlayer& operator=(const AnimationPlayer& rhs) = default;
	AnimationPlayer& operator=(AnimationPlayer&& rhs) = default;
	AnimationPlayer(const std::string& filepath, SpriteRenderer& renderer);
	void Update(float millisecondsPerUpdate);
	void Draw(Vector2<float> position, Colour colour);
	void Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, float scale);
	void Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, Vector2<float> scale);
	void Loop(bool loop) { isLooping = loop; }
	void Destroy();

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

	bool isLooping;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int currentFrame;
	float currentFrameTime;

	std::vector<CellData> cells;
	SpriteRenderer& renderer;
	std::shared_ptr<spdlog::logger> logger;
};

#endif
