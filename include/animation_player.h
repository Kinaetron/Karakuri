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
	/*
	* 2D animation player.
	*
	* \param filepath to the aseprite file you want to play.
	* \param renderer is a SpriteRennderer.
	*/
	AnimationPlayer(const std::string& filepath, SpriteRenderer& renderer);
	/*
	* Updates the state of the animation being played. Call it in the games update method.
	* 
	* \param millisecondsPerUpdate is the time the game takes to to call the update method, default should be 16.67
	*/
	void Update(float millisecondsPerUpdate);
	/*
	* Draws the cell of the of a animation
	* 
	* \param position is sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	*/
	void Draw(Vector2<float> position, Colour colour);
	/*
	* Draws the cell of the of a animation
	*
	* \param position is sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	* \param rotation sets the rotation of the animation cell in radians.
	* \param origin sets the point on the animation cell where it will be rotated around and where cell be start position.
	* \param scale increases or decreases the size of the cell based off of value.
	*/
	void Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, float scale);
	/*
	* Draws the cell of the of a animation
	*
	* \param position is sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	* \param rotation sets the rotation of the animation cell in radians.
	* \param origin sets the point on the animation cell where it will be rotated around and where cell be start position.
	* \param scale increases or decreases the size of the cell based off of value.
	*/
	void Draw(Vector2<float> position, Colour colour, float rotation, Vector2<float> origin, Vector2<float> scale);
	/*
	* Sets if the animation loops or not.
	* \param loop sets if the animation loops true or false.
	*/
	void Loop(bool loop) { isLooping = loop; }
	/*
	* This method destroys all the objects used by the animation system. Call it when you're closing the animation system.
	*/
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
