#pragma once
#include "Actor.h"

#include "Controller.h"
#include "inputController.h"
#include "AIcontroller.h"

class Character : public Actor
{
public:
	Character(GameStruct::Box box, float health, float speed, bool isPossessed, GameStruct::vector2 forwardVector, int ID);
	virtual ~Character();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other)	noexcept = delete;

	bool Draw() const override;
	virtual bool Tick(float deltaTime) override;

	bool SetKeepInWorld(bool set);

	virtual bool hasFired();

	GameStruct::vector2 GetForwardVector() const
	{
		return m_ForwardVector;
	}

protected:
	// -------------------------
	//Functions-----------------
	// -------------------------
	virtual bool HandleMovement(float deltaTime);
	bool KeepInWorld();

	// -------------------------
	//Variables-----------------
	// -------------------------
	unique_ptr<Controller>	m_Controller;

	float m_Speed;
	bool m_Possessed;

	GameStruct::vector2 m_ForwardVector;

	bool m_KeepInWorld = true;
};