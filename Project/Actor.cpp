//---------------------------
// Includes
//---------------------------
#include "Actor.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Actor::Actor(GameStruct::Box box, int health, int ID)
	: m_Box{ box }
	, m_ActorID{ ID }
	, m_Health{ make_unique<HealthComponent>(health) }
	, m_IsDead{ false }
	, m_ActorType{ type::actor }
{
	// nothing to create
}

Actor::~Actor()
{
	// nothing to destroy
}

//---------------------------
// Member functions
//---------------------------

bool Actor::Draw() const
{
	//GAME_ENGINE->SetColor()
	return GAME_ENGINE->DrawRect(m_Box.X, m_Box.Y, m_Box.Width, m_Box.Height);
}


bool Actor::Tick(float deltaTime)
{
	return true;
}

bool Actor::DealDamage(float amount)
{
	m_Health->Damage(amount);
	if (m_Health->GetHealth() <= 0)
	{
		m_IsDead = true;
	}
	return true;
}

bool Actor::IsDead() const
{
	return m_IsDead;
}