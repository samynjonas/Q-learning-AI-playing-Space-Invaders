#pragma once
#include "Projectile.h"
#include "Character.h"

class ProjectileManager final
{
public:
	ProjectileManager();
	~ProjectileManager();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) noexcept = delete;
	ProjectileManager& operator=(const ProjectileManager& other) = delete;
	ProjectileManager& operator=(ProjectileManager&& other)	noexcept = delete;

	bool Tick();
	bool Draw() const;

	bool Shoot(Character& character);
	bool HitCheck(Actor& actor);

	vector<Projectile*> GetProjectiles() const
	{
		return m_pProjectiles;
	}

private:
	bool CheckProjectileLife();


	vector<Projectile*> m_pProjectiles;


};

