#pragma once
#include "BaseState.h"
#include "MenuState.h"
#include "Observer.h"
#include "Scene.h"
#include "GameManager.h"

class PlayingState : public BaseState, public vic::Observer
{
public:
    PlayingState(GameManager::PlayMode mode);
    ~PlayingState();

    std::unique_ptr<BaseState> Update() override;
    void Notify(Event event, const vic::BaseComponent* subject) override;

private:
    void IncrementLevel();
    void SetLevel(int idx);
    void CleanupLevel();

    void HandleEnemyDiedEvent(const vic::BaseComponent* enemyLogic);

    void SetRandomPlace(const vic::BaseComponent* component);

private:
    std::vector<std::pair<vic::Scene*, std::string>> m_Levels;

    vic::Scene* m_Hud;

    glm::vec2 m_LevelTopLeft;
    glm::vec2 m_LevelDimension;

    vic::TextRenderComponent* m_ScoreRenderComponent;

    int m_Score = 0;
    int m_LivesLeft = 3;
    int m_CurrentLevel;
    int m_EnemiesRemaining;

    bool m_ShowHighScore;
    bool m_ReloadLevel;

    GameManager::PlayMode m_Mode;
};

