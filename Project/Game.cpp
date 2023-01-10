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
	m_Highscore = 0;
	m_Episode = 0;


	for (size_t index = 0; index < BATCH_AMOUNT; index++)
	{
		m_VecBatches.push_back(make_unique<Episode>());
	}

	m_pFileWriter = make_unique<FileWriter>("..\\NeuralNetwork");

}

void Game::Start()
{
	// Insert the code that needs to be executed at the start of the project

	/*m_BtnGameSpeed = make_unique<Button>(_T("Speed"));
	m_BtnGameSpeed->SetBounds(GAME_ENGINE->GetGameWidth() + 150, 650, 125, 50);
	m_BtnGameSpeed->AddActionListener(this);
	m_BtnGameSpeed->Show();*/

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


	for (const auto& batch : m_VecBatches)
	{
		if (batch->IsFinished() == false)
		{
			batch->Render(true);
			break;
		}
	}

	RenderText();
}

void Game::RenderText() const
{
	//Drawing text
	GAME_ENGINE->SetColor(RGB(50, 50, 50));
	int boxWidth{ GAME_ENGINE->GetWidth() - GAME_ENGINE->GetGameWidth() };

	int textOffset{ 25 };
	int textPos{ 500 };
	int CategoryYOffse{ 75 };

	GAME_ENGINE->FillRect(GAME_ENGINE->GetGameWidth(), textPos, boxWidth, GAME_ENGINE->GetGameHeight());

	int currentScore{};
	int activeBatch{};

	for (int index{0}; index < m_VecBatches.size(); ++index)
	{
		if (m_VecBatches[index]->IsFinished() == false)
		{
			currentScore = m_VecBatches[index]->GetScore();
			activeBatch = index;
			break;
		}

	}

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring batchBuffer = std::to_wstring(activeBatch);
	GAME_ENGINE->DrawString(_T("Active batch:"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 0);
	GAME_ENGINE->DrawString(batchBuffer,		 GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 0 + textOffset);

	wstring scoreBuffer = std::to_wstring(currentScore);
	GAME_ENGINE->DrawString(_T("Score"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 1);
	GAME_ENGINE->DrawString(scoreBuffer, GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 1 + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring allTimeHighestLifeTimeBuffer = std::to_wstring(static_cast<int>(m_Highscore));
	GAME_ENGINE->DrawString(_T("Highscore"),			  GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 2);
	GAME_ENGINE->DrawString(allTimeHighestLifeTimeBuffer, GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 2 + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring episodeBuffer = std::to_wstring(m_Episode);
	GAME_ENGINE->DrawString(_T("Episode:"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 3);
	GAME_ENGINE->DrawString(episodeBuffer,  GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 3 + textOffset);

	GAME_ENGINE->SetColor(RGB(0, 0, 0));
	wstring timeBuffer = std::to_wstring((m_RunTime / 1000));
	GAME_ENGINE->DrawString(_T("Game has been running for:"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4);
	GAME_ENGINE->DrawString(timeBuffer, GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4 + textOffset);

	//GAME_ENGINE->SetColor(RGB(0, 0, 0));
	//wstring drawingAmountBuffer = std::to_wstring(m_DrawAmount);
	//GAME_ENGINE->DrawString(_T("Drawing :"), GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4);
	//GAME_ENGINE->DrawString(drawingAmountBuffer, GAME_ENGINE->GetGameWidth() + textOffset, textPos + CategoryYOffse * 4 + textOffset);
}


void Game::Tick()
{
	m_RunTime += GAME_ENGINE->GetFrameDelay();

	for (const auto& batch : m_VecBatches)
	{
		if (batch->IsFinished())
		{
			continue; //batch already finished
		}
		batch->Tick();
	}


	if (AreAllQlearningDead() == true)
	{
		LoadNextEpisode();
	}
}

bool Game::AreAllQlearningDead() const
{
	for (const auto& batch : m_VecBatches)
	{
		if (batch->IsFinished() == false)
		{
			return false;
		}
	}

	return true;
}

void Game::LoadNextEpisode()
{
	++m_Episode;

	int episodeHighscore{};
	for (const auto& batch : m_VecBatches)
	{
		if (batch->GetScore() > episodeHighscore)
		{
			episodeHighscore = batch->GetScore();
		}
	}
	
	if (episodeHighscore > m_Highscore)
	{
		m_Highscore = m_Score;
	}
	
	m_Score = 0;

	std::vector<int> vecHighscores;
	std::map<int, int> mapScoreEpisodeIndex;

	for (int index = 0; index < m_VecBatches.size(); index++)
	{
		vecHighscores.push_back(m_VecBatches[index]->GetScore());
		mapScoreEpisodeIndex[m_VecBatches[index]->GetScore()] = index;
	}

	std::sort(vecHighscores.begin(), vecHighscores.end(), std::greater<int>());

	int highestScore{ m_VecBatches[mapScoreEpisodeIndex[vecHighscores[0]]]->GetScore() };
	if (highestScore > m_Highscore)
	{
		m_Highscore = highestScore;
	}

	NeuralNetwork highest{ m_VecBatches[mapScoreEpisodeIndex[vecHighscores[0]]]->GetNeuralNetwork() };
	NeuralNetwork second{ m_VecBatches[mapScoreEpisodeIndex[vecHighscores[1]]]->GetNeuralNetwork() };

	//NeuralNetwork newNeural{ highest.MergeAndMutate(second) };

	m_pFileWriter->Write(m_Episode, highest.GetConnections(), highestScore);

	m_VecBatches.clear();


	for (size_t index = 0; index < BATCH_AMOUNT; index++)
	{
		m_VecBatches.push_back(make_unique<Episode>());
	}

	for (auto& batch : m_VecBatches)
	{
		batch->SetStartNeuralNetwork(highest.MergeAndMutate(second));
	}
}

void Game::CallAction(Caller* callerPtr)
{
	/*static int currentSpeed{ GAME_ENGINE->GetGameSpeed() };
	if (callerPtr == m_BtnGameSpeed.get())
	{
		GAME_ENGINE->SetGameSpeed( GAME_ENGINE->GetGameSpeed() + 1.f );
	}*/

}
