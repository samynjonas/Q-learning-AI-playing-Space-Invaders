#include "AIcontroller.h"

AIcontroller::AIcontroller()
{

}

AIcontroller::~AIcontroller()
{

}

GameStruct::vector2 AIcontroller::GetMovement() const
{
	GameStruct::vector2 movementVector{ };

	movementVector.X = HorizontalMovement();
	movementVector.Y = VerticalMovement();

	return movementVector;
}


bool AIcontroller::PrimaryFire()
{
	if (m_pDelay->IsDone())
	{
		m_pDelay->SetDelay(RandomDelay());

		m_pDelay->Reset();
		return true;
	}
	return false;
}

float AIcontroller::HorizontalMovement() const
{
	float value{  };

	return value;
}

float AIcontroller::VerticalMovement() const
{
	float value{  };

	return value;
}