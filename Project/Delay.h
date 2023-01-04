#pragma once
#include "GameEngine.h"

class Delay
{
public:
	Delay(float delay);
	~Delay();

	bool Tick();
	bool IsDone() const;

	bool Reset();

	bool SetDelay(float delay);

	float GetCounter() const;

private:
	float m_Counter;
	float m_Delay;


};

