#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "CreateEnemies.h"
#include "CreatePlayer.h"
#include "CreateWall.h"
#include "GameObject.h"

inline void ReadLevelFromFile(vic::Scene* scene, const std::string& filename, PlayingState* playingState, int& nrOfEnemies, GameManager::PlayMode mode) {
    const float gridSize{ 30 };
    nrOfEnemies = 0;

    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }




    std::string line;
    int y = 0;

    int playerNr{ 0 };

    while (std::getline(file, line)) {
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            glm::vec2 pos{ x * gridSize , y * gridSize };

            char ch = line[x];
            switch (ch) {
            case '#':
                CreateWall(scene, pos);
                break;
            case 'P':
                if(playerNr == 0
                    || (playerNr == 1 && mode == GameManager::PlayMode::multiplayer))
                {
                    CreatePlayer(scene, pos, 0, playingState);
                    playerNr++;
                }
                else if((playerNr == 1 && mode == GameManager::PlayMode::versus))
                {
                    CreatePlayer(scene, pos, 1, playingState);
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
            default:
                break;
            }
        }
        y++;
    }

    file.close();
}