#include <queen.hpp>

Queen::Queen(int file, int rank, bool colored) : Material(file, rank, colored) {}

// void Queen::projectAttack(Chessboard *mainBoard)
// {
//     rookAttack(file_, rank_, mainBoard);
//     bishopAttack(file_, rank_, mainBoard);
// }

std::string Queen::getHTML()
{
    return colored_ ? "&#9813;" : "&#9819;";
}

char Queen::getTypeOfMaterial(){
    return colored_ ? 'Q' : 'q';
}

bool Queen::isColored() {
    return colored_;
}

bool Queen::isEnemy(Material *target)
{
    if (target->isColored() == colored_)
        return false;
    return true;
}