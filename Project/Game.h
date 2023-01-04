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
#include "QLearningCharacter.h"
#include "Projectile.h"

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
	bool ReleaseNullptr();


	// -------------------------
	// Datamembers
	// -------------------------
	unique_ptr<Character> m_pPlayer;
	unique_ptr<QLearningCharacter> m_pQlearningCharacter;


	std::vector<unique_ptr<Character>> m_pEnemies;

	unique_ptr<ProjectileManager> m_pProjectileManager;
};
