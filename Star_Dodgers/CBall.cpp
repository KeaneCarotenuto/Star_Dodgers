#include "CBall.h"
#include "CPlayer.h"
#include "CMath.h"

std::vector<CBall*> CBall::m_allBalls;

CBall::CBall()
{
	SetSprite("Ball.png");
	SetPosition(sf::Vector2f(0.0f, 0.0f));
	m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f , m_sprite->getLocalBounds().height / 2.0f);

	CWindowUtilities::Draw(GetSprite());

	m_allBalls.push_back(this);
}

CBall::~CBall()
{
	std::vector<CBall*>::iterator it = std::find(GetAllBalls().begin(), GetAllBalls().end(), this);
	if (it != GetAllBalls().end()) {
		m_allBalls.erase(it);
	}
	else {
		std::cerr << "\nWARNING: <CBall::~CBall> [this] does not exist in [m_allBalls]\n";
	}
}

void CBall::Update(float _fDeltaTime)
{
	
}

void CBall::FixedUpdate()
{
	//if player is not holding ball
	if (m_holder == nullptr) {

		WallCollision();

		AllPlayerCollision();

		m_acceleration = - GetVelocity() * 0.01f;

		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ResetBall();
		}
		else
		{
			switch (m_throwStyle)
			{
			case ThrowStyle::Fastball:
				m_acceleration = { 0,0 };
				break;
			case ThrowStyle::LeftCurve:
				SetVelocity(cmath::Rotate(GetVelocity(), -1.5f));
				break;
			case ThrowStyle::RightCurve:
				SetVelocity(cmath::Rotate(GetVelocity(), 1.5f));
				break;

			case ThrowStyle::None:

				break;

			default:
				break;
			}
		}

		

		SetVelocity(GetVelocity() + GetAcceleration());
		SetPosition(GetPosition() + GetVelocity());
	}
	else {
		//If player is holding ball, follow player
		SetPosition(m_holder->GetPosition());
	}
}

void CBall::ResetBall()
{
	SetVelocity({ 0,0 });
	m_acceleration = { 0,0 };

	if (m_isWinningBall) {
		m_isWinningBall = false;
	}

	m_power = CBall::BallPower::None;

	SetOwnerTeam(Team::UNDECIDED);
}

void CBall::AllPlayerCollision()
{
	//These two loops should be replaced with a single loop through "CTeamsManager::GetAllPlayers() - But its not working atm."
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
	{
		CPlayer* _player = iter->second.get();

		SpecificPlayerCollision(_player);

		++iter;
	}
	iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
	{
		CPlayer* _player = iter->second.get();

		SpecificPlayerCollision(_player);

		++iter;
	}
}

void CBall::SpecificPlayerCollision(CPlayer* _player)
{
	if (GetOwnerTeam() != Team::UNDECIDED && GetOwnerTeam() != _player->GetTeam() && cmath::Distance(_player->GetPosition(), this->GetPosition()) <= 50.0f)
	{
		SetVelocity({ 0,0 });

		if (m_isWinningBall) {
			std::cout << (GetOwnerTeam() == Team::BLUE ? "BLUE" : "RED") << " team wins! (Need to hook this up to winning a losing)";

			CTeamsManager::GetInstance()->ResetScore(Team::BLUE);
			CTeamsManager::GetInstance()->ResetScore(Team::RED);

			m_isWinningBall = false;
		}
		else {
			CTeamsManager::GetInstance()->AddScore(GetOwnerTeam() == Team::BLUE ? Team::BLUE : Team::RED);
		}

		SetOwnerTeam(Team::UNDECIDED);
	}
}

void CBall::SetOwnerTeam(Team _team)
{
	m_ownerTeam = _team;
	UpdateVisuals();
}

void CBall::UpdateVisuals()
{
	std::string fileName = "Ball";

	if (m_isWinningBall) fileName += "_Yellow";
	else fileName += (m_power == CBall::BallPower::None ? "" : "_Rainbow");

	switch (m_ownerTeam)
	{
	case Team::UNDECIDED:
		fileName += "";
		break;

	case Team::RED:
		fileName += "_Red";
		break;

	case Team::BLUE:
		fileName += "_Blue";
		break;

	default:
		break;
	}

	fileName += ".png";

	SetSprite(fileName);
}

