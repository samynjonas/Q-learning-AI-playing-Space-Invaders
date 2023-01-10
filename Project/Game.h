//-----------------------------------------------------------------
// Main Game  File
// C++ Header - Game.h - version v7_01					
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Character.h"
#include "ProjectileManager.h"
#include "Projectile.h"

#include "EnemyManager.h"

#include "QLearningCharacter.h"

#include "Episode.h"

#include <map>
#include <algorithm>

#include "FileWriter.h"



//-----------------------------------------------------------------
// Game Class																
//-----------------------------------------------------------------
class Game : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Game();

	virtual ~Game();

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Game(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) noexcept = delete;

	//---------------------------
	// General Methods
	//---------------------------
	void Initialize(HINSTANCE hInstance) override;
	void Start() override;
	void End() override;
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	void MouseMove(int x, int y, WPARAM wParam) override;
	void CheckKeyboard() override;
	void KeyPressed(TCHAR cKey) override;
	void Paint(RECT rect) override;
	void Tick() override;

	void CallAction(Caller* callerPtr) override;

private:
	// -------------------------
	// Datamembers
	// -------------------------
	int m_RunTime{};
	int m_Score{};
	int m_Highscore{};
	int m_Episode{};


	bool AreAllQlearningDead() const;
	void LoadNextEpisode();

	void RenderText() const;


	const int BATCH_AMOUNT{ 500 };
	std::vector<unique_ptr<Episode>> m_VecBatches;

	unique_ptr<FileWriter> m_pFileWriter;

};
