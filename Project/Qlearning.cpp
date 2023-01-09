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

int Qlearning::Output() const
{
	float leftValue{ m_pNeuralNetwork->GetInputLayer()->vecNeurons[0]->value };
	float rightValue{ m_pNeuralNetwork->GetInputLayer()->vecNeurons[1]->value };
	float shootValue{ m_pNeuralNetwork->GetInputLayer()->vecNeurons[2]->value };


	if (rightValue > leftValue)
	{
		if (shootValue > rightValue)
		{
			return static_cast<int>(actions::SHOOT);
		}
		return static_cast<int>(actions::RIGHT);
	}
	else
	{
		if (shootValue > leftValue)
		{
			return static_cast<int>(actions::SHOOT);
		}
		return static_cast<int>(actions::LEFT);
	}
	return 0;
}

bool Qlearning::ReceiveInfo(float frontDistance, float leftDistance, float rightDistance, float shipXvalue, float frontProjectileXValue, bool enemyInSight, Delay& shootDelay, GameStruct::point episodeTime)
{	
	//Getting the max value
	float maxFrontDistance	= GAME_ENGINE->GetGameHeight();
	float maxLeftDistance	= GAME_ENGINE->GetGameWidth();
	float maxRightDistance	= GAME_ENGINE->GetGameWidth();
	float maxShipXValue		= GAME_ENGINE->GetGameWidth();
	float maxFrontXValue	= GAME_ENGINE->GetGameWidth();
	float maxShootDelay		= shootDelay.GetDelay();
	float maxEpisodeTime	= episodeTime.Y;

	//Scaling down to percentage
	float scaledFrontDistance	= frontDistance / maxFrontDistance;
	float scaledLeftDistance	= leftDistance	/ maxLeftDistance;
	float scaledRightDistance	= rightDistance / maxRightDistance;
	float scaledShipXvalue		= shipXvalue	/ maxShipXValue;
	float scaledFrontXValue		= frontProjectileXValue / maxFrontXValue;
	float scaledShootDelay		= shootDelay.GetCounter() / maxShootDelay;
	float scaledEpisodeTime		= episodeTime.X / maxEpisodeTime;

	m_pNeuralNetwork->GetInputLayer()->vecNeurons[0]->value = scaledFrontDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[1]->value = scaledLeftDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[2]->value = scaledRightDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[3]->value = scaledShipXvalue;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[4]->value = scaledFrontXValue;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[5]->value = enemyInSight;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[6]->value = scaledShootDelay;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[7]->value = scaledEpisodeTime;


	return true;
}

void Qlearning::SetNeuralNetworkWeights(std::vector<Connection*> connections)
{
	m_pNeuralNetwork->SetConnections(connections);
}