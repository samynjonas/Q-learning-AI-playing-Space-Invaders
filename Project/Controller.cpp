#include "Controller.h"

Controller::Controller()
	: m_pDelay{ make_unique<Delay>(1000) }
	, BASESHOOTDELAY{ 2000 }
	, SHOOTOFFSET{ 1000 }
{
	m_pDelay->SetDelay(RandomDelay());
}

Controller::~Controller()
{

}

bool Controller::Tick()
{
	m_pDelay->Tick();

	return true;
}

int Controller::RandomDelay() const
{
	return BASESHOOTDELAY + ((rand() % SHOOTOFFSET) - (SHOOTOFFSET / 2));
}