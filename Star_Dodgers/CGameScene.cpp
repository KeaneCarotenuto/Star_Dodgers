#include "CPlayer.h"
#include "CBall.h"
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
		CGameManager::GetInstance()->GetController(i).get()->Bind(dynamic_cast<IGamepadInput*>(newPlayer.get()), playerLabel);
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

	CBall* newBall = new CBall();
	newBall->SetVelocity({ 10,-10 });
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

}