void CBall::AllPlayerInteractions()
{
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
	{
		CPlayer* _player = iter->second.get();

		SpecificPlayerInteractions(_player);

		++iter;
	}
	iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
	{
		CPlayer* _player = iter->second.get();

		SpecificPlayerInteractions(_player);

		++iter;
	}
}

void CBall::SpecificPlayerInteractions(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::SpecificPlayerInteractions> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;

	TryCatch(_player);
	TryPickup(_player);
}

/// <summary>
/// Checks if the player can catch the ball, if so, does it
/// </summary>
/// <param name="_player"></param>
void CBall::TryCatch(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::TryCatch> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;
	if (m_ownerTeam == Team::UNDECIDED || m_ownerTeam == _player->GetTeam()) return;

	if (cmath::Distance(_player->GetPosition(), this->GetPosition()) <= m_catchRadius) {
		m_power = CBall::BallPower::Homing;
		ForcePickup(_player);
	}
	else {
		//Failed to pickup: some kind of noise or something?
	}
}

/// <summary>
/// Checks if the player can pickup the ball, if so, does it
/// </summary>
/// <param name="_player"></param>
void CBall::TryPickup(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::TryPickup> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;
	if (m_ownerTeam != Team::UNDECIDED && m_ownerTeam != _player->GetTeam()) return;

	if (cmath::Distance(_player->GetPosition(), this->GetPosition()) <= m_pickupRadius) {
		ForcePickup(_player);
	}
	else {
		//Failed to pickup: some kind of noise or something?
	}
}

/// <summary>
/// Actually puts the ball in the player's possession (By Means of picking it up)
/// </summary>
/// <param name="_player"></param>
void CBall::ForcePickup(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::ForcePickup> [_player] is Null\n"; return; }

	m_holder = _player;

	if (CTeamsManager::GetInstance()->GetScore(m_holder->GetTeam()) >= 100) {
		CTeamsManager::GetInstance()->ResetScore(m_holder->GetTeam());
		m_isWinningBall = true;
	}

	SetOwnerTeam(m_holder->GetTeam());
}

/// <summary>
/// Actually puts the ball in the player's possession (By Means of catching it)
/// </summary>
/// <param name="_player"></param>
void CBall::ForceCatch(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::ForceCatch> [_player] is Null\n"; return; }

	m_holder = _player;

	if (CTeamsManager::GetInstance()->GetScore(m_holder->GetTeam()) >= 100) {
		CTeamsManager::GetInstance()->ResetScore(m_holder->GetTeam());
		m_isWinningBall = true;
	}

	SetOwnerTeam(m_holder->GetTeam());
}

void CBall::Throw(float _speed)
{
	if (m_holder == nullptr) return;

	m_throwStyle = m_holder->GetThrowStyle();

	if (cmath::Mag(m_holder->GetAim()) >= 0.01f) {

		m_initialDirection = m_holder->GetAim();

		switch (m_throwStyle)
		{
		case ThrowStyle::Fastball:
			SetVelocity(cmath::Normalize(m_holder->GetAim()) * _speed);
			break;

		case ThrowStyle::LeftCurve:
			SetVelocity(cmath::Rotate(cmath::Normalize(m_holder->GetAim()) * _speed, 45));
			break;

		case ThrowStyle::RightCurve:
			SetVelocity(cmath::Rotate(cmath::Normalize(m_holder->GetAim()) * _speed, -45));
			break;

		default:
			break;
		}
	}
	else {
		SetVelocity({(float) ( 5 - rand() % 10), (float)(5 - rand() % 10) });
	}
	

	m_holder = nullptr;
}

void CBall::WallCollision()
{
	bool hitWall = false;

	if ((GetVelocity().x > 0 && GetPosition().x >= CResourceHolder::GetWindow()->getSize().x) ||
		(GetVelocity().x < 0 && GetPosition().x <= 0))
	{
		SetVelocity(sf::Vector2f(-m_velocity.x, m_velocity.y));
		hitWall = true;
	}

	if ((GetVelocity().y > 0 && GetPosition().y >= CResourceHolder::GetWindow()->getSize().y) ||
		(GetVelocity().y < 0 && GetPosition().y <= 0))
	{
		SetVelocity(sf::Vector2f(m_velocity.x, -m_velocity.y));
		hitWall = true;
	}

	if (hitWall) {
		m_throwStyle = ThrowStyle::None;
	}
}

void CBall::LateUpdate(float _fDeltaTime)
{

}