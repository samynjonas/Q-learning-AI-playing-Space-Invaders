#include "inputController.h"

inputController::inputController()
{

}

inputController::~inputController()
{

}

float inputController::HorizontalMovement() const
{
	float value{ 0.f };

	if (GAME_ENGINE->IsKeyDown(_T('Q')) || GAME_ENGINE->IsKeyDown(_T('A')))
	{
		value = 1;
	}

	if (GAME_ENGINE->IsKeyDown(_T('D')))
	{
		value = -1;
	}

	return value;
}
float inputController::VerticalMovement() const
{
	float value{ 0.f };

	if (GAME_ENGINE->IsKeyDown(_T('Z')) || GAME_ENGINE->IsKeyDown(_T('W')))
	{
		value++;
	}

	if (GAME_ENGINE->IsKeyDown(_T('S')))
	{
		value--;
	}

	return value;
}

bool inputController::PrimaryFire()
{
	if (GAME_ENGINE->IsKeyDown(_T('E')))
	{
		if (m_IsPrimaryDown == false)
		{
			m_IsPrimaryDown = true;
			return true;
		}
	}
	else if (!GAME_ENGINE->IsKeyDown(_T('E')))
	{
		m_IsPrimaryDown = false;
	}
	return false;
}

GameStruct::vector2 inputController::GetMovement() const
{
	GameStruct::vector2 movementVector{  };

	movementVector.X = HorizontalMovement();
	//movementVector.Y = VerticalMovement();

	return movementVector;
}