#include <queen.hpp>

Queen::Queen(int file, int rank, bool colored) : Material(file, rank, colored) {}

// void Queen::projectAttack(Chessboard *mainBoard)
// {
//     rookAttack(file_, rank_, mainBoard);
//     bishopAttack(file_, rank_, mainBoard);
// }

std::string Queen::getHTML() const
{
    return colored_ ? "&#9813;" : "&#9819;";
}

int Queen::getint() const
{
    return colored_ ? whiteQueen : blackQueen;
}

bool Queen::isColored() const
{
    return colored_;
}

bool Queen::isEnemy(Material *target) const
{
    if (target->isColored() == colored_)
        return false;
    return true;
}