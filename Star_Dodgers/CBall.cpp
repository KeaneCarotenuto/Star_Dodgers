#include "CBall.h"
#include "CPlayer.h"
#include "CMath.h"

std::vector<CBall*> CBall::m_allBalls;

#pragma region Construct/Destruct

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

	m_wallbounceSFX.setBuffer(*CResourceHolder::GetSoundBuffer("bullethit_cannon.wav"));
	m_explodeSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Explosion.wav"));
	m_goldenStarSFX.setBuffer(*CResourceHolder::GetSoundBuffer("GoldenStarPickup.wav"));
	m_powerupSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Powerup.wav"));
	m_throwSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Throw.wav"));
	m_catchSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Catch.wav"));
	m_hurtSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Explosion.wav"));
	m_powerupSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Powerup.wav"));

	m_allBalls.push_back(this);
}

/// <summary>
/// Ball destructor
/// </summary>
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

#pragma endregion

#pragma region Utility

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
/// Reset ball to default state
/// <para>Author: Keane</para>
/// </summary>
void CBall::ResetBall()
{
	m_hitPlayers.clear();

	StopPower();

	SetVelocity({ 0,0 });
	m_acceleration = { 0,0 };

	if (m_isWinningBall) {
		m_isWinningBall = false;
	}

	m_canPickup = true;

	m_power = CBall::BallPower::None;

	SetOwnerTeam(Team::UNDECIDED);
}

#pragma endregion

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

/// <summary>
/// Performs the movement for the throw styles
/// </summary>
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

	case ThrowStyle::Normal:
		m_acceleration = -GetVelocity() * 0.01f;
		break;

	case ThrowStyle::None:
		break;

	default:
		break;
	}
}

#pragma region Powers

/// <summary>
/// Activates the actual power of the ball
/// </summary>
void CBall::ActivatePower()
{
	switch (m_power)
	{
	case CBall::BallPower::None:
		break;
	case CBall::BallPower::Homing:
		SetVelocity({ 0.0f, 0.0f });
		SetAcceleration({ 0.0f, 0.0f });

		//For the first time, activate power
		if (m_powerActivationTime == -INFINITY || m_powerDuration == -INFINITY) {
			m_powerActivationTime = cmath::g_clock->getElapsedTime().asSeconds();
			m_powerDuration = 3.0f;

			for (int i = 0; i < 3; i++) {
				CBall* _homingBall = new CBall();
				_homingBall->m_parent = this;
				_homingBall->SetPosition(GetPosition());
				_homingBall->SetVelocity(2.0f * sf::Vector2f(cos(float(rand() % 100)), sin(float(rand() % 100))));
				_homingBall->m_canPickup = false;
				_homingBall->m_throwStyle = ThrowStyle::None;
				_homingBall->SetOwnerTeam(m_ownerTeam);
				m_childBalls.push_back(_homingBall);
			}

			m_explodeSFX.play();
		}
		break;

	case CBall::BallPower::Exploding:
		SetVelocity({ 0.0f, 0.0f });
		SetAcceleration({ 0.0f, 0.0f });

		//For the first time, activate power
		if (m_powerActivationTime == -INFINITY || m_powerDuration == -INFINITY) {
			m_powerActivationTime = cmath::g_clock->getElapsedTime().asSeconds();
			m_powerDuration = 3.0f;

			m_explodeSFX.play();
		}
		break;

	case CBall::BallPower::BulletHell:
		SetVelocity({ 0.0f, 0.0f });
		SetAcceleration({ 0.0f, 0.0f });

		//For the first time, activate power
		if (m_powerActivationTime == -INFINITY || m_powerDuration == -INFINITY) {
			m_powerActivationTime = cmath::g_clock->getElapsedTime().asSeconds();
			m_powerDuration = 4.0f;

			m_explodeSFX.play();
		}
		break;

	case CBall::BallPower::SuperFast:
		//For the first time, activate power
		if (m_powerActivationTime == -INFINITY || m_powerDuration == -INFINITY) {
			m_powerActivationTime = cmath::g_clock->getElapsedTime().asSeconds();
			m_powerDuration = 4.0f;
		}
		break;
		break;
	default:
		break;
	}
}

