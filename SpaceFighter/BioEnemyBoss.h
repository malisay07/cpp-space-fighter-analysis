
#pragma once

#include "EnemyShip.h"

/** @brief Represents an enemy ship that is biological in nature. */
class BioEnemyBoss : public EnemyShip
{

public:

	/** @brief Creates a new instance of BioEnemyShip. */
	BioEnemyBoss();
	virtual ~BioEnemyBoss() {}

	/** @brief Initializes the enemy ship.
			@param position The starting position of the enemy ship.
			@param delaySeconds The delay before the enemy ship activates. */
	virtual void Initialize(const Vector2 position, const double delaySeconds);

	/** @brief Sets the texture that will be used to render the enemy ship.
		@param pTexture A pointer to the texture. */
	virtual void SetTexture(Texture* pBoss) { m_pTexture = pBoss; }

	/** @brief Updates the enemy ship.
		@param gameTime A reference to the game time object. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Draws the enemy ship.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);


private:

	Texture* m_pTexture = nullptr;
	//Hit flash timer
	float m_hitFlashTimer = 0.0f;

};
