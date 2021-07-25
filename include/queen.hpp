#pragma once

#include <material.hpp>

class Queen : public Material {
    public:
    Queen(int file, int rank, bool colored);
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML();
    int getint();
    bool isEnemy(Material* target);
    bool isColored();
    private:
};