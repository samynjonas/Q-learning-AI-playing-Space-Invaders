#pragma once
#include "Actor.h"

class Projectile final : public Actor
{
public:
	Projectile(GameStruct::Box box, float speed, GameStruct::vector2 direction);
	~Projectile();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	Projectile(const Projectile& other) = delete;
	Projectile(Projectile&& other) noexcept = delete;
	Projectile& operator=(const Projectile& other) = delete;
	Projectile& operator=(Projectile&& other)	noexcept = delete;

	bool Draw() const;
	bool Tick(float deltaTime);

	bool AddIgnoreID(int ID);

	bool containsIgnoreId(int ID) const;

private:
	// -------------------------
	// Functions
	// -------------------------


	// -------------------------
	// Variables
	// -------------------------
	float m_Speed;
	GameStruct::vector2 m_Direction;

	std::vector<int> m_IgnoreID{};

};

