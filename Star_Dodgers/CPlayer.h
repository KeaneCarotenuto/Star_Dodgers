#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "EasySFML.h"
#include "CGamepad.h"
#include <memory>

enum class Team
{
	RED = 0,
	BLUE = 1,
	UNDECIDED = 2
};

class CPlayer : public CGameObject
{
public:
	CPlayer();
	~CPlayer();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void SetController(CGamepad _controller) { m_controller = std::make_shared<CGamepad>(_controller); }
	void SetTeam(Team _team) { m_currentTeam = _team; }
	void SetTeam(int _team) { m_currentTeam = (Team)_team; }
	// set current scene for controller binding

private:
	std::shared_ptr<CGamepad> m_controller;
	Team m_currentTeam = Team::UNDECIDED;
};

#endif // __CPLAYER_H__
