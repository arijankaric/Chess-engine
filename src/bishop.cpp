#include <bishop.hpp>

Bishop::Bishop(int file, int rank, bool colored) : Material(file, rank, colored) {}
Bishop::~Bishop() {}
// void Bishop::projectAttack(Chessboard *mainBoard)
// {
//     bishopAttack(file_, rank_, mainBoard);
// }
std::string Bishop::getHTML()
{
    return colored_ ? "&#9815;" : "&#9821;";
}

char Bishop::getTypeOfMaterial()
{
    return colored_ ? 'B' : 'b';
}

bool Bishop::isColored() {
    return colored_;
}

bool Bishop::isEnemy(Material *target)
{
    if (target->isColored() == colored_)
        return false;
    return true;
}
