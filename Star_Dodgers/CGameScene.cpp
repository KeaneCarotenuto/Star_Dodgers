#include "CPlayer.h"
#include "CTeamsManager.h"
#include "CResourceHolder.h"
#include <map>
#include "CGameScene.h"
#include "CPostGameScene.h"
#include "CControlsMenu.h"

#ifndef M_PIf32
#define M_PIf32 3.14159f
#endif // !M_PIf32

/// <summary>
/// Constructs the game scene
/// </summary>
CGameScene::CGameScene()
{
	int _redPlayers = 0;
	int _bluePlayers = 0;

	//instantiate all players
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		sf::Vector2f pos;
		CTeamsManager::GetInstance()->GetPlayer(i).get()->m_inGame = true;
		//blue team
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
			CTeamsManager::GetInstance()->GetPlayer(i).get()->SetCurrentAimAngle(180);
		}
		else if (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetTeam() == Team::RED) //Red Team
		{
			_redPlayers++;
			pos = sf::Vector2f(1920 * 1 / 4,  (3 - _redPlayers) * 1080 / 3);

			//sprite
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
			CTeamsManager::GetInstance()->GetPlayer(i).get()->SetCurrentAimAngle(0);
		}

		//Set player values
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetPosition(pos);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetSize(sf::Vector2f(50, 50));
		
		CTeamsManager::GetInstance()->GetPlayer(i).get()->AddVelocitySpriteToDrawList();

		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("P" + std::to_string(i), nullptr);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->BindController("Gameplay", dynamic_cast<IGamepadInput*>(this));
	}

	//Create balls
	for (int i = 0; i < 10; i++)
	{
		CBall* b = new CBall();
		b->SetPosition(sf::Vector2f(1920 / 2, 1080 / 2));
		b->SetVelocity({ sin((M_PIf32/10.0f)*i) * 5.0f,cos((M_PIf32/10.0f)*i) * 5.0f});
		m_sceneBalls.push_back(b);
	}
	for (int i = 0; i < 10; i++)
	{
		CBall* b = new CBall();
		b->SetPosition(sf::Vector2f(1920 / 2, 1080 / 2));
		b->SetVelocity({ -sin((M_PIf32/10.0f)*i) * 5.0f,cos((M_PIf32/10.0f)*i) * 5.0f});
		m_sceneBalls.push_back(b);
	}
	
	//Create UI
	f = 0.2f;
	std::string frameStr = (CTeamsManager::GetInstance()->GetPlayerCount() == 2) ? "UIframeimg_2P.png" : "UIframeimg_4P.png";
	m_uiFrameImg = new CUIImage(1, {0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f, CResourceHolder::GetTexture(frameStr));
	m_redScore = new CUIBar(1, sf::Vector2f(10.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarRed.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	m_blueScore = new CUIBar(1, sf::Vector2f(1850.0f, 775.0f), sf::Vector2f(5.0f, 3.0f), 270, CResourceHolder::GetTexture("UIBarBlue.png"), CResourceHolder::GetTexture("UIBarFrame.png"));
	
	m_starrySky.setTexture(*CResourceHolder::GetTexture(frameStr));
	CWindowUtilities::Draw(&m_starrySky, CResourceHolder::GetShader("starry.glsl"));

	//add sprites to draw list
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
	
	//Create midline
	m_midLine = new sf::VertexArray(sf::PrimitiveType::Quads, 4);
	(*m_midLine)[0].position = { CResourceHolder::GetWindowSize().x / 2.0f - 5.0f, 0 };
	(*m_midLine)[1].position = { CResourceHolder::GetWindowSize().x / 2.0f - 5.0f, (float)CResourceHolder::GetWindowSize().y };
	(*m_midLine)[2].position = { CResourceHolder::GetWindowSize().x / 2.0f + 5.0f, (float)CResourceHolder::GetWindowSize().y };
	(*m_midLine)[3].position = { CResourceHolder::GetWindowSize().x / 2.0f + 5.0f, 0 };

	(*m_midLine)[0].color = sf::Color(255, 255, 255, 100);
	(*m_midLine)[1].color = sf::Color(255, 255, 255, 100);
	(*m_midLine)[2].color = sf::Color(255, 255, 255, 100);
	(*m_midLine)[3].color = sf::Color(255, 255, 255, 100);

	CWindowUtilities::Draw(m_midLine);


}


/// <summary>
/// Removes all of the components that are in the game scene from their stored locations 
/// </summary>
CGameScene::~CGameScene()
{
	

	/*for (int itt = CTeamsManager::GetInstance()->GetPlayerCount() - 1; itt >= 0; itt--)
	{
		CTeamsManager::GetInstance()->GetPlayer(itt).get()->StopRendering();
	}*/

	for (int i = 0; i < m_sceneBalls.size(); i++)
	{
		CObjectController::Destroy(m_sceneBalls[i]);
	}
	m_sceneBalls.clear();

	delete m_redScore;
	m_redScore = nullptr;
	delete m_blueScore;
	m_blueScore = nullptr;
	delete m_uiFrameImg;
	m_uiFrameImg = nullptr;
	delete 	m_timer;
	m_timer = nullptr;
	CWindowUtilities::m_drawList;

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
	CWindowUtilities::m_drawList;

	int throwEle = 0;
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		for (unsigned int ele = 0; ele < CWindowUtilities::m_drawList.size(); ele++)
		{
			if (CWindowUtilities::m_drawList[ele] == m_playerIconUI[i]->GetSprite())
			{
				// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
				// erase the element at the iterator 
				auto iter = CWindowUtilities::m_drawList.begin() + ele;
				CWindowUtilities::m_drawList.erase(iter);
				//continue;

			}
			if (CWindowUtilities::m_drawList[ele] == m_throwIconUI[i]->GetSprite())
			{
				auto iter = CWindowUtilities::m_drawList.begin() + ele;
				CWindowUtilities::m_drawList.erase(iter);
				continue;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		delete m_playerIconUI[i];
		delete m_throwIconUI[i];
	}
	
	//Remove midline
	std::vector<sf::Drawable*>::iterator position = std::find(CWindowUtilities::m_drawList.begin(), CWindowUtilities::m_drawList.end(), m_midLine);
	if (position != CWindowUtilities::m_drawList.end()) {
		CWindowUtilities::m_drawList.erase(position);
	}
	delete m_midLine;
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		CTeamsManager::GetInstance()->GetPlayer(i)->StopRendering();
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetIsReady(false);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->SetTeam(Team::UNDECIDED);
		CTeamsManager::GetInstance()->GetPlayer(i).get()->m_inGame = false;
		CTeamsManager::GetInstance()->GetPlayer(i)->UnbindController("P" + std::to_string(i));
		CTeamsManager::GetInstance()->GetPlayer(i)->UnbindController("Gameplay");
	}
}

/// <summary>
/// Update function for game scene
/// </summary>
/// <param name="_fDeltaTime"></param>
void CGameScene::Update(float _fDeltaTime)
{
	//Does background shader
	CResourceHolder::GetShader("starry.glsl")->setUniform("iResolution", sf::Vector2f{1920.0f,1080.0f});
	CResourceHolder::GetShader("starry.glsl")->setUniform("iTime", cmath::g_clock->getElapsedTime().asSeconds());
	
	//Updates UI for all players
	for (unsigned int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		switch (CTeamsManager::GetInstance()->GetPlayer(i).get()->GetThrowStyle())
		{
		case ThrowStyle::Normal: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("NormalThrowIcon.png")); break; }
		case ThrowStyle::RightCurve: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("LeftCurveIcon.png")); break; }
		case ThrowStyle::LeftCurve: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("RightCurveIcon.png")); break; }
		case ThrowStyle::Fastball: { m_throwIconUI[i]->GetSprite()->setTexture(*CResourceHolder::GetTexture("FastBallIcon.png")); break; }
		case ThrowStyle::None: { /*fallthrough*/ }
		default: { m_throwIconUI[i] = nullptr; break; }
		}
	}

	//Update score bars
	m_redScore->SetFill(100.0f, CTeamsManager::GetInstance()->GetScore(Team::RED));
	m_blueScore->SetFill(100.0f, CTeamsManager::GetInstance()->GetScore(Team::BLUE));
	
}

void CGameScene::FixedUpdate()
{

}

/// <summary>
/// Late update
/// </summary>
/// <param name="_fDeltaTime"></param>
void CGameScene::LateUpdate(float _fDeltaTime)
{
	//check for win
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

/// <summary>
/// Check who got the winning ball
/// </summary>
/// <param name="_throwingTeam"></param>
/// <param name="_points"></param>
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
