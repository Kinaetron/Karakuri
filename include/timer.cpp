#include "timer.h"

Timer::Timer(const float time): 
	time(time),
	timer(time),
	started(false)
{
}

void Timer::Reset() 
{
	timer = time;
	started = false;
}

void Timer::Update(float millisecondsPerUpdate) {
	if (started) {
		timer -= millisecondsPerUpdate;
	}
}

const bool Timer::OutOfTime() const
{
	bool something = timer <= 0.1f;

	if(started) {
		return something;
	}

	return true;
}
