#include <knight.hpp>

Knight::Knight(int file, int rank, bool colored) : Material(file, rank, colored) {}

// void Knight::projectAttack(Chessboard *mainBoard)
// {
//     jumpingAttack(file_, rank_, mainBoard);
// }

std::string Knight::getHTML() const
{
    return colored_ ? "&#9816;" : "&#9822;";
}

int Knight::getint() const
{
    return colored_ ? whiteKnight : blackKnight;
}

bool Knight::isColored() const
{
    return colored_;
}

bool Knight::isEnemy(Material *target) const
{
    if (target->isColored() == colored_)
        return false;
    return true;
}

char Knight::getchar() const
{
    return colored_ ? 'N' : 'n';
}