/// <summary>
/// The logic for the ball during update
/// </summary>
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
		m_canPickup = false;

		//If ball is slow enough, come to a stop
		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ActivatePower();
		}

		//If the power is active
		if (m_powerActivationTime != -INFINITY && m_powerDuration != -INFINITY) {

			//if the power still has time
			if (cmath::g_clock->getElapsedTime().asSeconds() - m_powerActivationTime <= m_powerDuration) {

				for (CBall* _homingBall : m_childBalls) {
					std::shared_ptr<CPlayer> closest = CTeamsManager::GetInstance()->GetNearestPlayer(_homingBall->GetPosition(), GetOwnerTeam() == Team::BLUE ? Team::RED : Team::BLUE, m_hitPlayers);

					if (closest) {
						_homingBall->SetAcceleration(cmath::Normalize(closest->GetPosition() - _homingBall->GetPosition()) * 0.25f);
					}
				}

			}
			else {
				//Stop powerups
				ResetBall();
			}
		}

		break;

	case CBall::BallPower::Exploding:
		m_canPickup = false;

		m_acceleration = -GetVelocity() * 0.01f;

		//If ball is slow enough, come to a stop
		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ActivatePower();
		}

		//If the power is active
		if (m_powerActivationTime != -INFINITY && m_powerDuration != -INFINITY) {

			//if the power still has time
			if (cmath::g_clock->getElapsedTime().asSeconds() - m_powerActivationTime <= m_powerDuration) {

				//spawn a ball every so often, and shoot it at some angle based on time

				static bool canSpawn = true;
				float sinVal = sin(float(M_PI) / 2.0f + cmath::g_clock->getElapsedTime().asSeconds() * 10.0f);

				//Spawn ball, then wait to be allowed to spawn again. Using sine waves to time it.
				if (canSpawn && sinVal >= 0.5f)
				{
					canSpawn = false;
					m_explodeSFX.play();

					float speedMulti = 2.0f;
					const unsigned int maxRotations = 4;
					for (int rotation = 0; rotation < maxRotations; rotation++) {
						CBall* _fragmentBall = new CBall();
						_fragmentBall->m_parent = this;
						_fragmentBall->SetPosition(GetPosition());
						_fragmentBall->SetVelocity(speedMulti * cmath::Rotate({ cos(float(rand() % 100)), sin(float(rand() % 100)) }, rotation * (360.0f / maxRotations)));
						_fragmentBall->m_canPickup = false;
						_fragmentBall->SetOwnerTeam(m_ownerTeam);
						m_childBalls.push_back(_fragmentBall);
					}
				}
				else if (sinVal <= -0.5f) {
					canSpawn = true;
				}

			}
			else {
				//Stop powerups
				ResetBall();
			}
		}
		break;

	case CBall::BallPower::BulletHell:

		m_canPickup = false;

		//If ball is slow enough, come to a stop
		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ActivatePower();
		}

		//If the power is active
		if (m_powerActivationTime != -INFINITY && m_powerDuration != -INFINITY) {

			//if the power still has time
			if (cmath::g_clock->getElapsedTime().asSeconds() - m_powerActivationTime <= m_powerDuration) {
				
				CPostProcessing::GetInstance()->AddScreenShake(sf::Vector2f{0.5f, 0.5f}, sf::Vector2f{10.0f,10.0f}, 0.3f);


				//spawn a ball every so often, and shoot it at some angle based on time

				static bool canSpawn = true;
				float sinVal = sin(float(M_PI) / 2.0f + cmath::g_clock->getElapsedTime().asSeconds() * 40.0f);

				//Spawn ball, then wait to be allowed to spawn again. Using sine waves to time it.
				if (canSpawn && sinVal >= 0.5f)
				{
					canSpawn = false;

					float speedMulti = 10.0f;
					const unsigned int maxRotations = 2;
					for (int rotation = 0; rotation < maxRotations; rotation++) {
						CBall* childBall = new CBall();
						childBall->m_parent = this;
						childBall->SetPosition(GetPosition());
						childBall->SetVelocity(speedMulti * cmath::Rotate({cos(cmath::g_clock->getElapsedTime().asSeconds()), sin(cmath::g_clock->getElapsedTime().asSeconds())}, rotation * (360.0f / maxRotations)));
						childBall->m_canPickup = false;
						childBall->SetOwnerTeam(m_ownerTeam);
						m_childBalls.push_back(childBall);
					}
				}
				else if (sinVal <= -0.5f) {
					canSpawn = true;
				}

			}
			else {
				//Stop powerups
				ResetBall();
			}
		}


		break;

	case CBall::BallPower::SuperFast:
		m_canPickup = true;

		//If the power is active
		if (m_powerActivationTime != -INFINITY && m_powerDuration != -INFINITY) {
			if (cmath::g_clock->getElapsedTime().asSeconds() - m_powerActivationTime <= m_powerDuration) {
				m_acceleration = { 0,0 };
			}
			else {
				StopPower();
			}
		}

		if (cmath::Mag(GetVelocity()) <= 0.25f) {
			ResetBall();
		}
		break;

	default:
		break;
		
		ResetBall();
	}
}

