#pragma once
#include <iostream>
#include <random>
#include <algorithm>

#include "NeuralNetwork.h"
#include "GameEngine.h"
#include "Delay.h"

class Qlearning
{
public:
	Qlearning();
	~Qlearning();

	bool Tick();

	bool ReadyNewEpisode();

	bool Render();

	NeuralNetwork GetNeuralNetwork() const
	{
		return *m_pNeuralNetwork;
	}

	void SetNeuralNetworkWeights( std::vector<Connection*> connections );

	int BellmanEquation(int reward);

	bool ReceiveInfo(GameStruct::point bulletOne, GameStruct::point bulletTwo, GameStruct::point bulletThree, GameStruct::point playerPos, int maxEnemyCount, int enemyCount, GameStruct::point closestEnemy, Delay& shootDelay, GameStruct::point episodeTime);



	int Output() const;

private:
	//actions
	//move left - move right - shoot
	const enum actions 
	{
		LEFT,
		RIGHT,
		SHOOT
	};

	//Observation variables
	const enum observation
	{
		bulletOneX				= 0,
		bulletOneY				= 1,
		bulletOneDistance		= 2,
		bulletTwoX				= 3,
		bulletTwoY				= 4,
		bulletTwoDistance		= 5,
		bulletThreeX			= 6,
		bulletThreeY			= 7,
		bulletThreeDistance		= 8,
		ShipX					= 9,
		DistanceLeftBorder		= 10,
		DistanceRightBorder		= 11,
		DistanceClosestEnemy	= 12,
		EnemyCount				= 13,
		ShootDelay				= 15,
		EpisodeTime				= 16,
	};


	unique_ptr<NeuralNetwork> m_pNeuralNetwork;


	bool get_discrete_state(float state);
};

