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
	m_pProjectileManager = make_unique<ProjectileManager>();
	
	GameStruct::Box playerBox{ GAME_ENGINE->GetGameWidth() / 2 - 25, GAME_ENGINE->GetGameHeight() - 100 - 25, 50, 50};
	m_pPlayer = make_unique<Character>(playerBox, 1, 1, true, GameStruct::vector2{0, -1}, 1 );
	m_pQlearningCharacter = make_unique<QLearningCharacter>(playerBox, 1, 1, true, GameStruct::vector2{ 0, -1 }, 1);

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
	
	GAME_ENGINE->SetColor(RGB(100, 100, 100));
	GAME_ENGINE->FillRect(0, 0, GAME_ENGINE->GetGameWidth(), GAME_ENGINE->GetGameHeight());

	m_pPlayer->Draw();

	m_pEnemyManager->Render();

	m_pProjectileManager->Draw();

	m_pQlearningCharacter->Draw();

	//Drawing score
	GAME_ENGINE->SetColor(RGB(50, 50, 50));

	int ScoringWidth{ GAME_ENGINE->GetWidth() - GAME_ENGINE->GetGameWidth() };

	GAME_ENGINE->FillRect(GAME_ENGINE->GetGameWidth(), 250, ScoringWidth, 250);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring buffer = std::to_wstring(GAME_ENGINE->GetGameScore());
	GAME_ENGINE->DrawString(buffer, GAME_ENGINE->GetGameWidth() + ScoringWidth / 2, 250 + 125);
}

void Game::Tick()
{	
	// Insert non-paint code that needs to be executed each tick
	m_pProjectileManager->Tick();
	
	m_pQlearningCharacter->Tick(GAME_ENGINE->GetFrameDelay());	
		
	m_pPlayer->Tick(GAME_ENGINE->GetFrameDelay());
	m_pProjectileManager->Shoot(*m_pPlayer);
	m_pProjectileManager->HitCheck(*m_pPlayer);


	m_pEnemyManager->Tick();
	for (auto& enemy : m_pEnemyManager->GetEnemyVector())
	{
		if (enemy != nullptr)
		{
			m_pQlearningCharacter->GetInViewInfo(enemy->GetBox());

			m_pProjectileManager->Shoot(*enemy);
			m_pProjectileManager->HitCheck(*enemy);
		}
	}


	for (const Projectile* projectile : m_pProjectileManager->GetProjectiles())
	{
		m_pQlearningCharacter->GetInViewInfo(projectile);
	}
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action

}
