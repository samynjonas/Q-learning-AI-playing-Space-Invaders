#pragma once
#include "Controller.h"
#include "GameEngine.h"

class inputController final: public Controller
{
public:
	inputController();
	~inputController();

	GameStruct::vector2 GetMovement() const override;
	
	bool PrimaryFire() override;

private:
	float HorizontalMovement() const override;
	float VerticalMovement() const override;

	bool m_IsPrimaryDown{ false };

};

