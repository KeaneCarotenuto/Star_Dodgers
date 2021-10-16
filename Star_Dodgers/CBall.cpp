#include "CBall.h"
#include "CPlayer.h"
#include "CMath.h"

std::vector<CBall*> CBall::m_allBalls;

/// <summary>
/// Ball Constructor
/// <para>Author: Keane</para>
/// </summary>
CBall::CBall()
{
	SetSprite("Ball.png");
	SetPosition(sf::Vector2f(0.0f, 0.0f));
	m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.0f, m_sprite->getLocalBounds().height / 2.0f);

	CWindowUtilities::Draw(GetSprite());
	m_ballSFX.setBuffer(*CResourceHolder::GetSoundBuffer("bullethit_cannon.wav"));
	m_allBalls.push_back(this);
}

CBall::~CBall()
{
	std::vector<sf::Drawable*>::iterator position = std::find(CWindowUtilities::m_drawList.begin(), CWindowUtilities::m_drawList.end(), m_sprite);
	if (position != CWindowUtilities::m_drawList.end()) {
		CWindowUtilities::m_drawList.erase(position);
	}
	delete m_sprite;

	for (CBall* _child : m_childBalls) {
		CObjectController::Destroy(_child);
	}

	std::vector<CBall*>::iterator it = std::find(m_allBalls.begin(), m_allBalls.end(), this);
	if (it != m_allBalls.end()) {
		m_allBalls.erase(it);
	}
	else {
		std::cerr << "\nWARNING: <CBall::~CBall> [this] does not exist in [m_allBalls]\n";
	}
}

/// <summary>
/// Returns the ball that is closest to the given point
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_point"></param>
/// <returns></returns>
CBall* CBall::GetClosestBall(sf::Vector2f _point)
{
	CBall* closest = nullptr;

	for (CBall* _ball : m_allBalls) {
		if (!_ball) continue;
		if (!closest || cmath::Distance(_ball->GetPosition(), _point) < cmath::Distance(closest->GetPosition(), _point)) {
			closest = _ball;
		}
	}

	return closest;
}

void CBall::Update(float _fDeltaTime)
{

}

/// <summary>
/// Fixed update call for ball
/// <para>Author: Keane</para>
/// </summary>
void CBall::FixedUpdate()
{
	//if player is not holding ball
	if (m_holder == nullptr) {

		//Check collisions
		WallCollision();

		AllPlayerCollision();

		//Update accel
		m_acceleration = -GetVelocity() * 0.01f;

		//depending on the ball type, perform some movement
		PerformThrowStyle();

		PerformPower();

		//Update velocity and pos
		SetVelocity(GetVelocity() + GetAcceleration());
		SetPosition(GetPosition() + GetVelocity());
	}
	else {
		//If player is holding ball, follow player
		SetPosition(m_holder->GetPosition());
	}
}

void CBall::PerformThrowStyle()
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

void CBall::PerformPower()
{

	switch (m_power)
	{
	case CBall::BallPower::None:
		//If ball is slow enough, come to a stop
		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ResetBall();
		}
		break;

	case CBall::BallPower::Homing:
		break;

	case CBall::BallPower::Exploding:
		break;

	case CBall::BallPower::BulletHell:
		//If ball is slow enough, come to a stop
		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			SetVelocity({ 0.0f, 0.0f });
			SetAcceleration({ 0.0f, 0.0f });

			//For the first time, activate power
			if (m_powerActivationTime == -INFINITY || m_powerDuration == -INFINITY) {
				m_powerActivationTime = cmath::g_clock->getElapsedTime().asSeconds();
				m_powerDuration = 4.0f;
			}
		}

		//If the power is active
		if (m_powerActivationTime != -INFINITY && m_powerDuration != -INFINITY) {

			//if the power still has time
			if (cmath::g_clock->getElapsedTime().asSeconds() - m_powerActivationTime <= m_powerDuration) {

				//spawn a ball every so often, and shoot it at some angle based on time

				static bool canSpawn = true;
				float sinVal = sin(float(M_PI) / 2.0f + cmath::g_clock->getElapsedTime().asSeconds() * 40.0f);

				//Spawn ball, then wait to be allowed to spawn again. Using sine waves to time it.
				if (canSpawn && sinVal >= 0.5f)
				{
					canSpawn = false;
					CBall* childBall = new CBall();
					childBall->SetPosition(GetPosition());
					childBall->SetVelocity({ cos(cmath::g_clock->getElapsedTime().asSeconds()), sin(cmath::g_clock->getElapsedTime().asSeconds()) });
					childBall->m_canPickup = false;
					childBall->SetOwnerTeam(m_ownerTeam);

					m_childBalls.push_back(childBall);
				}
				else if (sinVal <= -0.5f) {
					canSpawn = true;
				}

			}
			else {
				//Stop powerups
				m_powerActivationTime = -INFINITY;
				m_powerDuration = -INFINITY;

				for (CBall* _childBall : m_childBalls) {
					CObjectController::Destroy(_childBall);
				}
				m_childBalls.clear();

				ResetBall();
			}
		}


		break;

	default:
		break;
	}
}

