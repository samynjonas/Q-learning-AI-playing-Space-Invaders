#include "Projectile.h"


Projectile::Projectile(GameStruct::Box box, float speed, GameStruct::vector2 direction)
	: Actor(box, 1, 0)
	, m_Speed{ speed }
	, m_Direction{ direction }
{
	m_ActorType = type::projectile;

	m_IgnoreID.push_back(0);
}

Projectile::~Projectile()
{

}


bool Projectile::Draw() const
{
	GAME_ENGINE->SetColor(RGB(50, 50, 150));
	GAME_ENGINE->FillRect(m_Box.X, m_Box.Y, m_Box.Width, m_Box.Height);

	return true;
}

bool Projectile::Tick(float deltaTime)
{
	m_Box.Y += m_Direction.Y * m_Speed * deltaTime;
	m_Box.X += m_Direction.X * m_Speed * deltaTime;

	return true;
}

bool Projectile::AddIgnoreID(int ID)
{
	for (const int& IDs : m_IgnoreID)
	{
		if (IDs == ID)
		{
			return false;
		}
	}

	m_IgnoreID.push_back(ID);
	
	return true;
}

bool Projectile::containsIgnoreId(int ID) const
{
	for (const int& IDs : m_IgnoreID)
	{
		if (IDs == ID)
		{
			return true;
		}
	}

	return false;
}