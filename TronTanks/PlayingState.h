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

    void HandleEnemyDiedEvent(const vic::BaseComponent* enemyLogic);

    std::vector<std::pair<vic::Scene*, std::string>> m_Levels;

    int m_Score = 0;
    int m_CurrentLevel;
    int m_EnemiesRemaining;

    GameManager::PlayMode m_Mode;
};

