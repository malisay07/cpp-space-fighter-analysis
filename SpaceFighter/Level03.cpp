

#include "Level03.h"
#include "BioEnemyShip.h"


void Level03::LoadContent(ResourceManager& resourceManager)
{
	Level::LoadContent(resourceManager);

	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\Asteroid2.png");

	const int COUNT = 23;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55, .6, 0.7
	};

	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.1
	};

	float delay = 3.0; // start delay
	//Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += (float)delays[i];
		Vector2 position(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		BioEnemyShip* pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);
	}

	SetBackground(resourceManager.Load<Texture>("Textures\\Starry_night_Layer_8.png"));

	Level::LoadContent(resourceManager);
}

