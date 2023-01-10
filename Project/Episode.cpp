#include "Episode.h"




Episode::Episode()
	: m_Score{ 0 }
	, m_LifeTime{ 0 }
	, m_MaxLifeTime{ 3000 }
{
	m_pEnemyManager = make_unique<EnemyManager>();
	m_pProjectileManager = make_unique<ProjectileManager>();

	GameStruct::Box characterBox{ 0, GAME_ENGINE->GetGameHeight() - 100 - 25, 50, 50 };
	m_QlearningCharacter = make_unique<QLearningCharacter>( GameStruct::Box{ GAME_ENGINE->GetGameWidth() / 2 - characterBox.Width / 2, characterBox.Y, characterBox.Width, characterBox.Height }, 1, 1, true, GameStruct::vector2{0, -1}, 1);
}


Episode::~Episode()
{

}

void Episode::Render(bool renderNeuralNetwork) const
{
	//EUHM sometimes render, sometines draw hihi I DONT MAKE THE RULES

	m_pEnemyManager->Render();

	m_pProjectileManager->Draw();
	m_QlearningCharacter->Draw();

	if (renderNeuralNetwork)
	{
		m_QlearningCharacter->DrawNeuralNetwork();
	}
}

void Episode::Tick()
{	
	m_pProjectileManager->Tick();

	m_LifeTime += GAME_ENGINE->GetFrameDelay();
	m_QlearningCharacter->GetEpisodeTime(GameStruct::point{ m_LifeTime, m_MaxLifeTime });
	m_QlearningCharacter->Tick(GAME_ENGINE->GetFrameDelay());

	if (m_pProjectileManager->Shoot(*m_QlearningCharacter) == true)
	{
		m_Score += 1;
	}

	m_pProjectileManager->HitCheck(*m_QlearningCharacter);


	m_QlearningCharacter->GetAllBullets(m_pProjectileManager->GetProjectiles());
	
	m_pEnemyManager->Tick();
	for (auto& enemy : m_pEnemyManager->GetEnemyVector())
	{
		if (enemy != nullptr)
		{
			m_pProjectileManager->Shoot(*enemy);
			if (m_pProjectileManager->HitCheck(*enemy))
			{
				m_Score += enemy->GetScoring();

				m_MaxLifeTime += 1500;
			}

			m_QlearningCharacter->GetInViewInfo(enemy->GetBox());
		}
	}

	if (m_pEnemyManager->GetEnemyVector().empty())
	{
		m_Score += 50;
	}

}


bool Episode::IsFinished() const
{
	if (m_QlearningCharacter->IsDead())
	{
		return true;
	}

	if (m_pEnemyManager->GetEnemyVector().empty())
	{
		return true;
	}

	if (m_LifeTime >= m_MaxLifeTime)
	{
		return true;
	}

	return false;
}

int Episode::GetScore() const
{
	return m_Score + (m_LifeTime / 1000);
}

NeuralNetwork Episode::GetNeuralNetwork() const
{
	return m_QlearningCharacter->GetNeuralNetwork();
}

void Episode::SetStartNeuralNetwork(NeuralNetwork baseNeuralNetwork)
{
	m_QlearningCharacter->SetBaseNeuralNetwork(baseNeuralNetwork);
}