#ifndef TIMER_H
#define TIMER_H

#include "update_component.h"

class Timer: public UpdateComponent
{
public:
	Timer(const Timer& that) = default;
	Timer(Timer&& that) = default;
	Timer& operator=(const Timer& rhs) = default;
	Timer& operator=(Timer&& rhs) = default;

	Timer(float time);
	~Timer();
	void Reset();
	void Start() { started = true; }
	const bool Started() const { return started; }
	const bool OutOfTime() const;
	const float Time() const;

private:
	void Update(float millisecondsPerUpdate) override;

private:
	const float time;
	float timer;
	bool started;
};
#endif // !TIMER_H