/// <summary>
/// Stops the power DOESNT RESET
/// </summary>
void CBall::StopPower()
{
	m_powerActivationTime = -INFINITY;
	m_powerDuration = -INFINITY;

	for (CBall* _childBall : m_childBalls) {
		CObjectController::Destroy(_childBall);
	}
	m_childBalls.clear();
}

#pragma endregion

#pragma region PlayerInteractions

/// <summary>
/// Check interactions with all players
/// <para>Author: Keane</para>
/// </summary>
void CBall::AllPlayerInteractions()
{
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		SpecificPlayerInteractions(CTeamsManager::GetInstance()->GetPlayer(i).get());
	}

	/*
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
	}*/
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
		ForceCatch(_player);
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

	ResetBall();

	m_holder = _player;

	if (CTeamsManager::GetInstance()->GetScore(m_holder->GetTeam()) >= 100) {
		CTeamsManager::GetInstance()->ResetScore(m_holder->GetTeam());
		SetWinningBall();
		
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

	ResetBall();

	m_catchSFX.play();

	m_holder = _player;

	if (CTeamsManager::GetInstance()->GetScore(m_holder->GetTeam()) >= 100) {
		CTeamsManager::GetInstance()->ResetScore(m_holder->GetTeam());
		SetWinningBall();
	}
	else {
		m_power = static_cast<BallPower>(1 + (rand() % 4));
		//m_power = BallPower::BulletHell;
		m_powerupSFX.play();
	}

	SetOwnerTeam(m_holder->GetTeam());
}

/// <summary>
/// Sets current ball to winning ball
/// </summary>
void CBall::SetWinningBall()
{
	
	m_goldenStarSFX.play();

	m_isWinningBall = true;
	m_power = CBall::BallPower::None;

	UpdateVisuals();
}

/// <summary>
/// Attempt to throw the ball in the aim direction
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_speed"></param>
void CBall::Throw(float _speed)
{
	if (m_holder == nullptr) return;

	m_throwSFX.play();

	m_throwStyle = m_holder->GetThrowStyle();

	m_initialDirection = m_holder->GetAim();
	float currentAim = m_holder->GetCurrentAimAngle();

	//calculate aim vector using the currentAim angle
	sf::Vector2f aimVector = cmath::Normalize(sf::Vector2f(cos(cmath::Radians(currentAim)), sin(cmath::Radians(currentAim))));

	switch (m_throwStyle)
	{
	case ThrowStyle::Fastball:
		SetVelocity(aimVector * _speed);
		break;

	case ThrowStyle::LeftCurve:
		SetVelocity(cmath::Rotate(aimVector * _speed, 45));
		break;

	case ThrowStyle::RightCurve:
		SetVelocity(cmath::Rotate(aimVector * _speed, -45));
		break;

	default:
		break;
	}

	switch (m_power)
	{
	case CBall::BallPower::None:
		break;
	case CBall::BallPower::Homing:
		break;
	case CBall::BallPower::Exploding:
		SetVelocity(GetVelocity() * 0.5f);
		break;
	case CBall::BallPower::BulletHell:
		break;
	case CBall::BallPower::SuperFast:
		SetVelocity(GetVelocity() * 2.0f);
		ActivatePower();
		break;
	default:
		break;
	}


	m_holder = nullptr;
}

