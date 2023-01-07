#include "QLearningCharacter.h"

QLearningCharacter::QLearningCharacter(GameStruct::Box box, float health, float speed, bool isPossessed, GameStruct::vector2 forwardVector, int ID)
	: Character(box, health, speed, isPossessed, forwardVector, ID)
	, m_SimulateFire{ false }
	, m_ViewRange{ 1000 }
	, m_FrontProjectilePos{ 0.f, 0.f }
	, m_FrontProjectileDistance{ static_cast<float>(box.Y) }
	, m_LeftProjectileDistance{ static_cast<float>(box.X) }
	, m_RightProjectileDistance{ static_cast<float>(GAME_ENGINE->GetWidth() - box.X) }
	, m_HasReceivedInfo{ false }
	, m_pQlearning{ make_unique<Qlearning>() }
{

}

QLearningCharacter::~QLearningCharacter()
{

}

bool QLearningCharacter::MoveLeft()
{
	GameStruct::vector2 movementVector{ 1, 0 };

	movementVector *= m_Speed;
	movementVector *= GAME_ENGINE->GetFrameDelay();

	m_Box.X -= movementVector.X;
	m_Box.Y -= movementVector.Y;

	return true;
}
bool QLearningCharacter::MoveRight()
{
	GameStruct::vector2 movementVector{ -1, 0 };

	movementVector *= m_Speed;
	movementVector *= GAME_ENGINE->GetFrameDelay();

	m_Box.X -= movementVector.X;
	m_Box.Y -= movementVector.Y;

	return true;
}


bool QLearningCharacter::Draw() const
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


	GAME_ENGINE->SetColor(RGB(255, 10, 10));
	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_FrontProjectilePos.X, m_Box.GetCenter().Y - m_FrontProjectileDistance);

	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_Box.GetCenter().X - m_LeftProjectileDistance, m_Box.GetCenter().Y);
	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_Box.GetCenter().X + m_RightProjectileDistance, m_Box.GetCenter().Y);

	m_pQlearning->Render();

	return true;
}

bool QLearningCharacter::HandleMovement(float deltaTime)
{
	GameStruct::vector2 movementVector{ m_pQlearning->Output(), 0 };
	movementVector *= m_Speed;
	movementVector *= deltaTime;

	m_Box.X -= movementVector.X;
	m_Box.Y -= movementVector.Y;

	return true;
}


bool QLearningCharacter::Tick(float deltaTime)
{
	//Clear previous InviewInfo

	m_Controller->Tick();
	m_pQlearning->Tick();

	if (m_KeepInWorld)
	{
		KeepInWorld();
	}

	if (m_HasReceivedInfo)
	{
		m_pQlearning->ReceiveInfo(m_FrontProjectileDistance, m_LeftProjectileDistance, m_RightProjectileDistance, m_Box.X, m_FrontProjectilePos.X, m_IsEnemyInSight);
		
		HandleMovement(GAME_ENGINE->GetFrameDelay());
		
		ResetInfo();
	}


	return true;
}


bool QLearningCharacter::GetInViewInfo(const Projectile* projectile)
{
	if (projectile->GetActorType() == type::projectile)
	{
		if (projectile->GetBox().Y > m_Box.Y)
		{
			return false;
		}

		int distance = GetDistance(projectile->GetBox().GetCenter(), m_Box.GetCenter());

		if (projectile->GetBox().Y > m_Box.Y - m_Box.Height)
		{
			//Is on left or right
			if (projectile->GetBox().X < m_Box.X)
			{
				//On left				
				if (distance < m_LeftProjectileDistance)
				{
					m_LeftProjectileDistance = distance;
					m_HasReceivedInfo = true;
					return true;
				}
			}
			else if (projectile->GetBox().X > m_Box.X + m_Box.Width)
			{
				//On Right
				if (distance < m_RightProjectileDistance)
				{
					m_RightProjectileDistance = distance;
					m_HasReceivedInfo = true;
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else if (projectile->GetBox().X > m_Box.X && projectile->GetBox().X < m_Box.X + m_Box.Width)
		{
			if (distance < m_FrontProjectileDistance)
			{
				m_FrontProjectileDistance = distance;
				m_FrontProjectilePos = projectile->GetBox().GetCenter();
			}
			m_HasReceivedInfo = true;
			return true;
		}
	}
	return false;
}

bool QLearningCharacter::GetInViewInfo(GameStruct::Box enemyBox)
{
	int aiCenter{ m_Box.GetCenter().X };

	if (aiCenter > enemyBox.X && aiCenter < enemyBox.X + enemyBox.Width)
	{
		m_IsEnemyInSight = true;
		return true;
	}

	return false;
}


bool QLearningCharacter::Shoot()
{
	m_SimulateFire = true;

	return true;
}
bool QLearningCharacter::hasFired()
{
	if (m_SimulateFire == true)
	{
		m_SimulateFire = false;
		return true;
	}
	return false;
}

int QLearningCharacter::GetSquaredDistance(GameStruct::point p1, GameStruct::point p2) const
{
	int distance{};

	distance = ( powf((p2.X - p1.X), 2.f) + powf((p2.Y - p1.Y), 2.f) );

	return abs(distance);
}
int QLearningCharacter::GetDistance(GameStruct::point p1, GameStruct::point p2) const
{
	return sqrtf(GetSquaredDistance(p1, p2));
}

bool QLearningCharacter::ResetInfo()
{
	//m_FrontProjectilePos = GameStruct::point{ 0, 0 };
	m_IsEnemyInSight			= false;
	m_FrontProjectileDistance	= m_Box.Y;
	m_LeftProjectileDistance	= m_Box.X;
	m_RightProjectileDistance	= GAME_ENGINE->GetWidth() - m_Box.X;

	m_HasReceivedInfo = false;

	return true;
}