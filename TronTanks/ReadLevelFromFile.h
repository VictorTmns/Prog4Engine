#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "CreateDiamond.h"
#include "CreateEnemies.h"
#include "CreatePlayer.h"
#include "CreateWall.h"
#include "GameObject.h"

inline void ReadLevelFromFile(vic::Scene* scene, const glm::vec2& topLeft, const std::string& filename, PlayingState* playingState, GameManager::PlayMode mode, int& nrOfEnemies, glm::vec2& levelSize) {
    const float gridSize{ 30 };
    nrOfEnemies = 0;
    levelSize.x = 0;
    levelSize.y = 0;


    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::runtime_error("couldn't find level file at: " + filename);
    }




    std::string line;
    int y = 0;

    int playerNr{ 0 };

    while (std::getline(file, line)) {
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            glm::vec2 pos{ x * gridSize  + topLeft.x, y * gridSize  + topLeft.y};


            char ch = line[x];
            switch (ch) {
            case '#':
                CreateWall(scene, pos);
                break;
            case 'P':
                if(playerNr == 0
                    || (playerNr == 1 && mode == GameManager::PlayMode::multiplayer))
                {
                    CreatePlayer(scene, pos, 0, playingState, true);
                    playerNr++;
                }
                else if((playerNr == 1 && mode == GameManager::PlayMode::versus))
                {
                    CreatePlayer(scene, pos, 1, playingState, false);
                    playerNr++;

                }
                break;
            case 'E':
                CreateEnemy(scene, pos, false, playingState);
                nrOfEnemies++;
                break;
            case 'R':
                CreateEnemy(scene, pos, true, playingState);
                nrOfEnemies++;
                break;
            	case 'D':
                CreateDiamond(scene, pos);
                nrOfEnemies++;
                break;
            default:
                break;
            }
        }
        y++;
        if (static_cast<float>(line.size()) > levelSize.x)
            levelSize.x = static_cast<float>(line.size());
    }
    levelSize.y = static_cast<float>(y);


    levelSize *= gridSize;
    file.close();
}