#pragma endregion

#pragma region Collisions

/// <summary>
/// Perform collision checks against all players
/// <para>Author: Keane</para>
/// </summary>
void CBall::AllPlayerCollision()
{
	for (int i = 0; i < CTeamsManager::GetInstance()->GetPlayerCount(); i++)
	{
		SpecificPlayerCollision(CTeamsManager::GetInstance()->GetPlayer(i).get());
	}

	/*
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
	}*/
}

/// <summary>
/// Perform collision check and logic against specific player
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_player"></param>
void CBall::SpecificPlayerCollision(CPlayer* _player)
{
	bool didHit = false;

	//Check for hit
	if (GetOwnerTeam() != Team::UNDECIDED && GetOwnerTeam() != _player->GetTeam() && cmath::Distance(_player->GetPosition(), this->GetPosition()) <= 50.0f)
	{
		//Perform power specific interaction
		switch (m_power)
		{
		case CBall::BallPower::None:
			//if already hit, skip
			if (CheckAlreadyHit(_player)) return;

			//If winning ball, add score (Can only be winning ball if not power)
			if (m_isWinningBall) {
				std::cout << (GetOwnerTeam() == Team::BLUE ? "BLUE" : "RED") << " team wins! (Need to hook this up to winning a losing)";
				CGameManager::GetInstance()->TeamWon(GetOwnerTeam());
				CTeamsManager::GetInstance()->ResetScore(Team::BLUE);
				CTeamsManager::GetInstance()->ResetScore(Team::RED);
				CPostProcessing::GetInstance()->AddScreenShake(cmath::Abs(GetVelocity()*2.0f), sf::Vector2f{50.0f,50.0f}, 0.8f);
				CPostProcessing::GetInstance()->AddChromaAberration(0.002f, 0.5f);
			}
			else {
				CTeamsManager::GetInstance()->AddScore(GetOwnerTeam() == Team::BLUE ? Team::BLUE : Team::RED);
				CPostProcessing::GetInstance()->AddScreenShake(cmath::Abs(GetVelocity()/2.0f), sf::Vector2f{50.0f,50.0f}, 0.3f);
				CPostProcessing::GetInstance()->AddChromaAberration(0.001f, 0.3f);
			}

			didHit = true;

			if (m_parent) {
				std::vector<CBall*>::iterator it = std::find(m_parent->m_childBalls.begin(), m_parent->m_childBalls.end(), this);
				if (it != m_parent->m_childBalls.end()) {
					m_parent->m_childBalls.erase(it);
				}

				CObjectController::Destroy(this);
			}
			else {
				ResetBall();
			}

			break;

		case CBall::BallPower::Homing:
			break;

		case CBall::BallPower::Exploding:
			//if already hit, skip
			if (CheckAlreadyHit(_player)) return;

			CTeamsManager::GetInstance()->AddScore(GetOwnerTeam() == Team::BLUE ? Team::BLUE : Team::RED);
			ActivatePower();

			didHit = true;
			break;

		case CBall::BallPower::BulletHell:
			break;

		case CBall::BallPower::SuperFast:
			CTeamsManager::GetInstance()->AddScore(GetOwnerTeam() == Team::BLUE ? Team::BLUE : Team::RED);

			didHit = true;
			CPostProcessing::GetInstance()->AddScreenShake(cmath::Abs(GetVelocity()), sf::Vector2f{50.0f,50.0f}, 0.5f);
			CPostProcessing::GetInstance()->AddChromaAberration(0.0015f, 0.3f);

			ResetBall();
			break;

		default:
			break;
		}
	}

	if (didHit) {
		switch (_player->GetTeam())
		{
		case Team::RED:
			CGameManager::GetInstance()->WinningBall(Team::BLUE, 1);
			break;
		case Team::BLUE:
			CGameManager::GetInstance()->WinningBall(Team::RED, 1);
			break;
		default:
			break;
		}
		m_hurtSFX.play();
	}
}

