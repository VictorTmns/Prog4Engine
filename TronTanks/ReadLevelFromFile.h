﻿#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "CreateEnemies.h"
#include "CreatePlayer.h"
#include "CreateWall.h"
#include "GameObject.h"

inline void ReadLevelFromFile(vic::Scene* scene, const std::string& filename, PlayingState* playingState, int& nrOfEnemies) {
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

    while (std::getline(file, line)) {
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            glm::vec2 pos{ x * gridSize , y * gridSize };

            char ch = line[x];
            switch (ch) {
            case '#':
                CreateWall(scene, pos);
                break;
            case 'P':
                CreatePlayer(scene, pos, 0, playingState);
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