/// <summary>
/// Reset ball to default state
/// <para>Author: Keane</para>
/// </summary>
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

/// <summary>
/// Perform collision checks against all players
/// <para>Author: Keane</para>
/// </summary>
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

/// <summary>
/// Perform collision check and logic against specific player
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_player"></param>
void CBall::SpecificPlayerCollision(CPlayer* _player)
{
	if (GetOwnerTeam() != Team::UNDECIDED && GetOwnerTeam() != _player->GetTeam() && cmath::Distance(_player->GetPosition(), this->GetPosition()) <= 50.0f)
	{
		//If winning ball, add score
		if (m_isWinningBall) {
			std::cout << (GetOwnerTeam() == Team::BLUE ? "BLUE" : "RED") << " team wins! (Need to hook this up to winning a losing)";

			CTeamsManager::GetInstance()->ResetScore(Team::BLUE);
			CTeamsManager::GetInstance()->ResetScore(Team::RED);
		}
		else {
			CTeamsManager::GetInstance()->AddScore(GetOwnerTeam() == Team::BLUE ? Team::BLUE : Team::RED);
		}

		ResetBall();
	}
}

/// <summary>
/// Set the owner team of this ball
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_team"></param>
void CBall::SetOwnerTeam(Team _team)
{
	m_ownerTeam = _team;
	UpdateVisuals();
}

/// <summary>
/// Update the visuals of the ball based on team, type, winning ball, etc
/// <para>Author: Keane</para>
/// </summary>
void CBall::UpdateVisuals()
{
	std::string fileName = "Ball";

	//If winning or power
	if (m_isWinningBall) fileName += "_Yellow";
	else fileName += (m_power == CBall::BallPower::None ? "" : "_Rainbow");

	//If red or blue, or not
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

/// <summary>
/// Check interactions with all players
/// <para>Author: Keane</para>
/// </summary>
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

/// <summary>
/// Check interaction with specific player
/// </summary>
/// <param name="_player"></param>
void CBall::SpecificPlayerInteractions(CPlayer* _player)
{
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::SpecificPlayerInteractions> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;

	//Catch first, if not, try pickup (they cannot both happen, but that logic should probably be included here to make it more clear)
	TryCatch(_player);
	TryPickup(_player);
}

/// <summary>
/// Checks if the player can catch the ball, if so, does it
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_player"></param>
void CBall::TryCatch(CPlayer* _player)
{
	if (!m_canPickup) return;
	if (_player == nullptr) { std::cerr << "\nWARNING: <CBall::TryCatch> [_player] is Null\n"; return; }
	if (m_holder != nullptr) return;
	if (m_ownerTeam == Team::UNDECIDED || m_ownerTeam == _player->GetTeam()) return;

	if (cmath::Distance(_player->GetPosition(), this->GetPosition()) <= m_catchRadius) {
		m_power = CBall::BallPower::BulletHell;
		ForcePickup(_player);
	}
	else {
		//Failed to pickup: some kind of noise or something?
	}
}

/// <summary>
/// Checks if the player can pickup the ball, if so, does it
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_player"></param>
void CBall::TryPickup(CPlayer* _player)
{
	if (!m_canPickup) return;
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
/// <para>Author: Keane</para>
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
/// <para>Author: Keane</para>
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

/// <summary>
/// Attempt to throw the ball in the aim direction
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_speed"></param>
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
		SetVelocity({ (float)(5 - rand() % 10), (float)(5 - rand() % 10) });
	}


	m_holder = nullptr;
}

/// <summary>
/// Bounce off of walls
/// <para>Author: Keane</para>
/// </summary>
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
		m_ballSFX.play();
		CPostProcessing::GetInstance()->AddScreenShake(cmath::Abs(GetVelocity()), sf::Vector2f{50.0f,50.0f}, 0.3f);
		CPostProcessing::GetInstance()->AddChromaAberration(0.001f, 0.3f);
	}
}

void CBall::LateUpdate(float _fDeltaTime)
{

}