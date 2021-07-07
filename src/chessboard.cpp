#include <chessboard.hpp>
#include <iostream>

Chessboard::Chessboard()
{
    std::cout << NUMOFSQUARES << std::endl;
    init();
}
Chessboard::~Chessboard() {}
// If we use this method for attack it will be a tad bit slower since we'll need to traverse the whole chessboard
// And how do we check is the attacking material visible, probably looping like we did with the opposite method
void Chessboard::transformSquare(int file, int rank, std::function<void(Square *)> transform)
{
    transform(&squares[file][rank]);
}
void Chessboard::setSquare(int file, int rank, Material *chessman)
{
    if (chessman)
        std::cout << "Inside setSquare file: " << file << " rank: " << rank << " typeOfMaterial: " << chessman->getTypeOfMaterial() << std::endl;
    else
        std::cout << "Inside setSquare file: " << file << " rank: " << rank << " typeOfMaterial: "
                  << "none" << std::endl;

    squares[file][rank].setMaterial(chessman);
}

Square &Chessboard::getSquare(int file, int rank)
{
        return squares[file][rank];
}

bool Chessboard::validAttacker(int file, int rank)
{
    std::cout << "Inside validAttacker File: " << file << " Rank: " << rank << std::endl;
    if (checkForRange(file, rank) && squares[file][rank].getMaterial())
    {
        std::cout << "Inside validAttacker True" << std::endl;

        return true;
    }
    std::cout << "Inside validAttacker False" << std::endl;

    return false;
}

// void Chessboard::attackingSquare(int file, int rank)
// {
//     Material *attackingMaterial = squares[file][rank].getMaterial();
//     attackingMaterial->projectAttack(this);
// }
// We need to account for En passant target square
bool Chessboard::attackSquare(int file, int rank, Material *attacker)
{
    if (checkForRange(file, rank))
    {
        std::cout << "Attacking square file: " << file << " rank: " << rank << std::endl;
        return squares[file][rank].attackSquare(attacker);
    }
    return false;
}
void Chessboard::init()
{
    bool colored = false;
    for (int files = 0; files < FILES; ++files)
    {
        for (int ranks = 0; ranks < RANKS; ++ranks)
        {
            squares[files][ranks].init(files, ranks, colored);
            //squares2[files*ranks] = new Square();
            colored = !colored;
        }
        colored = !colored;
    }
}

// Returns false if out of range, true if in range, kinda not intuitive, should change that
bool Chessboard::checkForRange(int file, int rank)
{
    std::cout << "Inside checkForRange\n";
    return (file < 0 || file >= FILES || rank < 0 || rank >= RANKS) ? false : true;
}

void Chessboard::convertPosition(int &rank, int &file)
{
    file -= 49;
    rank -= 97;
}
