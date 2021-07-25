#pragma once

#include <material.hpp>

class Bishop : public Material {
    public:
    Bishop(int file, int rank, bool colored);
    ~Bishop();
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML() const;
    int getint() const;
    bool isEnemy(Material* target) const;
    bool isColored() const;
    private:
};