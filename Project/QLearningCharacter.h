#pragma once
#include "Character.h"
#include "Qlearning.h"
#include "Projectile.h"

#include "Delay.h"

#include "FileWriter.h"


class QLearningCharacter : public Character
{
public:
	QLearningCharacter(GameStruct::Box box, float health, float speed, bool isPossessed, GameStruct::vector2 forwardVector, int ID);
	~QLearningCharacter();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	QLearningCharacter(const QLearningCharacter& other) = delete;
	QLearningCharacter(QLearningCharacter&& other) noexcept = delete;
	QLearningCharacter& operator=(const QLearningCharacter& other) = delete;
	QLearningCharacter& operator=(QLearningCharacter&& other)	noexcept = delete;

	NeuralNetwork GetNeuralNetwork() const
	{
		return m_pQlearning->GetNeuralNetwork();
	}
	void SetBaseNeuralNetwork( NeuralNetwork baseNeuralNetwork );

	bool MoveLeft();
	bool MoveRight();
	bool Shoot();

	bool Tick(float deltaTime) override;
	bool Draw() const override;

	bool DrawNeuralNetwork() const;

	bool hasFired() override;
	
	int GetLifeTime() const
	{
		return m_LifeTime;
	}

	bool GetAllBullets(std::vector<Projectile*> enemyBullets);

	bool GetInViewInfo(GameStruct::Box enemyBox);
	bool GetEpisodeTime(GameStruct::point episodeTime)
	{
		m_EpisodeTime = episodeTime;
		return true;
	}

private:
	int m_LifeTime;

	bool m_SimulateFire;
	
	int m_ViewRange;
	
	GameStruct::point m_BulletOnePos;
	GameStruct::point m_BulletTwoPos;
	GameStruct::point m_BulletThreePos;
	GameStruct::point m_EpisodeTime;
	bool  m_IsEnemyInSight;

	bool m_HasReceivedInfo; 
	
	unique_ptr<Qlearning> m_pQlearning;

	unique_ptr<Delay> m_pShootDelay;


	bool HandleMovement(float deltaTime) override;

	bool ResetInfo();
	int GetSquaredDistance(GameStruct::point p1, GameStruct::point p2) const;
	int GetDistance(GameStruct::point p1, GameStruct::point p2) const;
};

