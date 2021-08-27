#include "CGameScene.h"

CGameScene::CGameScene(int _playerCount)
{
	Player = new sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	CGameManager::GetController(0)->Bind(dynamic_cast<IGamepadInput*>(this), "GameScene");
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update(float _fDeltaTime)
{
	CWindowUtilities::Draw(Player);
}

void CGameScene::FixedUpdate()
{
}

void CGameScene::LateUpdate(float _fDeltaTime)
{
}

void CGameScene::AddPlayer(sf::Vector2f _startPos, int _controllerIndex, int _playerCount)
{
	
	/*CGameManager::GetController(_controllerIndex)->Bind(dynamic_cast<IGamepadInput*>(this), "Lobby");
	std::string playerLabel = "P" + std::to_string(_controllerIndex + 1);


	sf::Text* readyText = new sf::Text("", *CResourceHolder::GetFont("comic.ttf"), 15);
	LobbyPlayer newPlayer = { std::make_shared<CPlayer>(playerObj), readyText, false };
	m_players.push_back(newPlayer);*/


}

void CGameScene::OnButtonInput(GamepadButtonEvent _event)
{
	if (_event.type == GamepadButtonEvent::EventType::PRESSED)
	{
		switch (_event.button)
		{
			case Button::DPAD_LEFT:
			{
				Player->move(sf::Vector2f(-5, 0));
			}
			case Button::DPAD_RIGHT:
			{
				Player->move(sf::Vector2f(5, 0));
			}
			case Button::SOUTH:
			{
				Player->move(sf::Vector2f(0, -5));
			}
			case Button::EAST: // back
			{
				Player->move(sf::Vector2f(0, 5));
				//CGameManager::ChangeActiveScene<CMainMenu>();


			}
		}
	}
	//int team = (int)m_players[_event.gamepadIndex].playerPtr->GetTeam();
	//if (_event.type == GamepadButtonEvent::EventType::PRESSED)
	//{
	//	switch (_event.button)
	//	{
	//	case Button::DPAD_LEFT:
	//	{
	//		std::cout << "left";
	//	}
	//	case Button::DPAD_RIGHT:
	//	{

	//	}
	//	case Button::SOUTH:
	//	{

	//	}
	//	case Button::EAST: // back
	//	{
	//		//CGameManager::ChangeActiveScene<CMainMenu>();


	//	}
	//	}
	//}
}
