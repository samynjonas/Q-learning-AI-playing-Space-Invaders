#pragma once
#include "Actor.h"

#include "Controller.h"
#include "Delay.h"

class BaseEnemy : public Actor
{
public:
	BaseEnemy(GameStruct::Box box, GameStruct::vector2 forwardVector);
	virtual ~BaseEnemy();

	BaseEnemy(const BaseEnemy& other) = delete;
	BaseEnemy(BaseEnemy&& other) noexcept = delete;
	BaseEnemy& operator=(const BaseEnemy& other) = delete;
	BaseEnemy& operator=(BaseEnemy&& other)	noexcept = delete;


	bool Draw() const override;
	virtual bool Tick(float deltaTime) override;
	
	void Move(float x, float y);

	virtual bool hasFired();

	GameStruct::vector2 GetForwardVector() const
	{
		return m_ForwardVector;
	}

private:

	// -------------------------
	//Variables-----------------
	// -------------------------
	const int SHOOTCHANCE{ 2048 };

	float m_Speed;

	GameStruct::vector2 m_ForwardVector;
};

//Medium enemy
class Crab final : public BaseEnemy
{
public:
	Crab(GameStruct::Box box, GameStruct::vector2 forwardVector);
	~Crab();

	Crab(const Crab& other) = delete;
	Crab(Crab&& other) noexcept = delete;
	Crab& operator=(const Crab& other) = delete;
	Crab& operator=(Crab&& other)	noexcept = delete;



private:



};

//Small enemy
class Squid final : public BaseEnemy
{
public:
	Squid(GameStruct::Box box, GameStruct::vector2 forwardVector);
	~Squid();

	Squid(const Squid& other) = delete;
	Squid(Squid&& other) noexcept = delete;
	Squid& operator=(const Squid& other) = delete;
	Squid& operator=(Squid&& other)	noexcept = delete;

private:


};

//Big enemy
class Octopus final : public BaseEnemy
{
public:
	Octopus(GameStruct::Box box, GameStruct::vector2 forwardVector);
	~Octopus();

	Octopus(const Octopus& other) = delete;
	Octopus(Octopus&& other) noexcept = delete;
	Octopus& operator=(const Octopus& other) = delete;
	Octopus& operator=(Octopus&& other)	noexcept = delete;

private:


};




