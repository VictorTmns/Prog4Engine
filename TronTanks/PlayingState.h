#pragma once
#include "BaseState.h"
#include "Observer.h"
#include "Scene.h"

class PlayingState : public BaseState, public vic::Observer
{
public:
    PlayingState();

    void Update() override;
    void Notify(Event event, const vic::BaseComponent* subject) override;

private:
    void IncrementLevel();
    void SetLevel(int idx);

    void HandleEnemyDiedEvent(const vic::BaseComponent* enemyLogic);

    std::vector<std::pair<vic::Scene*, std::string>> m_Levels;
    int m_Score = 0;

    int m_CurrentLevel;

    int m_EnemiesRemaining;
};

