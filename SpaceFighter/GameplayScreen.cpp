
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "Level02.h"
#include "Level03.h"


GameplayScreen::GameplayScreen(const int levelIndex)
    : m_levelIndex(levelIndex), m_pLevel(nullptr), m_pResourceManager(nullptr)
{
    SetTransitionInTime(1.0f);
    SetTransitionOutTime(3.0f);

    // Return to main menu when screen is removed
    SetOnRemove([this]() { AddScreen(new MainMenuScreen()); });

    Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);

}

void GameplayScreen::LoadLevel(const int levelIndex)
{
    // Delete previous level if it exists
    if (m_pLevel)
    {
        delete m_pLevel;
        m_pLevel = nullptr;
    }

    // Create new level based on index
    switch (levelIndex)
    {
    case 0: m_pLevel = new Level01(); break;
    case 1: m_pLevel = new Level02(); break;
    case 2: m_pLevel = new Level03(); break;
    default:
        std::cerr << "Warning: Invalid level index " << levelIndex
            << ". Loading Level01 as fallback.\n";
        m_pLevel = new Level01();
        break;
    }

    // Safety check
    if (!m_pLevel)
    {
        throw std::runtime_error("Failed to create a level!");
    }

    // Assign the gameplay screen pointer
    m_pLevel->SetGameplayScreen(this);

    // Load level content safely
    if (m_pResourceManager)
    {
        m_pLevel->LoadContent(*m_pResourceManager);
    }
    else
    {
        throw std::runtime_error("ResourceManager not set before loading level!");
    }
}


void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}

void GameplayScreen::AdvanceToNextLevel()
{
    if (m_isAdvancing)
        return; 

    m_isAdvancing = true;

    m_levelIndex++;

    std::cout << "GameplayScreen::AdvanceToNextLevel()\n";

    SetOnRemove([this]()
        {
            AddScreen(new GameplayScreen(m_levelIndex));
        });

    Exit();
}
