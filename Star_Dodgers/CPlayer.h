#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "EasySFML.h"
#include "CGamepad.h"
#include "CResourceHolder.h"
#include "CTeamsManager.h"
#include "CGameManager.h"
#include <memory>

class CPlayer : public CGameObject
{
public:
	CPlayer(int _controllerIndex, std::string _texName, Team _team, sf::Vector2f _pos);
	~CPlayer();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void SetController(std::shared_ptr<CGamepad> _controller) { m_controller = _controller; }
	void SetController(int _controllerIndex) { m_controller = CGameManager::GetInstance()->GetController(_controllerIndex); }
	int GetControllerIndex() const { return(m_controller->GetIndex()); }

	void SetSprite(std::string _texName) { m_sprite.setTexture(*CResourceHolder::GetTexture(_texName)); }
	sf::Sprite* GetSprite() { return(&m_sprite); }

	void SetTeam(Team _team);
	Team GetTeam() { return(m_currentTeam); }

	void SetIsReady(bool _isReady) { m_isReadyToPlay = _isReady; }
	bool IsPlayerReady() { return(m_isReadyToPlay); }

	void SetPosition(sf::Vector2f _pos) { m_sprite.setPosition(_pos); }
	void SetPosition(float _x, float _y) { m_sprite.setPosition(_x, _y); }
	sf::Vector2f GetPosition() { return(m_sprite.getPosition()); }
	void SetSize(sf::Vector2f _size);
	// this function returns the width, height, top coord and right coord of the player sprite taking into account 
	// scale, transforms and rotations
	sf::Rect<float> GetRect() { return(m_sprite.getGlobalBounds()); }

private:
	std::shared_ptr<CGamepad> m_controller;
	Team m_currentTeam = Team::UNDECIDED;
	sf::Sprite m_sprite;
	bool m_isReadyToPlay;
	
	sf::Vector2f m_velocity;
	sf::Vector2f m_throwDirection;
};

#endif // __CPLAYER_H__
