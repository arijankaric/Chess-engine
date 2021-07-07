#pragma once

#include <material.hpp>

class Bishop : public Material {
    public:
    Bishop(int file, int rank, bool colored);
    ~Bishop();
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML();
    char getTypeOfMaterial();
    bool isEnemy(Material* target);
    bool isColored();
    private:
};