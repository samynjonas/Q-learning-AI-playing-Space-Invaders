#include "Enemy.h"

BaseEnemy::BaseEnemy(GameStruct::Box box, GameStruct::vector2 forwardVector)
	: Actor(box, 1, 2)
	, m_Speed{ 1 }
	, m_ForwardVector{ forwardVector }
{
	m_Box.Width		= 50;
	m_Box.Height	= 30;

	m_Scoring		= 10;

	m_ActorType = type::enemy;
}

BaseEnemy::~BaseEnemy()
{

}

bool BaseEnemy::Draw() const
{
	GAME_ENGINE->SetColor(RGB(10, 150, 150));

	if (m_IsDead)
	{
		GAME_ENGINE->SetColor(RGB(255, 150, 150));
	}

	GAME_ENGINE->FillRect(m_Box.X, m_Box.Y, m_Box.Width, m_Box.Height);

	return true;
}
bool BaseEnemy::Tick(float deltaT)
{
	return true;
}

bool BaseEnemy::hasFired()
{
	int shoot = rand() % SHOOTCHANCE;
	if (shoot == 1)
	{
		return true;
	}

	return false;
}


void BaseEnemy::Move(float x, float y)
{
	m_Box.X += x;
	m_Box.Y += y;
}

//Other types
Crab::Crab(GameStruct::Box box, GameStruct::vector2 forwardVector)
	: BaseEnemy(box, forwardVector)
{
	m_Box.Width	 = 44;
	m_Box.Height = 24;
				 
	m_Scoring	 = 20;
}

Crab::~Crab()
{

}

Squid::Squid(GameStruct::Box box, GameStruct::vector2 forwardVector)
	: BaseEnemy(box, forwardVector)
{
	m_Box.Width  = 24;
	m_Box.Height = 24;

	m_Scoring	 = 30;
}

Squid::~Squid()
{

}

Octopus::Octopus(GameStruct::Box box, GameStruct::vector2 forwardVector)
	: BaseEnemy(box, forwardVector)
{
	m_Box.Width  = 48;
	m_Box.Height = 24;

	m_Scoring	 = 10;
}

Octopus::~Octopus()
{

}