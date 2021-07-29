#include <rook.hpp>

Rook::Rook(int file, int rank, bool colored) : Material(file, rank, colored) {}
// We could project attack in chessboard or game by getting an anonymous function from the material
// Or we could give chessboard to material to project its attack on the chessboard
// What's better and in which situation and why?
// void Rook::projectAttack(Chessboard *mainBoard)
// {
//     rookAttack(file_, rank_, mainBoard);
// }
// But we end up with basically the same stuff
// Bad implementation I guess
// Fix this somehow
// std::function<void(Chessboard *)> Rook::projectAttackFunction()
// {
//     return [this](Chessboard *mainBoard)
//     {
//         verticalUp(file_, rank_, mainBoard);
//         verticalDown(file_, rank_, mainBoard);
//         horizontalLeft(file_, rank_, mainBoard);
//         horizontalRight(file_, rank_, mainBoard);
//     };
// }

std::string Rook::getHTML() const
{
    return colored_ ? "&#9814;" : "&#9820;";
}

int Rook::getint() const{
    return colored_ ? whiteRook : blackRook;
}

bool Rook::isColored() const{
    return colored_;
}

bool Rook::isEnemy(Material *target) const
{
    if (target->isColored() == colored_)
        return false;
    return true;
}

char Rook::getchar() const
{
    return colored_ ? 'R' : 'r';
}