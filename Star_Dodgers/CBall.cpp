#include "CBall.h"
#include "CPlayer.h"
#include "CMath.h"

std::vector<CBall*> CBall::m_allBalls;

CBall::CBall()
{
	SetSprite("Ball_White.png");
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

		SetVelocity(GetVelocity() + GetAcceleration());
		SetPosition(GetPosition() + GetVelocity());
	}
	else {
		//If player is holding ball, follow player
		SetPosition(m_holder->GetPosition());
	}
}

void CBall::AllPlayerCollision()
{
	//These two loops should be replaced with a single loop through "CTeamsManager::GetAllPlayers() - But its not working atm."

	switch (m_ownerTeam)
	{
	case Team::UNDECIDED: {

		break;
	}

	case Team::RED: {
		std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
		while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
		{
			std::shared_ptr<CPlayer> _player = iter->second;

			SpecificPlayerCollision(_player);

			++iter;
		}
		break;
	}

	case Team::BLUE: {
		std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
		while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
		{
			std::shared_ptr<CPlayer> _player = iter->second;

			SpecificPlayerCollision(_player);

			++iter;
		}
		break;
	}

	default:
		break;
	}
}

void CBall::SpecificPlayerCollision(std::shared_ptr<CPlayer> _player)
{
	if (cmath::Distance(_player->GetPosition(), this->GetPosition()) <= 50.0f)
	{
		SetPosition({ 0,0 });

		SetOwnerTeam(Team::UNDECIDED);
	}
}

void CBall::SetOwnerTeam(Team _team)
{
	m_ownerTeam = _team;
	SetSprite((m_ownerTeam == Team::UNDECIDED ?
		"Ball_White.png" :
		m_ownerTeam == Team::BLUE ?
		"Ball_Blue.png" :
		"Ball_Red.png"));
}

void CBall::AllPlayerInteractions()
{
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam(Team::BLUE).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::BLUE).end())
	{
		std::shared_ptr<CPlayer> _player = iter->second;

		SpecificPlayerInteractions(_player);

		++iter;
	}
	iter = CTeamsManager::GetInstance()->GetTeam(Team::RED).begin();
	while (iter != CTeamsManager::GetInstance()->GetTeam(Team::RED).end())
	{
		std::shared_ptr<CPlayer> _player = iter->second;

		SpecificPlayerInteractions(_player);

		++iter;
	}
}

void CBall::SpecificPlayerInteractions(std::shared_ptr<CPlayer> _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::TryPickup> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;

	TryPickup(_player);
}

void CBall::TryPickup(std::shared_ptr<CPlayer> _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::TryPickup> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;

	if (cmath::Distance(_player->GetPosition(), this->GetPosition()) <= m_pickupRadius) {
		ForcePickup(_player);
	}
	else {
		//Failed to pickup: some kind of nose or something?
	}
}

void CBall::ForcePickup(std::shared_ptr<CPlayer> _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::ForcePickup> [_player] is Null\n"; return; }

	m_holder = _player;
	SetOwnerTeam(m_holder->GetTeam());
}

void CBall::Throw(float _speed)
{
	if (m_holder == nullptr) return;

	if (cmath::Mag(m_holder->GetAim()) >= 0.01f) {
		SetVelocity(cmath::Normalize(m_holder->GetAim()) * _speed);
	}
	else {
		SetVelocity({(float) ( 5 - rand() % 10), (float)(5 - rand() % 10) });
	}
	

	m_holder = nullptr;
}

void CBall::WallCollision()
{
	if ((GetVelocity().x > 0 && GetPosition().x >= CResourceHolder::GetWindow()->getSize().x) ||
		(GetVelocity().x < 0 && GetPosition().x <= 0))
	{
		SetVelocity(sf::Vector2f(-m_velocity.x, m_velocity.y));
	}

	if ((GetVelocity().y > 0 && GetPosition().y >= CResourceHolder::GetWindow()->getSize().y) ||
		(GetVelocity().y < 0 && GetPosition().y <= 0))
	{
		SetVelocity(sf::Vector2f(m_velocity.x, -m_velocity.y));
	}
}

void CBall::LateUpdate(float _fDeltaTime)
{

}