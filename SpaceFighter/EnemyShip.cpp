
#include "EnemyShip.h"
#include "Level.h"

EnemyShip::EnemyShip()
{
	SetMaxHitPoints(1); 
	SetCollisionRadius(25);
}


void EnemyShip::Update(const GameTime& gameTime)
{
	if (m_delaySeconds > 0)
	{
		m_delaySeconds -= gameTime.GetElapsedTime();

		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();
		}
	}

	if (IsActive())
	{
		m_activationSeconds += gameTime.GetElapsedTime();

		if (m_activationSeconds > 2 && !IsOnScreen())
		{
			Deactivate();

			if (!m_reportedDead && m_pLevel)
			{
				m_reportedDead = true;
				std::cout << "Enemy left screen, counting as destroyed\n";
				m_pLevel->OnEnemyDestroyed();
			}
		}
	}

	Ship::Update(gameTime);
}


void EnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{

	SetPosition(position);
	m_delaySeconds = delaySeconds;

	Ship::Initialize();

	
}


void EnemyShip::Hit(const float damage)
{
	std::cout << "EnemyShip::Hit called for " << GetIndex()
		<< ", damage: " << damage << std::endl;

	if (!IsActive() || m_reportedDead)
		return;

	m_health -= damage;

	if (m_health <= 0)
	{
		Deactivate();

		m_reportedDead = true;

		std::cout << "EnemyShip destroyed: " << GetIndex() << std::endl;
		
		if (!m_pLevel)
		{
			std::cout << "ERROR: Enemy has no level pointer!\n";
			return;
		}

		m_pLevel->SpawnExplosion(this);
		m_pLevel->OnEnemyDestroyed();
	}
}