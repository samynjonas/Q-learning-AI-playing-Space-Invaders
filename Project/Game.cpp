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
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);


	//Custom variables
	m_pProjectileManager = make_unique<ProjectileManager>();
	
	GameStruct::Box playerBox{ GAME_ENGINE->GetWidth() / 2, GAME_ENGINE->GetHeight() - 100, 50, 50};
	m_pPlayer = make_unique<Character>(playerBox, 1, 1, true, GameStruct::vector2{0, -1}, 1 );
	m_pQlearningCharacter = make_unique<QLearningCharacter>(playerBox, 1, 1, true, GameStruct::vector2{ 0, -1 }, 1);

	const size_t enemyAmount{ 10 };
	for (size_t index = 0; index < enemyAmount; index++)
	{
		m_pEnemies.push_back(make_unique<Character>(GameStruct::Box{ 10 + (100 * static_cast<int>(index)), 100, 50, 50}, 1, 1, false, GameStruct::vector2{0, 1}, 2));
	}


	

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

	/* Example:
	switch (cKey)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox(_T("Moving left."));
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox(_T("Moving down."));
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox(_T("Moving right."));
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox(_T("Moving up."));
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox(_T("Escape menu."));
	}
	*/
}

void Game::Paint(RECT rect)
{
	// Insert paint code
	GAME_ENGINE->DrawSolidBackground(RGB( 191, 191, 191 ));
	
	m_pPlayer->Draw();

	for (const auto& enemy : m_pEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Draw();
		}
	}

	m_pProjectileManager->Draw();


	m_pQlearningCharacter->Draw();

}

void Game::Tick()
{	
	// Insert non-paint code that needs to be executed each tick
	m_pProjectileManager->Tick();
	
	m_pQlearningCharacter->Tick(GAME_ENGINE->GetFrameDelay());
	
		
	m_pPlayer->Tick(GAME_ENGINE->GetFrameDelay());
	m_pProjectileManager->Shoot(*m_pPlayer);
	m_pProjectileManager->HitCheck(*m_pPlayer);

	for (auto& enemy : m_pEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Tick(GAME_ENGINE->GetFrameDelay());
	
			m_pQlearningCharacter->GetInViewInfo(enemy->GetBox());

			m_pProjectileManager->Shoot(*enemy);
			m_pProjectileManager->HitCheck(*enemy);

			if (enemy->IsDead())
			{
				enemy.release();
			}
		}
	}


	for (const Projectile* projectile : m_pProjectileManager->GetProjectiles())
	{
		m_pQlearningCharacter->GetInViewInfo(projectile);
	}

	ReleaseNullptr();
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action

}

bool Game::ReleaseNullptr()
{
	for (size_t index = 0; index < m_pEnemies.size(); index++)
	{
		if (m_pEnemies[index] == nullptr)
		{
			m_pEnemies.erase(m_pEnemies.begin() + index);
		}
	}

	return true;
}
