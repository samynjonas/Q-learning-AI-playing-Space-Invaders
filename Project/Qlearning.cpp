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
	float leftValue{	m_pNeuralNetwork->GetInputLayer()->vecNeurons[0]->value };
	float rightValue{	m_pNeuralNetwork->GetInputLayer()->vecNeurons[1]->value };
	float shootValue{	m_pNeuralNetwork->GetInputLayer()->vecNeurons[2]->value };


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


bool Qlearning::ReceiveInfo(GameStruct::point bulletOne, GameStruct::point bulletTwo, GameStruct::point bulletThree, float shipXvalue, float distanceLeftBorder, float distanceRightBorder, bool enemyInSight, Delay& shootDelay, GameStruct::point episodeTime)
{
	//Max values
	float maxBulletOneX				= GAME_ENGINE->GetGameWidth();
	float maxBulletOneY				= GAME_ENGINE->GetGameHeight();
	float maxBulletTwoX				= GAME_ENGINE->GetGameWidth();
	float maxBulletTwoY				= GAME_ENGINE->GetGameHeight();
	float maxBulletThreeX			= GAME_ENGINE->GetGameWidth();
	float maxBulletThreeY			= GAME_ENGINE->GetGameHeight();

	float maxShipX					= GAME_ENGINE->GetGameWidth();
	float maxDistanceLeftBorder		= GAME_ENGINE->GetGameWidth();
	float maxDistanceRightBorder	= GAME_ENGINE->GetGameWidth();
		  
	float maxShootDelay				= shootDelay.GetDelay();
	float maxEpisodeTime			= episodeTime.Y;


	//Scaled values
	float scaledBulletOneX			= bulletOne.X			/ maxBulletOneX;
	float scaledBulletOneY			= bulletOne.Y			/ maxBulletOneY;
	float scaledBulletTwoX			= bulletTwo.X			/ maxBulletTwoX;
	float scaledBulletTwoY			= bulletTwo.Y			/ maxBulletTwoY;
	float scaledBulletThreeX		= bulletThree.X			/ maxBulletThreeX;
	float scaledBulletThreeY		= bulletThree.Y			/ maxBulletThreeY;
		  
	float scaledShipX				= shipXvalue			/ maxShipX;
	float scaledDistanceLeftBorder	= distanceLeftBorder	/ maxDistanceLeftBorder;
	float scaledDistanceRightBorder = distanceRightBorder	/ maxDistanceRightBorder;
		  
	float scaledShootDelay			= shootDelay.GetCounter() / maxShootDelay;
	float scaledEpisodeTime			= episodeTime.X / maxEpisodeTime;

	//Sent to neural network
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[0]->value = scaledBulletOneX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[1]->value = scaledBulletOneY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[2]->value = scaledBulletTwoX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[3]->value = scaledBulletTwoY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[4]->value = scaledBulletThreeX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[5]->value = scaledBulletThreeY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[6]->value = scaledShipX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[7]->value = scaledDistanceLeftBorder;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[8]->value = scaledDistanceRightBorder;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[9]->value = enemyInSight;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[10]->value = scaledShootDelay;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[11]->value = scaledEpisodeTime;

	return true;
}

void Qlearning::SetNeuralNetworkWeights(std::vector<Connection*> connections)
{
	m_pNeuralNetwork->SetConnections(connections);
}