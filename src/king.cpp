#include <king.hpp>

King::King(int file, int rank, bool colored) : Material(file, rank, colored) {}

// Need to figure out how to make squares/material communicate with one another
// Probably actors, but how do I implement it without actors and sendMsg/rcvMsg
// void King::projectAttack(Chessboard *mainBoard)
// {
//     allAround(file_, rank_, mainBoard);
// }

std::string King::getHTML()
{
    return colored_ ? "&#9812;" : "&#9818;";
}

bool King::isColored()
{
    return colored_;
}

bool King::isEnemy(Material *target)
{
    if (target->isColored() == colored_)
        return false;
    return true;
}

char King::getTypeOfMaterial()
{
    return colored_ ? 'K' : 'k';
}
