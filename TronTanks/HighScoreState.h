#pragma once
#include "BaseState.h"
class HighScoreState final :
    public BaseState 
{
public:
	HighScoreState(int score);
	std::unique_ptr<BaseState> Update() override;
};

