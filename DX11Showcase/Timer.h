#pragma once
#include <Windows.h>

class Timer 
{
public:
	Timer();
	~Timer();

	float DeltaTime() const;
	void Reset();
	void Frame();

	static Timer& Instance()
	{
		static Timer instance;
		return instance;
	}

	Timer(Timer const&) = delete;
	void operator=(Timer const&) = delete;

private:
	double secondsPerCount;
	double deltaTime;

	__int64 baseTime;
	__int64 prevTime;
	__int64 currentTime;
};