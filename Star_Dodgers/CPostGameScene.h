#pragma once
#include "CSceneBase.h"
#include "CTeamsManager.h"
class CPostGameScene :
    public CSceneBase
{
public:
	
	CPostGameScene(Team _winningTeam = Team::UNDECIDED, int _bluePoints = 0, int _redPoints = 0);
	~CPostGameScene();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

private:
	sf::Text* m_gameWinner;
	sf::Text* m_gameSummary;
	sf::Text* m_menuButton;
	sf::Text* m_playAgainButton;

	enum class OptionSelected
	{
		MainMenu,
		PlayAgain
	};
};

