#ifndef __CBall_H__
#define __CBall_H__

#include "EasySFML.h"
#include "CGamepad.h"
#include "CResourceHolder.h"
#include "CTeamsManager.h"
#include "CGameManager.h"
#include "CPlayer.h"
#include "CPostProcessing.h"
#include <memory>


class CBall : public CGameObject
{
public:
	enum class BallPower {
		None,
		Homing,
		Exploding,
		BulletHell,
	};

	CBall();
	~CBall();

	static std::vector<CBall*> GetAllBalls() { return m_allBalls; };
	static CBall* GetClosestBall(sf::Vector2f _point);

	void SetSprite(std::string _texName) { m_sprite->setTexture(*CResourceHolder::GetTexture(_texName)); }
	sf::Sprite* GetSprite() { return(m_sprite); }

	void SetPosition(sf::Vector2f _pos) { GetSprite()->setPosition(_pos); }
	sf::Vector2f GetPosition() { return GetSprite()->getPosition(); }

	void SetVelocity(sf::Vector2f _vel) { m_velocity = _vel; }
	sf::Vector2f GetVelocity() { return m_velocity; }

	void SetAcceleration(sf::Vector2f _acc) { m_acceleration = _acc; }
	sf::Vector2f GetAcceleration() { return m_acceleration; }

	void SetPickupRadius(float _rad) { m_pickupRadius = _rad; };
	float GetPickupRadius() { return m_pickupRadius; };

	void SetCatchRadius(float _rad) { m_catchRadius = _rad; };
	float GetCatchRadius() { return m_catchRadius; };

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void PerformThrowStyle();
	void PerformPower();

	void TryPickup(CPlayer* _player);
	void TryCatch(CPlayer* _player);
	void Throw(float _speed = 20.0f);

	void ResetBall();

	void AllPlayerInteractions();
	void SpecificPlayerInteractions(CPlayer* _player);

	bool IsHeld() { return (m_holder != nullptr);  }
	CPlayer* GetHolder() { return m_holder; };

	Team GetOwnerTeam() { return m_ownerTeam; };

private:
	static std::vector<CBall*> m_allBalls;

	void AllPlayerCollision();
	void SpecificPlayerCollision(CPlayer* _player);
	
	void SetOwnerTeam(Team _team);
	void UpdateVisuals();

	void ForcePickup(CPlayer* _player);
	void ForceCatch(CPlayer* _player);
	
	void WallCollision();

	sf::Sprite* m_sprite = new sf::Sprite();

	//Styles/Power
	ThrowStyle m_throwStyle = ThrowStyle::Fastball;
	BallPower m_power = BallPower::None;

	std::vector<CBall*> m_childBalls;
	float m_powerActivationTime = -INFINITY;
	float m_powerDuration = -INFINITY;

	//Movement
	sf::Vector2f m_initialDirection = sf::Vector2f(0, 0);
	sf::Vector2f m_velocity = sf::Vector2f(0,0);
	sf::Vector2f m_acceleration = sf::Vector2f(0, 0);

	//Pickup
	bool m_canPickup = true;
	float m_pickupRadius = 50.0f;
	float m_catchRadius = 100.0f;

	bool m_isWinningBall = false;

	Team m_ownerTeam = Team::UNDECIDED;
	CPlayer* m_holder = nullptr;

	sf::Sound m_wallbounceSFX, m_explodeSFX, m_goldenStarSFX, m_powerupSFX;
};

#endif // __CBall_H__