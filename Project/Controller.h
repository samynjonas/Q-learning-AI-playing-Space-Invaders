#pragma once
#include "GameStruct.h"
#include "Delay.h"



class Controller
{
public:
	Controller();
	virtual ~Controller();

	virtual GameStruct::vector2 GetMovement() const = 0; //Pure function

	bool Tick();

	int RandomDelay() const;

	virtual bool PrimaryFire() = 0;  //Pure function

protected:
	virtual float HorizontalMovement() const = 0;
	virtual float VerticalMovement() const = 0;

	unique_ptr<Delay> m_pDelay;

	const int BASESHOOTDELAY;
	const int SHOOTOFFSET;
};

