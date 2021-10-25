#include "CPlayer.h"

#include "CTeamsManager.h"
#include "CResourceHolder.h"
#include <map>
#include "CGameScene.h"
#include "CPostGameScene.h"
#include "CControlsMenu.h"

CGameScene::CGameScene()
{
	int _redPlayers = 0;
	int _bluePlayers = 0;
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		sf::Vector2f pos;
		if (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetTeam() == Team::BLUE)
		{
			_bluePlayers++;
			pos = sf::Vector2f(1920 * 3 / 4, _bluePlayers * 1080 / 3);

			// player icon
			sf::Vector2f iconPos = (_bluePlayers == 1) ? sf::Vector2f(1795.f, 22.f) : sf::Vector2f(1795.f, 942.f);
			std::string sprStr = "PlayerSprite" + std::to_string(CTeamsManager::GetInstance()->GetPlayer(i).get()->GetIconElement()) + ".png";
			m_playerIconUI[i] = new CUIImage(2, iconPos, { .5f, .5f }, 0.f, CResourceHolder::GetTexture(sprStr));

			// throw sprite
			iconPos = (_bluePlayers == 1) ? sf::Vector2f(1680.f, 12.f) : sf::Vector2f(1665.f, 982.f);
			switch (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetThrowStyle())
			{
			case ThrowStyle::Normal: { sprStr = "NormalThrowIcon.png"; break; }
			case ThrowStyle::LeftCurve: { sprStr = "LeftCurveIcon.png"; break; }
			case ThrowStyle::RightCurve: { sprStr = "RightCurveIcon.png"; break; }
			case ThrowStyle::Fastball: { sprStr = "FastBallIcon.png"; break; }
			case ThrowStyle::None: { /*fallthrough*/ }
			default: { sprStr = "null"; break; }
			}
			m_throwIconUI[i] = (sprStr != "null") ? new CUIImage(2, iconPos, { .75f, .75f }, 0.f, CResourceHolder::GetTexture(sprStr)) : nullptr;
		}
		else if (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetTeam() == Team::RED)
		{
			_redPlayers++;
			pos = sf::Vector2f(1920 * 1 / 4,  (3 - _redPlayers) * 1080 / 3);

			sf::Vector2f iconPos = (_redPlayers == 1) ? sf::Vector2f(25.f, 945.f) : sf::Vector2f(25.f, 22.f);
			std::string sprStr = "PlayerSprite" + std::to_string(CTeamsManager::GetInstance()->GetPlayer(i).get()->GetIconElement()) + ".png";
			m_playerIconUI[i] = new CUIImage(2, iconPos, { .5f, .5f }, 0.f, CResourceHolder::GetTexture(sprStr));

			// throw sprite
			iconPos = (_redPlayers == 1) ? sf::Vector2f(170.f, 982.f) : sf::Vector2f(170.f, 18.f);
			switch (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetThrowStyle())
			{
			case ThrowStyle::Normal: { sprStr = "NormalThrowIcon.png"; break; }
			case ThrowStyle::LeftCurve: { sprStr = "LeftCurveIcon.png"; break; }
			case ThrowStyle::RightCurve: { sprStr = "RightCurveIcon.png"; break; }
			case ThrowStyle::Fastball: { sprStr = "FastBallIcon.png"; break; }
			case ThrowStyle::None: { /*fallthrough*/ }
			default: { sprStr = "null"; break; }
			}
			m_throwIconUI[i] = (sprStr != "null") ? new CUIImage(2, iconPos, { .75f, .75f }, 0.f, CResourceHolder::GetTexture(sprStr)) : nullptr;
		}
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetPosition(pos);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetSize(sf::Vector2f(50, 50));
		CTeamsManager::GetInstance()->GetPlayer(i).get()->AddVelocitySpriteToDrawList();

		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("P" + std::to_string(i), nullptr);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("Gameplay", dynamic_cast<IGamepadInput*>(this));
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

	m_newBall = new CBall();
	m_newBall->SetPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	m_newBall->SetVelocity({ -2,-10 });
	m_newBall2 = new CBall();
	m_newBall2->SetPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	m_newBall2->SetVelocity({ 2,10 });

	f = 0.2f;
	m_uiFrameImg = new CUIImage(1, {0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f, CResourceHolder::GetTexture("UIframeimg.png"));
	m_redScore = new CUIBar(1, sf::Vector2f(10.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarRed.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	m_blueScore = new CUIBar(1, sf::Vector2f(1850.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarBlue.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	
	m_starrySky.setTexture(*CResourceHolder::GetTexture("UIframeimg.png"));
	CWindowUtilities::Draw(&m_starrySky, CResourceHolder::GetShader("starry.glsl"));

	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		CWindowUtilities::Draw(m_playerIconUI[i]->GetSprite());
	}

	for (int i = 0; i < 4; i++)
	{
		if (m_throwIconUI[i] != nullptr)
		{
			CWindowUtilities::Draw(m_throwIconUI[i]->GetSprite());
		}
	}

	m_timer = new CUITimer(1, {930.0f, 20.0f}, {2.0f, 2.0f}, 0.0f);
	
}


/// <summary>
/// Removes all of the components that are in the game scene from their stored locations 
/// </summary>
CGameScene::~CGameScene()
{
	CObjectController::Destroy(m_newBall);
	m_newBall = nullptr;

	CObjectController::Destroy(m_newBall2);
	m_newBall2 = nullptr;

	for (int itt = CTeamsManager::GetInstance()->GetPlayerCount() - 1; itt >= 0; itt--)
	{
		CTeamsManager::GetInstance()->GetPlayer(itt).get()->StopRendering();
	}

	delete m_redScore;
	m_redScore = nullptr;
	delete m_blueScore;
	m_blueScore = nullptr;
	delete m_uiFrameImg;
	m_uiFrameImg = nullptr;

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

	int throwEle = 0;
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawList.size(); ele++)
	{
		if (CWindowUtilities::m_drawList[ele] == m_playerIconUI[0]->GetSprite())
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator 
			auto iter = CWindowUtilities::m_drawList.begin() + ele;
			CWindowUtilities::m_drawList.erase(iter, iter + CTeamsManager::GetInstance()->GetPlayerCount());
			continue;
		}

		if (CWindowUtilities::m_drawList[ele] == m_throwIconUI[throwEle]->GetSprite())
		{
			auto iter = CWindowUtilities::m_drawList.begin() + ele;
			CWindowUtilities::m_drawList.erase(iter);
			++throwEle;
			continue;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		delete m_playerIconUI[i];
		delete m_throwIconUI[i];
	}
}

void CGameScene::Update(float _fDeltaTime)
{
	CResourceHolder::GetShader("starry.glsl")->setUniform("iResolution", sf::Vector2f{1920.0f,1080.0f});
	CResourceHolder::GetShader("starry.glsl")->setUniform("iTime", cmath::g_clock->getElapsedTime().asSeconds());
	
	for (unsigned int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		switch (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetThrowStyle())
		{
		case ThrowStyle::Normal: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("NormalThrowIcon.png")); break; }
		case ThrowStyle::LeftCurve: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("LeftCurveIcon.png")); break; }
		case ThrowStyle::RightCurve: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("RightCurveIcon.png")); break; }
		case ThrowStyle::Fastball: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("FastBallIcon.png")); break; }
		case ThrowStyle::None: { /*fallthrough*/ }
		default: { m_throwIconUI[i] = nullptr; break; }
		}
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
	
}

/// <summary>
/// Game over function that moves to the post game scene
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_team">This is the winning team</param>
void CGameScene::GameOver(Team _winningTeam)
{
	std::cout << CTeamsManager::GetInstance()->GetScore(Team::RED);

	// unbind controllers
	for (int cont = 0; cont < CGameManager::GetInstance()->GetControllerCount(); cont++)
	{
		CGameManager::GetInstance()->GetController(cont)->Unbind("Gameplay");
	}
	CGameManager::GetInstance()->ChangeActiveScene<CPostGameScene>(_winningTeam, m_BlueWiningBalls, m_redWiningBalls);
}

void CGameScene::WinningThrow(Team _throwingTeam, int _points)
{
	switch (_throwingTeam)
	{
	case Team::UNDECIDED:
		break;
	case Team::RED:
		m_redWiningBalls += _points;
		break;
	case Team::BLUE:
		m_BlueWiningBalls += _points;
		break;
	default:
		break;
	}
}
