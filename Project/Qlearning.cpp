#include "Qlearning.h"

Qlearning::Qlearning()
	: discrete_obs_win_size{ GAME_ENGINE->GetWidth() / DISCRETE_OBS_SIZE }
{
	//Initializing the q_table
	q_table = new float** [SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		q_table[i] = new float* [DISCRETE_OBS_SIZE];
		for (int j = 0; j < DISCRETE_OBS_SIZE; j++)
		{
			q_table[i][j] = new float[discrete_obs_win_size];
			for (int k = 0; k < discrete_obs_win_size; k++)
			{
				q_table[i][j][k] = ((rand() % 200) - 400) / 100.f;
			}
		}
	}
}

Qlearning::~Qlearning()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < DISCRETE_OBS_SIZE; j++)
		{
			delete[] q_table[i][j];
		}
		delete[] q_table[i];
	}
	delete[] q_table;
}

bool Qlearning::Tick()
{
	return true;
}


bool Qlearning::get_discrete_state(float state)
{

}

int Qlearning::BellmanEquation(int reward)
{	
	return 0;
}

bool Qlearning::ReadyNewEpisode()
{
	return true;
}

float Qlearning::Output() const
{
	switch (m_CurrentAction)
	{
	case LEFT:

		return -1.f;

		break;
	case RIGHT:
		
		return 1.f;
		
		break;
	case NOTHING:
		
		return 0.f;

		break;
	}
	return 0.f;
}

bool Qlearning::ReceiveInfo(float frontDistance, float leftDistance, float rightDistance, float shipXvalue, float frontProjectileXValue)
{	
	//Getting the max value
	float maxFrontDistance	= GAME_ENGINE->GetHeight();
	float maxLeftDistance	= GAME_ENGINE->GetWidth();
	float maxRightDistance	= GAME_ENGINE->GetWidth();
	float maxShipXValue		= GAME_ENGINE->GetWidth();
	float maxFrontXValue	= GAME_ENGINE->GetWidth();

	//Scaling down to percentage
	float scaledFrontDistance	= frontDistance / maxFrontDistance;
	float scaledLeftDistance	= leftDistance	/ maxLeftDistance;
	float scaledRightDistance	= rightDistance / maxRightDistance;
	float scaledShipXvalue		= shipXvalue	/ maxShipXValue;
	float scaledFrontXValue		= frontProjectileXValue / maxFrontXValue;

	//putting in observation table
	m_ObservationTable[static_cast<int>(frontDistance)] = scaledFrontDistance;
	m_ObservationTable[static_cast<int>(leftDistance)] = scaledLeftDistance;
	m_ObservationTable[static_cast<int>(rightDistance)] = scaledRightDistance;
	m_ObservationTable[static_cast<int>(shipX)] = scaledShipXvalue;
	m_ObservationTable[static_cast<int>(frontX)] = scaledFrontXValue;

	return true;
}