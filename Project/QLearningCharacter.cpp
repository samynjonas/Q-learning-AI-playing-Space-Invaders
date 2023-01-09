#include "QLearningCharacter.h"

QLearningCharacter::QLearningCharacter(GameStruct::Box box, float health, float speed, bool isPossessed, GameStruct::vector2 forwardVector, int ID)
	: Character(box, health, speed, isPossessed, forwardVector, ID)
	, m_SimulateFire{ false }
	, m_ViewRange{ 250 }
	, m_FrontProjectilePos{ 0.f, 0.f }
	, m_FrontProjectileDistance{ static_cast<float>(box.Y) }
	, m_LeftProjectileDistance{ static_cast<float>(box.X) }
	, m_RightProjectileDistance{ static_cast<float>(GAME_ENGINE->GetWidth() - box.X) }
	, m_HasReceivedInfo{ false }
	, m_pQlearning{	 make_unique<Qlearning>() }
	, m_LifeTime{ 0 }
	, m_pShootDelay{ make_unique<Delay>(1000) }
	, m_EpisodeTime{ GameStruct::point{0, 0}}
{
	ResetInfo();
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
	return true;
}

bool QLearningCharacter::DrawNeuralNetwork() const
{
	m_pQlearning->Render();

	GAME_ENGINE->SetColor(RGB(255, 10, 10));
	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_FrontProjectilePos.X, m_Box.GetCenter().Y - m_FrontProjectileDistance);

	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_Box.GetCenter().X - m_LeftProjectileDistance, m_Box.GetCenter().Y);
	GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_Box.GetCenter().X + m_RightProjectileDistance, m_Box.GetCenter().Y);

	return true;
}

bool QLearningCharacter::HandleMovement(float deltaTime)
{
	GameStruct::vector2 movementVector{ 0, 0 };

	if (m_pQlearning->Output() == 0)
	{
		//move left
		movementVector.X = -1;
	}
	else if (m_pQlearning->Output() == 1)
	{
		//move right
		movementVector.X = 1;
	}

	movementVector *= m_Speed;
	movementVector *= deltaTime;

	m_Box.X -= movementVector.X;

	return true;
}


bool QLearningCharacter::Tick(float deltaTime)
{
	//Clear previous InviewInfo
	m_LifeTime += deltaTime;

	m_pShootDelay->Tick();
	m_pQlearning->Tick();

	if (m_KeepInWorld)
	{
		//KeepInWorld();

		if (m_Box.X < 0)
		{
			m_IsDead = true;
		}

		if (m_Box.X + m_Box.Width > GAME_ENGINE->GetGameWidth())
		{
			m_IsDead = true;
		}

	}

	m_pQlearning->ReceiveInfo(m_FrontProjectileDistance, m_LeftProjectileDistance, m_RightProjectileDistance, m_Box.X, m_FrontProjectilePos.X, m_IsEnemyInSight, *m_pShootDelay, m_EpisodeTime);
	
	HandleMovement(GAME_ENGINE->GetFrameDelay());
	
	ResetInfo();


	return true;
}





bool QLearningCharacter::GetInViewInfo(const Projectile* projectile)
{
	if (projectile->containsIgnoreId(1) == true)
	{
		return false;
	}

	if (projectile->GetActorType() == type::projectile) //if projectile is of type projectile
	{
		if (projectile->GetBox().Y > m_Box.Y) // if the projectile has already passed the character
		{
			return true;
		}

		int distance = GetDistance(projectile->GetBox().GetCenter(), m_Box.GetCenter()); // Get the distance from the projectile to the character

		if (projectile->GetBox().Y > m_Box.Y - m_Box.Height) //If the projectile is on the player level
		{
			//Is on left or right
			if (projectile->GetBox().X < m_Box.X) //If the x is smaller then the character x == is on the left
			{
				//On left				
				if (distance < m_LeftProjectileDistance)
				{
					m_LeftProjectileDistance = distance;
					m_HasReceivedInfo = true;
					return true;
				}
			}
			else if (projectile->GetBox().X > m_Box.X + m_Box.Width) //Else if the x is bigger then the character x == is on the right
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
				return true;
			}
		}
		else if (projectile->GetBox().X > m_Box.X - 10 && projectile->GetBox().X < m_Box.X + m_Box.Width + 10) //certain X box == is above
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
	return true;
}
bool QLearningCharacter::GetInViewInfo(GameStruct::Box enemyBox)
{
	int aiCenter{ m_Box.GetCenter().X };

	if (aiCenter > enemyBox.X && aiCenter < enemyBox.X + enemyBox.Width)
	{
		m_IsEnemyInSight = true;
		return true;
	}

	return true;
}


bool QLearningCharacter::Shoot()
{
	m_SimulateFire = true;

	return true;
}
bool QLearningCharacter::hasFired()
{
	if (m_pQlearning->Output() == 2 && m_pShootDelay->IsDone())
	{
		m_pShootDelay->Reset();
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
	int halfGameWidht{ GAME_ENGINE->GetGameWidth() / 2 };

	m_FrontProjectilePos = GameStruct::point{ m_Box.GetCenter().X, 0};
	m_IsEnemyInSight			= false;
	m_FrontProjectileDistance	= m_Box.Y;

	m_LeftProjectileDistance	= m_Box.X + m_Box.Width;
	m_RightProjectileDistance	= GAME_ENGINE->GetGameWidth() - m_Box.X + m_Box.Width;

	m_HasReceivedInfo = false;

	return true;
}

void QLearningCharacter::SetBaseNeuralNetwork(NeuralNetwork baseNeuralNetwork)
{
	m_pQlearning->SetNeuralNetworkWeights(baseNeuralNetwork.GetConnections());
}