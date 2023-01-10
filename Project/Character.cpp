#include "Character.h"

Character::Character(GameStruct::Box box, float health, float moveSpeed, bool isPossessed, GameStruct::vector2 forwardVector, int ID)
	: Actor( box, health, ID )
	, m_Speed{ moveSpeed }
	, m_Possessed{ isPossessed }
	, m_ForwardVector{ forwardVector }
{
	m_ActorType = type::character;


	if (isPossessed)
	{
		m_Controller = make_unique<inputController>();
	}
	else
	{
		m_Controller = make_unique<AIcontroller>();
	}
}

Character::~Character()
{
	
}


bool Character::Draw() const
{
	if (m_Possessed)
	{
		GAME_ENGINE->SetColor(RGB(10, 10, 10));
	}
	else
	{
		GAME_ENGINE->SetColor(RGB(10, 100, 10));
	}


	if (m_IsDead)
	{
		GAME_ENGINE->SetColor(RGB(150, 10, 10));
	}

	GAME_ENGINE->FillRect(m_Box.X, m_Box.Y, m_Box.Width, m_Box.Height);

	return true;
}

bool Character::HandleMovement(float deltaTime)
{
	GameStruct::vector2 movementVector{ m_Controller->GetMovement().normalize() };

	movementVector *= m_Speed * GAME_ENGINE->GetGameSpeed();
	movementVector *= deltaTime;

	m_Box.X -= movementVector.X;
	m_Box.Y -= movementVector.Y;

	return true;
}

bool Character::Tick(float deltaTime)
{
	HandleMovement(deltaTime);

	m_Controller->Tick();

	if (m_KeepInWorld)
	{
		KeepInWorld();
	}

	return true;
}

bool Character::SetKeepInWorld(bool set = true)
{
	m_KeepInWorld = set;
	return m_KeepInWorld;
}

bool Character::KeepInWorld()
{
	if (m_Box.X < 0)
	{
		m_Box.X = 0 + 1;
	}

	if (m_Box.X + m_Box.Width > GAME_ENGINE->GetGameWidth())
	{
		m_Box.X = GAME_ENGINE->GetGameWidth() - m_Box.Width - 1;
	}

	if (m_Box.Y < 0)
	{
		m_Box.Y = 0 + 1;
	}

	if (m_Box.Y + m_Box.Height > GAME_ENGINE->GetGameHeight())
	{
		m_Box.Y = GAME_ENGINE->GetGameHeight() - m_Box.Height - 1;
	}

	return true;
}

bool Character::hasFired()
{
	return m_Controller->PrimaryFire();
}