#include <pawn.hpp>
#include <iostream>

// See difference between class Pawn : virtual public Material and
// class Pawn : public Material

// void Pawn::projectAttack(Chessboard& mainBoard)
// {
//     if (colored_)
//         forward(file_, rank_, mainBoard);
//     else
//         backward(file_, rank_, mainBoard);
// }

std::string Pawn::getHTML() const
{
    return colored_ ? "&#9817;" : "&#9823;";
}

int Pawn::getint() const
{
    // std::cout << "colored_: " << colored_ << std::endl;
    return colored_ ? whitePawn : blackPawn;
}

Pawn::Pawn(int file, int rank, bool colored, bool facing) : Material(file, rank, colored), facing_{facing} {}

bool Pawn::isColored() const
{
    return colored_;
}

bool Pawn::isEnemy(Material *target) const
{
    if (target->isColored() == colored_)
        return false;
    return true;
}
