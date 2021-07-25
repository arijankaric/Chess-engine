#pragma once

#include <material.hpp>

class Knight : public Material
{
public:
    Knight(int file, int rank, bool colored);
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML();
    int getint();
    bool isEnemy(Material* target);
    bool isColored();
private:
};