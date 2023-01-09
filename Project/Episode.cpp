#include "Episode.h"




Episode::Episode()
	: m_Score{ 0 }
	, m_LifeTime{ 0 }
{
	m_pProjectileManager = make_unique<ProjectileManager>();
	m_pEnemyManager = make_unique<EnemyManager>();
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

	m_QlearningCharacter->Tick(GAME_ENGINE->GetFrameDelay());

	m_pProjectileManager->Shoot(*m_QlearningCharacter);
	m_pProjectileManager->HitCheck(*m_QlearningCharacter);


	for (const Projectile* projectile : m_pProjectileManager->GetProjectiles())
	{
		m_QlearningCharacter->GetInViewInfo(projectile);
	}
	
	m_pEnemyManager->Tick();
	for (auto& enemy : m_pEnemyManager->GetEnemyVector())
	{
		if (enemy != nullptr)
		{
			m_pProjectileManager->Shoot(*enemy);
			if (m_pProjectileManager->HitCheck(*enemy))
			{
				m_Score += enemy->GetScoring();
			}

			m_QlearningCharacter->GetInViewInfo(enemy->GetBox());
		}
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

	return false;
}

int Episode::GetScore() const
{
	return m_Score;
}

NeuralNetwork Episode::GetNeuralNetwork() const
{
	return m_QlearningCharacter->GetNeuralNetwork();
}