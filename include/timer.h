#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer(const Timer& that) = default;
	Timer(Timer&& that) = default;
	Timer& operator=(const Timer& rhs) = default;
	Timer& operator=(Timer&& rhs) = default;

	Timer(float time);
	void Reset();
	void Update(float millisecondsPerUpdate);
	void Start() { started = true; }
	const bool Started() const { return started; }
	const bool OutOfTime() const;
	const float Time() const;

private:
	const float time;
	float timer;
	bool started;
};
#endif // !TIMER_H