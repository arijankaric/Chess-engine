#pragma once

#include <material.hpp>

class Rook : public Material
{
public:
    Rook(int file, int rank, bool colored);
    // We could project attack in chessboard or game by getting an anonymous function from the material
    // Or we could give chessboard to material to project its attack on the chessboard
    // What's better and in which situation and why?
    // void projectAttack(Chessboard& mainBoard);
    // But we end up with basically the same stuff
    // Bad implementation I guess
    // Fix this somehow
    // std::function<void(Chessboard *)> projectAttackFunction();

    std::string getHTML() const;
    int getint() const;
    char getchar() const;
    bool isEnemy(Material* target) const;
    bool isColored() const;
    private:
};