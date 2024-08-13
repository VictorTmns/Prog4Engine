#pragma once
#include "BaseComponent.h"
#include "BaseState.h"
#include "Scene.h"
#include "TextRenderComponent.h"

class HighScoreState final :
    public BaseState 
{
public:
	HighScoreState(int score);
	~HighScoreState() override = default;
	std::unique_ptr<BaseState> Update() override;

private:
	void LoadScores();
	void ShowHighScoreList();
	void CheckForInput();
private:
	struct DescendingCompare {
		bool operator()(int left, int right) const {
			return left > right;
		}
	};

	std::multimap <int, std::string, DescendingCompare> m_HighScores;

	std::string m_HighScorePath;

	vic::TextRenderComponent* m_NameRender;
	vic::Scene* m_Scene;
	std::string m_Name;

	int m_Score;

	bool m_NameComplete = false;
};

