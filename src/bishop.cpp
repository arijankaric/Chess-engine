#include <bishop.hpp>

Bishop::Bishop(int file, int rank, bool colored) : Material(file, rank, colored) {}
Bishop::~Bishop() {}
// void Bishop::projectAttack(Chessboard *mainBoard)
// {
//     bishopAttack(file_, rank_, mainBoard);
// }
std::string Bishop::getHTML() const
{
    return colored_ ? "&#9815;" : "&#9821;";
}

int Bishop::getint() const
{
    return colored_ ? whiteBishop : blackBishop;
}

bool Bishop::isColored() const
{
    return colored_;
}

bool Bishop::isEnemy(Material *target) const
{
    if (target->isColored() == colored_)
        return false;
    return true;
}

char Bishop::getchar() const
{
    return colored_ ? 'B' : 'b';
}