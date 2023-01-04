#pragma once
#include "Controller.h"

class AIcontroller final : public Controller
{
public:
	AIcontroller();
	~AIcontroller();

	GameStruct::vector2 GetMovement() const override;

	bool PrimaryFire() override;

private:
	float HorizontalMovement() const override;
	float VerticalMovement() const override;
};

