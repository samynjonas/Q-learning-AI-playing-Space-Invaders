#include "Delay.h"


Delay::Delay(float delay)
	: m_Delay{ delay }
	, m_Counter{ 0.f }
{

}

Delay::~Delay()
{

}

bool Delay::Tick()
{
	if (IsDone() == false)
	{
		m_Counter += GAME_ENGINE->GetFrameDelay();
	}
	return true;
}

bool Delay::IsDone() const
{
	if (m_Counter >= m_Delay)
	{
		return true;
	}
	return false;
}

bool Delay::Reset()
{
	m_Counter = 0;

	return true;
}

bool Delay::SetDelay(float delay)
{
	m_Delay = delay;

	return true;
}

float Delay::GetCounter() const
{
	return m_Counter;
}