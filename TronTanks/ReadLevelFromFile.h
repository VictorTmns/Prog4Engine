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

void ReadLevelFromFile(vic::Scene* scene, const std::string& filename) {
    const float gridSize{ 30 };


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
                CreatePlayer(scene, pos, 0);
                break;
            case 'E':
                CreateEnemy(scene, pos, false);
                break;
            default:
                break;
            }
        }
        y++;
    }

    file.close();
}