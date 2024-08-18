#include "timer.h"
#include "update_manager.h"

Timer::Timer(const float time): 
	time(time),
	timer(time),
	started(false)
{
	UpdateManager::Add(this);
}

Timer::~Timer() {
	UpdateManager::Remove(this);
}

void Timer::Reset() 
{
	timer = time;
	started = false;
}

void Timer::Update(float millisecondsPerUpdate) 
{
	if (started) {
		timer = timer <= 0 ? 0 : timer - millisecondsPerUpdate;
	}
}

const bool Timer::OutOfTime() const
{
	bool withinError = timer <= 0.1f;
	return started ? withinError : true;
}

const float Timer::Time() const {
	return started ? timer : 0.0f;
}
