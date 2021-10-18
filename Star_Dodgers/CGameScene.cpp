#include "CPlayer.h"

#include "CTeamsManager.h"
#include "CResourceHolder.h"
#include <map>
#include "CGameScene.h"
#include "CPostGameScene.h"
#include "CControlsMenu.h"

CGameScene::CGameScene()
{
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("P" + std::to_string(i), nullptr);
		sf::Vector2f pos(rand() % (CResourceHolder::GetWindowSize().x - 50), rand() % (CResourceHolder::GetWindowSize().y - 50));
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetPosition(pos);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetSize(sf::Vector2f(50, 50));
		CTeamsManager::GetInstance()->GetPlayer(i).get()->AddVelocitySpriteToDrawList();

		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("Gameplay", dynamic_cast<IGamepadInput*>(this));
		//m_controllerIndex.push_back(iter->second.get()->GetControllerIndex());
	}

	/*
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
	*/

	newBall = new CBall();
	newBall->SetVelocity({ 10,-10 });
	newBall2 = new CBall();
	newBall2->SetVelocity({ 15,-10 });

	f = 0.2f;
	m_uiFrameImg = new CUIImage(1, {0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f, CResourceHolder::GetTexture("UIframeimg.png"));
	m_redScore = new CUIBar(1, sf::Vector2f(10.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarRed.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	m_blueScore = new CUIBar(1, sf::Vector2f(1850.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarBlue.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	
	m_starrySky.setTexture(*CResourceHolder::GetTexture("UIframeimg.png"));
	CWindowUtilities::Draw(&m_starrySky, CResourceHolder::GetShader("starry.glsl"));
	
}


/// <summary>
/// Removes all of the components that are in the game scene from their stored locations 
/// </summary>
CGameScene::~CGameScene()
{
	CObjectController::Destroy(newBall);
	newBall = nullptr;

	CObjectController::Destroy(newBall2);
	newBall2 = nullptr;
		
	for (int itt = CTeamsManager::GetInstance()->GetPlayerCount() - 1; itt >= 0; itt--)
	{
		CTeamsManager::GetInstance()->RemovePlayer(CTeamsManager::GetInstance()->GetPlayer(itt), itt);
	}

	delete m_redScore;
	delete m_blueScore;
	delete m_uiFrameImg;

	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawListShader.size(); ele++)
	{
		if (CWindowUtilities::m_drawListShader[ele].first == &m_starrySky)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator 
			auto iter = CWindowUtilities::m_drawListShader.begin() + ele;
			CWindowUtilities::m_drawListShader.erase(iter);
			break;
		}
	}
}

void CGameScene::Update(float _fDeltaTime)
{
	CResourceHolder::GetShader("starry.glsl")->setUniform("iResolution", sf::Vector2f{1920.0f,1080.0f});
	CResourceHolder::GetShader("starry.glsl")->setUniform("iTime", cmath::g_clock->getElapsedTime().asSeconds());
	for (unsigned int cont = 0; cont < m_controllerIndex.size(); cont++)
	{
		
	}
	m_redScore->SetFill(100.0f, CTeamsManager::GetInstance()->GetScore(Team::RED));
	m_blueScore->SetFill(100.0f, CTeamsManager::GetInstance()->GetScore(Team::BLUE));
	
}

void CGameScene::FixedUpdate()
{

}

void CGameScene::LateUpdate(float _fDeltaTime)
{
	if (m_winningTeam != Team::UNDECIDED)
	{
		GameOver(m_winningTeam);
	}
}

void CGameScene::OnButtonInput(GamepadButtonEvent _event)
{
	switch (_event.button)
	{
	
	case Button::DPAD_RIGHT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			GameOver( Team::BLUE);
			break;
		}
	}
	}
}

/// <summary>
/// Game over function that moves to the post game scene
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_team">This is the winning team</param>
void CGameScene::GameOver(Team _winningTeam)
{
	CGameManager::GetInstance()->ChangeActiveScene<CControlsMenu>();
	// unbind controllers
	for (int cont = 0; cont < CGameManager::GetInstance()->GetControllerCount(); cont++)
	{
		CGameManager::GetInstance()->GetController(cont)->Unbind("Gameplay");
	}
}
