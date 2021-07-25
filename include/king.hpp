#pragma once

#include <material.hpp>

class King : public Material {
    public:
    King(int file, int rank, bool colored);
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML();
    int getint();
    bool isEnemy(Material* target);
    bool isColored();
    private:
};