#include "Qlearning.h"

Qlearning::Qlearning()
	: m_pNeuralNetwork{ make_unique<NeuralNetwork>() }
{
	
}

Qlearning::~Qlearning()
{
	
}

bool Qlearning::Tick()
{
	m_pNeuralNetwork->Update();

	return true;
}

bool Qlearning::Render()
{
	m_pNeuralNetwork->Render();

	return true;
}


bool Qlearning::get_discrete_state(float state)
{

	return false;
}

int Qlearning::BellmanEquation(int reward)
{	
	//new value = current value(S, A) + learningrate * (Reward + discount rate * MaxQ - current Q)



	return 0;
}

bool Qlearning::ReadyNewEpisode()
{
	return true;
}

float Qlearning::Output() const
{
	
	return 0.f;
}

bool Qlearning::ReceiveInfo(float frontDistance, float leftDistance, float rightDistance, float shipXvalue, float frontProjectileXValue, bool enemyInSight)
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


	m_pNeuralNetwork->GetInputLayer()->vecNeurons[0]->value = scaledFrontDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[1]->value = scaledLeftDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[2]->value = scaledRightDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[3]->value = scaledShipXvalue;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[4]->value = scaledFrontXValue;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[5]->value = enemyInSight;


	return true;
}