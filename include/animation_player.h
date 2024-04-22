#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <vector>
#include <string>
#include <memory>
#include "frame_data.h"
#include "sprite_mirror.h"
#include "animation_data.h"
#include "sprite_renderer.h"

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
	* \param renderer is a SpriteRennderer.
	*/
	AnimationPlayer(SpriteRenderer& renderer);

	/*
	* The data of the animation that the player will play.
	*  \param data is a AnimationData.
	*/
	void Play(AnimationData* data);

	FrameData* GetFrameData();

	/*
	* Updates the state of the animation being played. Call it in the games update method.
	* 
	* \param millisecondsPerUpdate is the time the game takes to to call the update method, default should be 16.67.
	*/
	void Update(float millisecondsPerUpdate);

	/*
	* Draws the cell of the of a animation
	* 
	* \param position is sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	*/
	void Draw(Vector2<float> position, Colour colour, SpriteMirror mirror);

	/*
	* Draws the cell of the of a animation
	*
	* \param position is sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	* \param rotation sets the rotation of the animation cell in radians.
	* \param origin sets the point on the animation cell where it will be rotated around and where cell be start position.
	* \param scale increases or decreases the size of the cell based off of value.
	*/
	void Draw(Vector2<float> position, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, float scale);

	/*
	* Draws the cell of the of a animation
	*
	* \param position sets the position of the animation cell being drawn.
	* \param colour sets the colour of the animation cell.
	* \param rotation sets the rotation of the animation cell in radians.
	* \param origin sets the point on the animation cell where it will be rotated around and where cell be start position.
	* \param scale increases or decreases the size of the cell based off of value.
	*/
	void Draw(Vector2<float> position, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, Vector2<float> scale);

	/*
	* This method destroys all the objects used by the animation system. Call it when you're closing the animation system.
	*/
	void Destroy();

private:
	int currentFrame;
	float currentFrameTime;
	SpriteRenderer& renderer;
	AnimationData* animationData;
	std::shared_ptr<spdlog::logger> logger;
};

#endif
