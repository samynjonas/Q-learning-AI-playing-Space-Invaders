//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v7_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

//-----------------------------------------------------------------
// Game methods																				
//-----------------------------------------------------------------

Game::Game()
{
	// nothing to create
}

Game::~Game()
{
	// nothing to destroy
}


void Game::Initialize(HINSTANCE hInstance)
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("GALAGA AI"));
	GAME_ENGINE->RunGameLoop(true);		
	
	// Set the optional values
	GAME_ENGINE->SetWidth(1280);
	GAME_ENGINE->SetHeight(1044);
    GAME_ENGINE->SetFrameRate(144);

	GAME_ENGINE->SetGameWidth(960);
	GAME_ENGINE->SetGameHeight(1044);

	//Custom variables
	m_LifeTime = 0;
	m_AllTimeHighestLifetime = 0;
	m_Episode = 0;

	m_pProjectileManager = make_unique<ProjectileManager>();
	
	GameStruct::Box playerBox{ 0, GAME_ENGINE->GetGameHeight() - 100 - 25, 50, 50 };
	const int xOffset{ GAME_ENGINE->GetGameWidth() / (static_cast<int>(CHARACTER_AMOUNT) + 1) };
	
	for (int index = 0; index < CHARACTER_AMOUNT; index++)
	{
		m_VecQLearningCharacters.push_back(make_unique<QLearningCharacter>(GameStruct::Box{ (index + 1) * xOffset, playerBox.Y, playerBox.Width, playerBox.Height }, 1, 1, true, GameStruct::vector2{ 0, -1 }, 1));
	}


	m_pEnemyManager = make_unique<EnemyManager>();	

	// Set the keys that the project needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (TCHAR) VK_LEFT;
	//buffer << (TCHAR) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void Game::Start()
{
	// Insert the code that needs to be executed at the start of the project

	m_BtnAmountShower = make_unique<Button>(_T("Change Amount"));
	m_BtnAmountShower->SetBounds(GAME_ENGINE->GetGameWidth(), 650, 125, 50);
	m_BtnAmountShower->AddActionListener(this);
	m_BtnAmountShower->Show();

	m_BtnGameSpeed = make_unique<Button>(_T("Speed"));
	m_BtnGameSpeed->SetBounds(GAME_ENGINE->GetGameWidth() + 150, 650, 125, 50);
	m_BtnGameSpeed->AddActionListener(this);
	m_BtnGameSpeed->Show();

}

void Game::End()
{
	// Insert the code that needs to be executed at the closing of the project
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the project registers a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{	
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the project registers a mouse wheel action
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the mouse pointer moves across the project window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox(_T("Da mouse wuz here."));
		}
	}
	*/
}

