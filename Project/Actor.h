#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameStruct.h"
#include "GameEngine.h"

#include "HealthComponent.h"


//-----------------------------------------------------
// Actor Class
//-----------------------------------------------------
class Actor
{
public:
	enum class type
	{
		actor,
		character,
		projectile
	};

	Actor(GameStruct::Box box, int health, int ID );	// Constructor
	virtual ~Actor();											// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	Actor(const Actor& other) = delete;
	Actor(Actor&& other) noexcept = delete;
	Actor& operator=(const Actor& other) = delete;
	Actor& operator=(Actor&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions
	//-------------------------------------------------
	virtual bool Draw() const;
	virtual bool Tick(float deltaTime);

	int GetID() const
	{
		return m_ActorID;
	}
	bool setID(int newID)
	{
		m_ActorID = newID;
		return true;
	}
	
	type GetActorType() const
	{
		return m_ActorType;
	}


	bool DealDamage(float amount);
	float GetHealth() const
	{
		return m_Health->GetHealth();
	}

	bool IsDead() const;

	GameStruct::Box GetBox() const
	{
		return m_Box;
	}
	GameStruct::point GetPoint() const
	{
		return GameStruct::point{ m_Box.X, m_Box.Y };
	}

protected:
	//-------------------------------------------------
	// Private member functions
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	GameStruct::Box m_Box;
	unique_ptr<HealthComponent> m_Health;

	int m_ActorID;
	bool m_IsDead;

	type m_ActorType;

};

