#include "EnemyManager.h"

EnemyManager::EnemyManager()
	: m_EnemyCount{ 0 }
	, m_RowAmount{ 5 }
	, m_CollumAmount{ 11 }
	, m_SpawnBox{ GameStruct::Box{ 0, 300, 1000, 250} }
	, m_EnemyBox{ GameStruct::Box{ 0, 0, 50, 30} }
{
	const int xOffset{ m_SpawnBox.Width / (static_cast<int>(m_CollumAmount) + 1) };
	const int yOffset{ m_SpawnBox.Height / (static_cast<int>(m_RowAmount) + 1) };

	for (int rowIndex = 0; rowIndex < m_RowAmount; rowIndex++)
	{
		for (int colIndex = 0; colIndex < m_CollumAmount; colIndex++)
		{
			m_VecEnemies.push_back(make_unique<BaseEnemy>(GameStruct::Box{ m_SpawnBox.X + xOffset * (colIndex + 1) - m_EnemyBox.Width / 2, m_SpawnBox.Y + yOffset * (rowIndex + 1) - m_EnemyBox.Height / 2, m_EnemyBox.Width, m_EnemyBox.Height }, GameStruct::vector2{ 0, 1 }));
		}
	}
}

EnemyManager::~EnemyManager()
{

}


void EnemyManager::Tick()
{
	static int moving{ 1 };

	if (moving > 0)
	{
		//moving right
		if (m_SpawnBox.X + m_SpawnBox.Width - m_EnemyBox.Width >= GAME_ENGINE->GetGameWidth())
		{
			moving = -1;
		}
	}
	else if (moving < 0)
	{
		//moving left
		if (m_SpawnBox.X + m_EnemyBox.Width < 0)
		{
			moving = 1;
		}
	}


	m_SpawnBox.X += moving;

	for (auto& enemy : m_VecEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Tick(GAME_ENGINE->GetFrameDelay());

			enemy->Move(moving, 0);

			if (enemy->IsDead())
			{
				//Release ptr
				enemy.release();
			}

		}
	}

	ReleaseNullptr();
}

void EnemyManager::Render() const
{
	for (const auto& enemy : m_VecEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Draw();

		}
	}
}

std::vector<unique_ptr<BaseEnemy>>& EnemyManager::GetEnemyVector()
{
	return m_VecEnemies;
}

bool EnemyManager::ReleaseNullptr()
{
	for (size_t index = 0; index < m_VecEnemies.size(); index++)
	{
		if (m_VecEnemies[index] == nullptr)
		{
			m_VecEnemies.erase(m_VecEnemies.begin() + index);
		}
	}

	return true;
}
