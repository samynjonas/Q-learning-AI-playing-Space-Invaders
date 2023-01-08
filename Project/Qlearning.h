#pragma once
#include <iostream>
#include <random>
#include <algorithm>

#include "NeuralNetwork.h"
#include "GameEngine.h"

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


	int BellmanEquation(int reward);

	bool ReceiveInfo(float frontDistance, float leftDistance, float rightDistance, float shipXvalue, float frontProjectileXValue, bool enemyInSight);

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
		frontDistance	= 0,
		leftDistance	= 1,
		rightDistance	= 2,
		shipX			= 3,
		frontX			= 4,
		EnemyInSight	= 5
	};


	unique_ptr<NeuralNetwork> m_pNeuralNetwork;


	bool get_discrete_state(float state);
};