void Game::CheckKeyboard()
{	
	// Here you can check if a key of choice is held down
	// Is executed once per frame if the Project Loop is running 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void Game::KeyPressed(TCHAR cKey)
{	
	// DO NOT FORGET to use SetKeyList() !!

	// Insert the code that needs to be executed when a key of choice is pressed
	// Is executed as soon as the key is released
	// You first need to specify the keys that the research engine needs to watch by using the SetKeyList() method

	//Example:
	/*switch (cKey)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox(_T("Moving left."));
		break;
	}*/
}

void Game::Paint(RECT rect)
{
	// Insert paint code
	GAME_ENGINE->DrawSolidBackground(RGB( 191, 191, 191 ));
	
	GAME_ENGINE->SetColor(RGB(100, 100, 100));
	GAME_ENGINE->FillRect(0, 0, GAME_ENGINE->GetGameWidth(), GAME_ENGINE->GetGameHeight());

	m_pEnemyManager->Render();
	m_pProjectileManager->Draw();


	bool hasChosenOne{ false };
	for (int index{ 0 }; index < m_VecQLearningCharacters.size(); index++)
	{
		if (index < m_DrawAmount)
		{
			m_VecQLearningCharacters[index]->Draw();

			if (m_VecQLearningCharacters[index]->IsDead() == false && hasChosenOne == false)
			{
				hasChosenOne = true;
				m_VecQLearningCharacters[index]->DrawNeuralNetwork();
			}
		}
	}
	
	if (hasChosenOne == false)
	{
		m_VecQLearningCharacters[0]->DrawNeuralNetwork();
	}



	//Drawing score
	GAME_ENGINE->SetColor(RGB(50, 50, 50));
	int boxWidth{ GAME_ENGINE->GetWidth() - GAME_ENGINE->GetGameWidth() };
	GAME_ENGINE->FillRect(GAME_ENGINE->GetGameWidth(), 250, boxWidth, GAME_ENGINE->GetGameHeight() );


	int textOffset{ 25 };
	int textPos{ 250 };
	int CategoryYOffse{ 75 };
	
	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring scoreBuffer = std::to_wstring(GAME_ENGINE->GetGameScore());
	GAME_ENGINE->DrawString(_T("Score:"), GAME_ENGINE->GetGameWidth() + textOffset, textPos);
	GAME_ENGINE->DrawString(scoreBuffer,  GAME_ENGINE->GetGameWidth() + textOffset, textPos + textOffset);

	if (AreAllQlearningDead() == true)
	{
		GAME_ENGINE->SetColor(RGB(200, 0, 0));
	}
	else
	{
		GAME_ENGINE->SetColor(RGB(0, 0, 0));
	}


	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring lifeTimeBuffer = std::to_wstring(static_cast<int>(m_LifeTime / 1000));
	GAME_ENGINE->DrawString(_T("Lifetime"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse);
	GAME_ENGINE->DrawString(lifeTimeBuffer, GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring allTimeHighestLifeTimeBuffer = std::to_wstring(static_cast<int>(m_AllTimeHighestLifetime / 1000));
	GAME_ENGINE->DrawString(_T("All time highest lifeTime"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 2);
	GAME_ENGINE->DrawString(allTimeHighestLifeTimeBuffer,	 GAME_ENGINE->GetGameWidth() + textOffset,	 textPos + CategoryYOffse * 2 + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring episodeBuffer = std::to_wstring(m_Episode);
	GAME_ENGINE->DrawString(_T("Episode:"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 3);
	GAME_ENGINE->DrawString(episodeBuffer,  GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 3 + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring drawingAmountBuffer = std::to_wstring(m_DrawAmount);
	GAME_ENGINE->DrawString(_T("Drawing :"),		GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4);
	GAME_ENGINE->DrawString(drawingAmountBuffer,	GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4 + textOffset);
}

void Game::Tick()
{	
	// Insert non-paint code that needs to be executed each tick
	m_pProjectileManager->Tick();


	for (auto& qlearnigCharacters : m_VecQLearningCharacters)
	{
		if (qlearnigCharacters->IsDead() == false)
		{
			qlearnigCharacters->Tick(GAME_ENGINE->GetFrameDelay());
			m_pProjectileManager->Shoot(*qlearnigCharacters);
			m_pProjectileManager->HitCheck(*qlearnigCharacters);

			for (const Projectile* projectile : m_pProjectileManager->GetProjectiles())
			{
				qlearnigCharacters->GetInViewInfo(projectile);
			}


			for (auto& enemy : m_pEnemyManager->GetEnemyVector())
			{
				if (enemy != nullptr)
				{
					qlearnigCharacters->GetInViewInfo(enemy->GetBox());
				}
			}

		}
	}

	if (AreAllQlearningDead() == false)
	{
		m_LifeTime += GAME_ENGINE->GetFrameDelay();
	}
	else
	{
		LoadNextEpisode();
	}

	m_pEnemyManager->Tick();
	for (auto& enemy : m_pEnemyManager->GetEnemyVector())
	{
		if (enemy != nullptr)
		{
			m_pProjectileManager->Shoot(*enemy);
			m_pProjectileManager->HitCheck(*enemy);
		}
	}	
}

bool Game::AreAllQlearningDead() const
{
	for (const auto& qlearnigCharacters : m_VecQLearningCharacters)
	{
		if (qlearnigCharacters->IsDead() == false)
		{
			return false;
		}
	}

	return true;
}

void Game::LoadNextEpisode()
{
	++m_Episode;
	
	if (m_LifeTime > m_AllTimeHighestLifetime)
	{
		m_AllTimeHighestLifetime = m_LifeTime;
	}
	
	m_LifeTime = 0;

	std::vector<int> vecLifeTimes;
	std::map<int, int> mapLifeTimeCharacterIndex;

	int highestLifeTime{ 0 };
	int secondHighest{ 0 };

	for (int index = 0; index < m_VecQLearningCharacters.size(); index++)
	{
		vecLifeTimes.push_back(m_VecQLearningCharacters[index]->GetLifeTime());
		mapLifeTimeCharacterIndex[m_VecQLearningCharacters[index]->GetLifeTime()] = index;
	}

	std::sort(vecLifeTimes.begin(), vecLifeTimes.end(), std::greater<int>());

	NeuralNetwork highest{ m_VecQLearningCharacters[mapLifeTimeCharacterIndex[vecLifeTimes[0]]]->GetNeuralNetwork() };
	NeuralNetwork second{  m_VecQLearningCharacters[mapLifeTimeCharacterIndex[vecLifeTimes[1]]]->GetNeuralNetwork() };

	NeuralNetwork newNeural{ highest.MergeAndMutate(second) };

	m_VecQLearningCharacters.clear();


	GameStruct::Box playerBox{ 0, GAME_ENGINE->GetGameHeight() - 100 - 25, 50, 50 };
	const int xOffset{ GAME_ENGINE->GetGameWidth() / (static_cast<int>(CHARACTER_AMOUNT) + 1) };

	for (int index = 0; index < CHARACTER_AMOUNT; index++)
	{
		m_VecQLearningCharacters.push_back(make_unique<QLearningCharacter>(GameStruct::Box{ (index + 1) * xOffset, playerBox.Y, playerBox.Width, playerBox.Height }, 1, 1, true, GameStruct::vector2{ 0, -1 }, 1));
	}

	for (auto& qlearnigCharacters : m_VecQLearningCharacters)
	{
		qlearnigCharacters->SetBaseNeuralNetwork(newNeural);
	}
}

void Game::CallAction(Caller* callerPtr)
{
	if (callerPtr == m_BtnAmountShower.get())
	{
		if (m_DrawAmount == 1)
		{
			m_DrawAmount = 10;
		}
		else if (m_DrawAmount == 10)
		{
			m_DrawAmount = 25;
		}
		else if (m_DrawAmount == 25)
		{
			m_DrawAmount = 50;
		}
		else if (m_DrawAmount == 50)
		{
			m_DrawAmount = 75;
		}
		else if (m_DrawAmount == 75)
		{
			m_DrawAmount = CHARACTER_AMOUNT;
		}
		else if (m_DrawAmount == CHARACTER_AMOUNT)
		{
			m_DrawAmount = 1;
		}
		else
		{
			m_DrawAmount = 1;
		}
	}

	static int currentSpeed{ GAME_ENGINE->GetGameSpeed() };
	if (callerPtr == m_BtnGameSpeed.get())
	{
		GAME_ENGINE->SetGameSpeed( GAME_ENGINE->GetGameSpeed() + 1.f );
	}

}
