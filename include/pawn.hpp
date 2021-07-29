#pragma once

#include <material.hpp>


// See difference between class Pawn : virtual public Material and
// class Pawn : public Material

class Pawn : public Material
{
public:
    // void projectAttack(Chessboard& mainBoard);
    std::string getHTML() const;
    Pawn(int file, int rank, bool colored, bool facing);
    int getint() const;
    char getchar() const;
    bool isEnemy(Material* target) const;
    bool isColored() const;
private:
    bool facing_; // facing downwards or upwards, true - white/upwards, false - black/downwards
};