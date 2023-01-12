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


bool Qlearning::ReceiveInfo(GameStruct::point bulletOne, GameStruct::point bulletTwo, GameStruct::point bulletThree, GameStruct::point playerPos, int maxEnemies, int enemyCount, GameStruct::point closestEnemy, Delay& shootDelay, GameStruct::point episodeTime)
{
	//Max values
	float maxBulletOneX				= GAME_ENGINE->GetGameWidth();
	float maxBulletOneY				= GAME_ENGINE->GetGameHeight();
	float maxBulletOneDistance		= GAME_ENGINE->GetGameHeight();
	float maxBulletTwoX				= GAME_ENGINE->GetGameWidth();
	float maxBulletTwoY				= GAME_ENGINE->GetGameHeight();
	float maxBulletTwoDistance		= GAME_ENGINE->GetGameHeight();
	float maxBulletThreeX			= GAME_ENGINE->GetGameWidth();
	float maxBulletThreeY			= GAME_ENGINE->GetGameHeight();
	float maxBulletThreeDistance	= GAME_ENGINE->GetGameHeight();

	float maxShipX					= GAME_ENGINE->GetGameWidth();
	float maxDistanceLeftBorder		= GAME_ENGINE->GetGameWidth();
	float maxDistanceRightBorder	= GAME_ENGINE->GetGameWidth();
		  
	float maxShootDelay				= shootDelay.GetDelay();
	float maxEpisodeTime			= episodeTime.Y;

	float maxDistanceClosestEnemy	= GAME_ENGINE->GetGameHeight();
	float maxEnemyCount				= maxEnemies;


	//Scaled values
	float scaledBulletOneX				= bulletOne.X									/ maxBulletOneX;
	float scaledBulletOneY				= bulletOne.Y									/ maxBulletOneY;
	float scaledBulletOneDistance		= playerPos.distance(bulletOne)					/ maxBulletOneDistance;
	float scaledBulletTwoX				= bulletTwo.X									/ maxBulletTwoX;
	float scaledBulletTwoY				= bulletTwo.Y									/ maxBulletTwoY;
	float scaledBulletTwoDistance		= playerPos.distance(bulletTwo)					/ maxBulletTwoDistance;
	float scaledBulletThreeX			= bulletThree.X									/ maxBulletThreeX;
	float scaledBulletThreeY			= bulletThree.Y									/ maxBulletThreeY;
	float scaledBulletThreeDistance		= playerPos.distance(bulletThree)				/ maxBulletThreeDistance;

	float scaledShipX					= playerPos.X									/ maxShipX;
	float scaledDistanceLeftBorder		= playerPos.X									/ maxDistanceLeftBorder;
	float scaledDistanceRightBorder		= (GAME_ENGINE->GetGameWidth() - playerPos.X)	/ maxDistanceRightBorder;
		  
	float scaledShootDelay				= shootDelay.GetCounter()						/ maxShootDelay;
	float scaledEpisodeTime				= episodeTime.X									/ maxEpisodeTime;

	float scaledDistanceClosestEnemy	= playerPos.distance(closestEnemy)				/ maxDistanceClosestEnemy;
	float scaledEnemyCount				= enemyCount									/ maxEnemyCount;

	//Sent to neural network
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletOneX)]->value				= scaledBulletOneX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletOneY)]->value				= scaledBulletOneY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletOneDistance)]->value		= scaledBulletOneDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletTwoX)]->value				= scaledBulletTwoX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletTwoY)]->value				= scaledBulletTwoY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletTwoDistance)]->value		= scaledBulletTwoDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletThreeX)]->value			= scaledBulletThreeX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletThreeY)]->value			= scaledBulletThreeY;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(bulletThreeDistance)]->value		= scaledBulletThreeDistance;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(ShipX)]->value					= scaledShipX;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(DistanceLeftBorder)]->value		= scaledDistanceLeftBorder;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(DistanceRightBorder)]->value		= scaledDistanceRightBorder;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(DistanceClosestEnemy)]->value	= scaledDistanceClosestEnemy;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(EnemyCount)]->value				= scaledEnemyCount;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(ShootDelay)]->value				= scaledShootDelay;
	m_pNeuralNetwork->GetInputLayer()->vecNeurons[static_cast<int>(EpisodeTime)]->value				= scaledEpisodeTime;

	return true;
}

void Qlearning::SetNeuralNetworkWeights(std::vector<Connection*> connections)
{
	m_pNeuralNetwork->SetConnections(connections);
}