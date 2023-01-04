#pragma once
#include "Character.h"
#include "Qlearning.h"
#include "Projectile.h"

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

	bool MoveLeft();
	bool MoveRight();
	bool Shoot();

	bool Tick(float deltaTime) override;
	bool Draw() const override;

	bool hasFired() override;

	bool GetInViewInfo(const Projectile* projectile);


private:
	bool m_SimulateFire;
	
	int m_ViewRange;
	
	GameStruct::point m_FrontProjectilePos;
	
	float m_FrontProjectileDistance;
	float m_LeftProjectileDistance;
	float m_RightProjectileDistance;

	bool m_HasReceivedInfo; 
	
	unique_ptr<Qlearning> m_pQlearning;

	bool HandleMovement(float deltaTime) override;

	bool ResetInfo();
	int GetSquaredDistance(GameStruct::point p1, GameStruct::point p2) const;
	int GetDistance(GameStruct::point p1, GameStruct::point p2) const;
};

