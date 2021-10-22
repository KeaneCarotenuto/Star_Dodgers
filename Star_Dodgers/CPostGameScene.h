#pragma once
#include "CSceneBase.h"
class CPostGameScene :
    public CSceneBase
{
public:
	CPostGameScene();
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

