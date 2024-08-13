#include "HighScoreState.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "BaseComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "TextRenderComponent.h"

HighScoreState::HighScoreState(int score)
	: m_HighScorePath{"../Data/Tron/HighScore.txt"}
{
    m_Score = score;
    LoadScores();


	m_Scene = vic::SceneManager::GetInstance().CreateScene("highScore");

	vic::Font* textFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 50);

	vic::GameObject& scoreText = m_Scene->CreateGameObject();
    scoreText.AddComponent<vic::TextRenderComponent>(textFont, "score: " + std::to_string(m_Score));
    scoreText.GetTransform().SetWorldPosition(320, 20);

	vic::GameObject& inputText = m_Scene->CreateGameObject();
	inputText.AddComponent<vic::TextRenderComponent>(textFont, "enter your name + ENTER");
	inputText.GetTransform().SetWorldPosition(320, 150);

	vic::GameObject& inputName = m_Scene->CreateGameObject();
    m_NameRender= inputName.AddComponent<vic::TextRenderComponent>(textFont, "");
    inputName.GetTransform().SetWorldPosition(320, 200);

}

std::unique_ptr<BaseState> HighScoreState::Update()
{
	if (m_NameComplete != true)
	{
		m_NameRender->SetText(m_Name);
		CheckForInput();
	}

	return nullptr;
}

void HighScoreState::LoadScores()
{
    std::ifstream file(m_HighScorePath);

    if (!file.is_open()) {
        throw std::runtime_error("can't find highscore list");
    }

    std::string line{};
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string name;
        int score;

        if (lineStream >> name >> score) {
            m_HighScores.emplace(score, name);
        }
    }

    file.close();
}

void HighScoreState::ShowHighScoreList()
{

    m_HighScores.emplace(m_Score, m_Name);
    m_NameComplete = true;
    m_Scene->DeleteAll();



    vic::Font* textFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 30);
    std::ofstream file(m_HighScorePath);
    file.clear();

    int i{ 0 };
    for (auto& highScore : m_HighScores)
    {
        i++;
        if(i > 10)
            break;

        file << highScore.second << " " << highScore.first << std::endl;


        vic::GameObject& go = m_Scene->CreateGameObject();
        go.GetTransform().SetWorldPosition(320, static_cast<float>(i) * 40 + 30);
        go.AddComponent<vic::TextRenderComponent>(textFont, highScore.second + ": " + std::to_string(highScore.first));
    }

    file.close();
}

void HighScoreState::CheckForInput()
{
    //This is dumb
    if (vic::InputManager::GetInstance().KeyDown(SDLK_a))
        m_Name.append("a");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_b))
        m_Name.append("b");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_c))
        m_Name.append("c");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_d))
        m_Name.append("d");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_e))
        m_Name.append("e");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_f))
        m_Name.append("f");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_g))
        m_Name.append("g");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_h))
        m_Name.append("h");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_i))
        m_Name.append("i");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_j))
        m_Name.append("j");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_k))
        m_Name.append("k");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_l))
        m_Name.append("l");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_m))
        m_Name.append("m");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_n))
        m_Name.append("n");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_o))
        m_Name.append("o");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_p))
        m_Name.append("p");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_q))
        m_Name.append("q");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_r))
        m_Name.append("r");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_s))
        m_Name.append("s");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_t))
        m_Name.append("t");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_u))
        m_Name.append("u");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_v))
        m_Name.append("v");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_w))
        m_Name.append("w");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_x))
        m_Name.append("x");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_y))
        m_Name.append("y");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_z))
        m_Name.append("z");
    if (vic::InputManager::GetInstance().KeyDown(SDLK_RETURN))
        m_Name.pop_back();
    if (vic::InputManager::GetInstance().KeyDown(SDLK_RETURN))
        ShowHighScoreList();

}
