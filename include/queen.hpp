#pragma once

#include <material.hpp>

class Queen : public Material {
    public:
    Queen(int file, int rank, bool colored);
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML() const;
    int getint() const;
    char getchar() const;
    bool isEnemy(Material* target) const;
    bool isColored() const;
    private:
};