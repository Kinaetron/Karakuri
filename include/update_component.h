#ifndef UPDATE_COMPONENT_H
#define UPDATE_COMPONENT_H

#include "game.h"

class UpdateComponent
{
protected:
	virtual void Update(float millisecondsPerUpdate) = 0;
	friend class Game;
};
#endif