#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include "GameEngine.h"

class Qlearning
{
public:
	Qlearning();
	~Qlearning();

	bool Tick();

	bool ReadyNewEpisode();

	int BellmanEquation(int reward);

	bool ReceiveInfo(float frontDistance, float leftDistance, float rightDistance, float shipXvalue, float frontProjectileXValue);

	float Output() const;

private:
	//actions
	//move left - move right - shoot
	const enum actions 
	{
		LEFT,
		RIGHT,
		NOTHING
	};
	const int NUM_OF_ACTIONS = 3;
	actions m_CurrentAction{ actions::LEFT };

	//Observation variables
	const enum observation
	{
		frontDistance	= 0,
		leftDistance	= 1,
		rightDistance	= 2,
		shipX			= 3,
		frontX			= 4
	};
	const int NUM_OF_OBSERVATIONS{ 5 };
	float m_ObservationTable[5] = { 0.f, 0.f, 0.f, 0.f, 0.f }; //One state

	const int SIZE = 20;
	const int DISCRETE_OBS_SIZE = SIZE * NUM_OF_OBSERVATIONS;
	float discrete_obs_win_size;
	
	float*** q_table;


	const float LEARNING_RATE = 0.1f;
	const float DISCOUNT = 0.95f;
	const int EPISODES = 25000;


	bool get_discrete_state(float state);

};

