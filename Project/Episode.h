#pragma once

#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "QLearningCharacter.h"
#include "Delay.h"

#include <map>
#include <algorithm>

class Episode final
{
public:
	Episode();
	~Episode();

	void Render(bool renderNeuralNetwork = false) const;
	void Tick();

	bool IsFinished() const;
	int GetScore() const;
	NeuralNetwork GetNeuralNetwork() const;

	void SetStartNeuralNetwork(NeuralNetwork baseNeuralNetwork);


private:
	int m_LifeTime;
	int m_Score;

	int m_MaxLifeTime;

	unique_ptr<EnemyManager> m_pEnemyManager;				//Handling the enemies of this batch
	unique_ptr<QLearningCharacter> m_QlearningCharacter;	//The AI that will learn in this batch
	unique_ptr<ProjectileManager> m_pProjectileManager;		//The projectile manager of this batch
};

