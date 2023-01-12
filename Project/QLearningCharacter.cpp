#include "QLearningCharacter.h"

QLearningCharacter::QLearningCharacter(GameStruct::Box box, float health, float speed, bool isPossessed, GameStruct::vector2 forwardVector, int ID)
	: Character(box, health, speed, isPossessed, forwardVector, ID)
	, m_SimulateFire{ false }
	, m_ViewRange{ 250 }
	, m_HasReceivedInfo{ false }
	, m_pQlearning{	 make_unique<Qlearning>() }
	, m_LifeTime{ 0 }
	, m_pShootDelay{ make_unique<Delay>(1000) }
	, m_EpisodeTime{ GameStruct::point{ 0, 0 } }
	, m_BulletOnePos{ GameStruct::point{ 0, 0 } }
	, m_BulletTwoPos{ GameStruct::point{ 0, 0 } }
	, m_BulletThreePos{ GameStruct::point{ 0, 0 } }
	, m_ClosestEnemy{ GameStruct::point{ 0, 0 } }
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

	//GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_BulletOnePos.X, m_BulletOnePos.Y);
	//GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_BulletTwoPos.X, m_BulletTwoPos.Y);
	//GAME_ENGINE->DrawLine(m_Box.GetCenter().X, m_Box.GetCenter().Y, m_BulletThreePos.X, m_BulletThreePos.Y);


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
		KeepInWorld();

		/*if (m_Box.X < 0)
		{
			m_IsDead = true;
		}

		if (m_Box.X + m_Box.Width > GAME_ENGINE->GetGameWidth())
		{
			m_IsDead = true;
		}*/

	}

	m_pQlearning->ReceiveInfo(m_BulletOnePos, m_BulletTwoPos, m_BulletThreePos, m_Box.GetCenter(), m_MaxEnemyCount, m_EnemyCount, m_ClosestEnemy, *m_pShootDelay, m_EpisodeTime);

	HandleMovement(GAME_ENGINE->GetFrameDelay());
	
	ResetInfo();


	return true;
}


bool QLearningCharacter::GetAllBullets(std::vector<Projectile*> enemyBullets)
{
	int bulletCounter{};
	for (const auto* projectile : enemyBullets)
	{
		if (projectile->containsIgnoreId(1) == true)
		{
			continue;
		}
		
		bulletCounter++;

		if (bulletCounter == 1)
		{
			m_BulletOnePos = projectile->GetBox().GetCenter();
		}
		else if (bulletCounter == 2)
		{
			m_BulletTwoPos = projectile->GetBox().GetCenter();
		}
		else if (bulletCounter == 3)
		{
			m_BulletThreePos = projectile->GetBox().GetCenter();
			return true;
		}
	}

	return true;
}


bool QLearningCharacter::GetInViewInfo(std::vector<BaseEnemy*> enemies)
{
	int distance{GAME_ENGINE->GetGameHeight()};
	m_EnemyCount = enemies.size();

	for (const auto& enemy : enemies)
	{
		int checkDistance{ m_Box.GetCenter().distance(enemy->GetBox().GetCenter()) };
		if (checkDistance < distance)
		{
			distance = checkDistance;
			m_ClosestEnemy = enemy->GetBox().GetCenter();
		}
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

	m_BulletOnePos		= GameStruct::point{ m_Box.GetCenter().X, 0 };
	m_BulletTwoPos		= GameStruct::point{ m_Box.GetCenter().X, 0 };
	m_BulletThreePos	= GameStruct::point{ m_Box.GetCenter().X, 0 };
	m_ClosestEnemy		= GameStruct::point{ m_Box.GetCenter().X, 0 };
	m_EnemyCount		= m_MaxEnemyCount;


	m_HasReceivedInfo = false;

	return true;
}

void QLearningCharacter::SetBaseNeuralNetwork(NeuralNetwork baseNeuralNetwork)
{
	m_pQlearning->SetNeuralNetworkWeights(baseNeuralNetwork.GetConnections());
}