/// <summary>
/// Checks if already hit player, otherwise add player to list of already hit
/// </summary>
/// <param name="_player"></param>
/// <returns></returns>
bool CBall::CheckAlreadyHit(CPlayer*& _player)
{
	//Check if ball has already hit player this reset
	if (std::find(m_hitPlayers.begin(), m_hitPlayers.end(), _player) != m_hitPlayers.end()) {
		return true;
	}
	else {
		m_hitPlayers.push_back(_player);
	}
	if (m_parent && std::find(m_parent->m_hitPlayers.begin(), m_parent->m_hitPlayers.end(), _player) != m_parent->m_hitPlayers.end()) {
		return true;
	}
	else {
		if (m_parent) m_parent->m_hitPlayers.push_back(_player);
	}

	return false;
}

/// <summary>
/// Bounce off of walls
/// <para>Author: Keane</para>
/// </summary>
void CBall::WallCollision()
{
	bool hitWall = false;

	if ((GetVelocity().x > 0 && GetPosition().x + GetSprite()->getGlobalBounds().width / 2.0f >= CResourceHolder::GetWindow()->getSize().x) ||
		(GetVelocity().x < 0 && GetPosition().x - GetSprite()->getGlobalBounds().width / 2.0f <= 0))
	{
		SetVelocity(sf::Vector2f(-m_velocity.x, m_velocity.y));
		hitWall = true;
	}

	if ((GetVelocity().y > 0 && GetPosition().y + GetSprite()->getGlobalBounds().height / 2.0f >= CResourceHolder::GetWindow()->getSize().y) ||
		(GetVelocity().y < 0 && GetPosition().y - GetSprite()->getGlobalBounds().height / 2.0f <= 0))
	{
		SetVelocity(sf::Vector2f(m_velocity.x, -m_velocity.y));
		hitWall = true;
	}

	switch (m_power)
	{
	case CBall::BallPower::None:
		break;

	case CBall::BallPower::Homing:
		if (HitMidline(Team::UNDECIDED)) {
			ActivatePower();
		}
		break;

	case CBall::BallPower::Exploding:
		break;

	case CBall::BallPower::BulletHell:
		if (HitMidline(Team::UNDECIDED)) {
			ActivatePower();
		}
		break;

	case CBall::BallPower::SuperFast:
		if (HitMidline(GetOwnerTeam() == Team::RED ? Team::BLUE : Team::RED))
		{
			SetVelocity(sf::Vector2f(-m_velocity.x, m_velocity.y));
			hitWall = true;
		}
		break;

	default:
		break;
	}

	if (hitWall) {
		m_throwStyle = ThrowStyle::Normal;
		m_wallbounceSFX.play();
		CPostProcessing::GetInstance()->AddScreenShake(cmath::Abs(GetVelocity()), sf::Vector2f{50.0f,50.0f}, 0.3f);
		CPostProcessing::GetInstance()->AddChromaAberration(0.001f, 0.3f);
	}
}

/// <summary>
/// Checks if the ball hits the midline from a specific side
/// </summary>
/// <param name="_onThisSide"></param>
/// <returns></returns>
bool CBall::HitMidline(Team _onThisSide)
{
	switch (_onThisSide)
	{
	case Team::UNDECIDED:
		if (abs(GetPosition().x - CResourceHolder::GetWindow()->getSize().x / 2.0f) <= GetSprite()->getGlobalBounds().width / 2.0f) return true;
		break;
	case Team::RED:
		if (GetVelocity().x > 0 && GetPosition().x + GetSprite()->getGlobalBounds().width / 2.0f >= CResourceHolder::GetWindow()->getSize().x / 2.0f) return true;
		break;
	case Team::BLUE:
		if (GetVelocity().x < 0 && GetPosition().x - GetSprite()->getGlobalBounds().width / 2.0f <= CResourceHolder::GetWindow()->getSize().x / 2.0f) return true;
		break;
	default:
		break;
	}

	return false;
}

#pragma endregion

void CBall::LateUpdate(float _fDeltaTime)
{

}