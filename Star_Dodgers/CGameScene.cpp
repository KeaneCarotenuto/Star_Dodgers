#include "CPlayer.h"
#include "CTeamsManager.h"
#include "CResourceHolder.h"
#include <map>
#include "CGameScene.h"

CGameScene::CGameScene(int _playerCount)
{
	for (int i = 0; i < _playerCount; i++)
	{
		Team team = (((i + 1) % 2) == 0) ? Team::RED : Team::BLUE;
		std::string playerLabel = "P" + std::to_string(i + 1);
		sf::Vector2f pos(rand() % (CResourceHolder::GetWindowSize().x - 50), rand() % (CResourceHolder::GetWindowSize().y - 50));
		std::shared_ptr<CPlayer> newPlayer(new CPlayer(i, playerLabel + ".png", team, pos));
		CTeamsManager::GetInstance()->AddToTeam(newPlayer, team);
		CWindowUtilities::Draw(newPlayer.get()->GetAimSprite());
	}

	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
	{
		iter->second.get()->SetSize(sf::Vector2f(50, 50));
		iter->second.get()->AddVelocitySpriteToDrawList();
		CGameManager::GetInstance()->GetController(iter->second.get()->GetControllerIndex()).get()->Bind(dynamic_cast<IGamepadInput*>(this), "Gameplay");
		m_controllerIndex.push_back(iter->second.get()->GetControllerIndex());
		// setup UI
		++iter;
	}

	iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
	{
		iter->second.get()->SetSize(sf::Vector2f(50, 50));
		iter->second.get()->AddVelocitySpriteToDrawList();
		CGameManager::GetInstance()->GetController(iter->second.get()->GetControllerIndex()).get()->Bind(dynamic_cast<IGamepadInput*>(this), "Gameplay");
		m_controllerIndex.push_back(iter->second.get()->GetControllerIndex());
		// setup UI
		++iter;
	}
}

CGameScene::CGameScene()
{
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
	{
		iter->second.get()->SetPosition(rand() % (CResourceHolder::GetWindowSize().x - 50), rand() % (CResourceHolder::GetWindowSize().y - 50));
		iter->second.get()->SetSize(sf::Vector2f(50, 50));
		iter->second.get()->AddVelocitySpriteToDrawList();
		CGameManager::GetInstance()->GetController(iter->second.get()->GetControllerIndex()).get()->Bind(dynamic_cast<IGamepadInput*>(this), "Gameplay");
		m_controllerIndex.push_back(iter->second.get()->GetControllerIndex());
		// setup UI
		++iter;
	}

	iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
	{
		iter->second.get()->SetPosition(rand() % (CResourceHolder::GetWindowSize().x - 50), rand() % (CResourceHolder::GetWindowSize().y - 50));
		iter->second.get()->SetSize(sf::Vector2f(50, 50));
		iter->second.get()->AddVelocitySpriteToDrawList();
		CGameManager::GetInstance()->GetController(iter->second.get()->GetControllerIndex()).get()->Bind(dynamic_cast<IGamepadInput*>(this), "Gameplay");
		m_controllerIndex.push_back(iter->second.get()->GetControllerIndex());
		// setup UI
		++iter;
	}
}

CGameScene::~CGameScene()
{

}

void CGameScene::Update(float _fDeltaTime)
{
	for (unsigned int cont = 0; cont < m_controllerIndex.size(); cont++)
	{
		
	}
}

void CGameScene::FixedUpdate()
{

}

void CGameScene::LateUpdate(float _fDeltaTime)
{

}

void CGameScene::OnButtonInput(GamepadButtonEvent _event)
{
	std::shared_ptr<CPlayer> player = CTeamsManager::GetInstance()->GetPlayer(_event.gamepadIndex);

	switch (_event.button)
	{
	case Button::SOUTH: // X button - dodge
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			player.get()->Dodge();
		}
		break;
	}
	case Button::WEST: // curve ball left
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
		}
		break;
	}
	case Button::EAST: // curveball right
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
		}
		break;
	}
	case Button::NORTH: // fast ball
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
		}
		break;
	}
	case Button::RIGHT_SHOULDER: // catch / quick throw
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
		}
		break;
	}
	}
}

