#include "ProjectileManager.h"


ProjectileManager::ProjectileManager()
{

}

ProjectileManager::~ProjectileManager()
{

}

bool ProjectileManager::Tick()
{
	//TODO make more effecient if needed(runs 2x through vector), probably not
	for (auto& projectile : m_pProjectiles)
	{
		projectile->Tick(GAME_ENGINE->GetFrameDelay());
	}

	CheckProjectileLife();

	return true;
}

bool ProjectileManager::Draw() const
{
	for (const auto& projectile : m_pProjectiles)
	{
		projectile->Draw();
	}
	return true;
}

bool ProjectileManager::CheckProjectileLife()
{
	for (size_t index = 0; index < m_pProjectiles.size(); index++)
	{
		if (m_pProjectiles[index]->GetPoint().Y > GAME_ENGINE->GetHeight() || m_pProjectiles[index]->GetPoint().Y < 0 || m_pProjectiles[index]->GetHealth() <= 0.f)
		{
			delete m_pProjectiles[index];

			m_pProjectiles[index] = m_pProjectiles.back();
			m_pProjectiles.pop_back();
		}
	}

	return true;
}

bool ProjectileManager::Shoot(Character& character)
{
	if (character.hasFired())
	{
		m_pProjectiles.push_back(new Projectile(GameStruct::Box{ character.GetPoint().X + character.GetBox().Width / 2, character.GetPoint().Y, 5, 5 }, 3, character.GetForwardVector()));
		m_pProjectiles.back()->AddIgnoreID(character.GetID());

		return true;
	}

	return false;
}

bool ProjectileManager::Shoot(BaseEnemy& Enemy)
{
	if (Enemy.hasFired())
	{
		if (InGameBulletsWithId(Enemy.GetID()) < MAXENEMYBULLETS)
		{
			m_pProjectiles.push_back(new Projectile(GameStruct::Box{ Enemy.GetPoint().X + Enemy.GetBox().Width / 2, Enemy.GetPoint().Y, 5, 5 }, 1, Enemy.GetForwardVector()));
			m_pProjectiles.back()->AddIgnoreID(Enemy.GetID());
		}
		return true;
	}

	return false;
}

bool ProjectileManager::HitCheck(Actor& actor)
{
	for (auto& projectile : m_pProjectiles)
	{
		if (projectile->containsIgnoreId(actor.GetID()))
		{
			continue;
		}

		if (projectile->GetPoint().X > actor.GetPoint().X + actor.GetBox().Width)
		{
			continue;
		}

		if (projectile->GetPoint().X + projectile->GetBox().Width < actor.GetPoint().X)
		{
			continue;
		}

		if (projectile->GetPoint().Y < actor.GetPoint().Y - actor.GetBox().Height)
		{
			continue;
		}

		if (projectile->GetPoint().Y - projectile->GetBox().Height > actor.GetPoint().Y)
		{
			continue;
		}
		actor.DealDamage( 1.f );
		
		projectile->DealDamage(100.f);

		if (actor.IsDead())
		{
			GAME_ENGINE->AddToGameScore(actor.GetScoring());
		}

		return true;
	}
	return false;
}

int ProjectileManager::InGameBulletsWithId(int id) const
{
	int amount{ 0 };

	for (const auto& projectile : m_pProjectiles)
	{
		if (projectile->containsIgnoreId(id))
		{
			amount++;
		}
	}

	return amount;
}
