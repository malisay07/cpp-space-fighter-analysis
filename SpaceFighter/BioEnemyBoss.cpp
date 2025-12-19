#include "BioEnemyBoss.h"
#include "EnemyShip.h"
#include "Ship.h"
#include "Level.h"


BioEnemyBoss::BioEnemyBoss()
{
	SetSpeed(50);
	SetMaxHitPoints(20.0f);
	SetCollisionRadius(100);
}

void BioEnemyBoss::Initialize(const Vector2 position, const double delaySeconds)
{
	EnemyShip::Initialize(position, delaySeconds);
}

void BioEnemyBoss::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 7.5f;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

	}

	EnemyShip::Update(gameTime);
}


void BioEnemyBoss::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}