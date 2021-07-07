#include <knight.hpp>

Knight::Knight(int file, int rank, bool colored) : Material(file, rank, colored) {}

// void Knight::projectAttack(Chessboard *mainBoard)
// {
//     jumpingAttack(file_, rank_, mainBoard);
// }

std::string Knight::getHTML()
{
    return colored_ ? "&#9816;" : "&#9822;";
}

char Knight::getTypeOfMaterial(){
    return colored_ ? 'N' : 'n';
}

bool Knight::isColored() {
    return colored_;
}

bool Knight::isEnemy(Material *target)
{
    if (target->isColored() == colored_)
        return false;
    return true;
}