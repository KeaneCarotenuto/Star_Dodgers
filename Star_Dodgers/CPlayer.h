#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "EasySFML.h"
#include "CGamepad.h"
#include "CResourceHolder.h"
#include "CTeamsManager.h"
#include "CGameManager.h"
#include <memory>

//Forward dec
class CBall;

enum class ThrowStyle {
	Fastball,
	LeftCurve,
	RightCurve,
	None
};

class CPlayer : public CGameObject, public IGamepadInput
{
public:
	CPlayer(int _controllerNum, std::string _texName, Team _team, sf::Vector2f _pos);
	~CPlayer();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void OnButtonInput(GamepadButtonEvent _event);

	void SetController(std::shared_ptr<CGamepad> _controller) { m_controller = _controller; }
	void SetController(int _controllerNum) { m_controller = CGameManager::GetInstance()->GetController(_controllerNum); }
	int GetControllerIndex() const { return(m_controller->GetGamepadIndex()); }

	void SetAimSprite(std::string _texName) { m_aimSprite->setTexture(*CResourceHolder::GetTexture(_texName)); }
	sf::Sprite* GetAimSprite() { return(m_aimSprite); }
	int GetIconElement() { return(m_iconEle); }
	void AddVelocitySpriteToDrawList() { CWindowUtilities::Draw(m_velocitySprite); }
	void StopRendering();

	void SetTeam(Team _team);
	Team GetTeam() { return(m_team); }

	void SetIsReady(bool _isReady) { m_isReadyToPlay = _isReady; }
	bool IsPlayerReady() { return(m_isReadyToPlay); }

	void SetPosition(sf::Vector2f _pos) { m_aimSprite->setPosition(_pos); m_velocitySprite->setPosition(_pos - sf::Vector2f(5, 5)); }
	//void SetPosition(float _x, float _y) { m_aimSprite->setPosition(_x, _y); m_velocitySprite->setPosition(_x, _y); }
	sf::Vector2f GetPosition() { return(m_aimSprite->getPosition()); }
	void SetSize(sf::Vector2f _size);
	// this function returns the width, height, top coord and right coord of the player sprite taking into account 
	// scale, transforms and rotations
	sf::Rect<float> GetRect() { return(m_aimSprite->getGlobalBounds()); }

	ThrowStyle GetThrowStyle() { return m_throwStyle; };

	void Dodge();

	sf::Vector2f GetAim() { return m_desiredAim; };

private:
	std::shared_ptr<CGamepad> m_controller;
	Team m_team = Team::UNDECIDED;
	sf::Sprite* m_aimSprite;
	int m_iconEle;
	sf::Sprite* m_velocitySprite;
	bool m_isReadyToPlay;
	
	float m_speed;
	float m_leftAnalogStickSensitivity;
	float m_rightAnalogStickSensitivity;

	sf::Vector2f m_desiredVelocity;
	sf::Vector2f m_lastVelocity;  // velocity before analog stick stopped being triggered
	sf::Vector2f m_desiredAim;
	float m_currentAimAngle = 0.0f;
	float m_currentVelocityAngle = 0.0f;

	float m_dodgeTimer = 0.0f;
	float m_dodgeCooldown = 0.0f;

	ThrowStyle m_throwStyle = ThrowStyle::Fastball;

	float m_throwCharge = 1.0f;
	bool m_isChargingThrow = false;

	bool m_shouldDelete = false;
};

#endif // __CPLAYER_H__
