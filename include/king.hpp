#pragma once

#include <material.hpp>

class King : public Material {
    public:
    King(int file, int rank, bool colored);
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML() const;
    int getint() const;
    bool isEnemy(Material* target) const;
    bool isColored() const;
    private:
};