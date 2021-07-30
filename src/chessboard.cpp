#include <chessboard.hpp>
#include <iostream>
#include <fstream>

Chessboard::Chessboard()
{
    // std::cout << NUMOFSQUARES << std::endl;
    init();
}
Chessboard::~Chessboard() {}
// If we use this method for attack it will be a tad bit slower since we'll need to traverse the whole chessboard
// And how do we check is the attacking material visible, probably looping like we did with the opposite method
void Chessboard::transformSquare(int file, int rank, std::function<void(Square *)> transform)
{
    transform(&squares[file][rank]);
}

void Chessboard::setEnPassant(int file, int rank)
{
    // std::cout << "setting EnPassant on file: " << file << " rank: " << rank << std::endl;
    squares[file][rank].setEnPassant();
}

void Chessboard::setSquare(int file, int rank, Material *chessman)
{
    // if (chessman)
    //     std::cout << "Inside setSquare file: " << file << " rank: " << rank << " int: " << chessman->getint() << std::endl;
    // else
    //     std::cout << "Inside setSquare file: " << file << " rank: " << rank << " int: "
    //               << "none" << std::endl;

    squares[file][rank].setMaterial(chessman);
}

const Square &Chessboard::getSquare(int file, int rank) const
{
    if(checkForRange(file, rank))
        return squares[file][rank];
    
    std::cout << "out of range getSquare\n";
    exit(1);
}

bool Chessboard::validAttacker(int file, int rank, bool color)
{
    // std::cout << color << std::endl;
    // std::cout << "Inside validAttacker File: " << file << " Rank: " << rank << std::endl;
    if (checkForRange(file, rank) && squares[file][rank].isThereMaterial())
    {
        if(squares[file][rank].getMaterial()->isColored() != color)
        {

            std::cout << "It's not your move yet\n";
            return false;
        }
        // std::cout << "Inside validAttacker True" << std::endl;
        return true;
    }
    // std::cout << "Inside validAttacker False" << std::endl;

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
        // std::cout << "Attacking square file: " << file << " rank: " << rank << std::endl;
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
bool Chessboard::checkForRange(int file, int rank) const
{
    // std::cout << "Inside checkForRange\n";
    return (file < 0 || file >= FILES || rank < 0 || rank >= RANKS) ? false : true;
}

void Chessboard::convertPosition(int &rank, int &file)
{
    file -= 49;
    rank -= 97;
}

void Chessboard::generateHTML(const std::string outputPath)
{
    std::ofstream out_file;
    out_file.open(outputPath, std::ios_base::app);

    out_file << "<body>" << std::endl;
    out_file << "<TABLE class=\"chessboard\" style=\"width:800px;height:800px;\" border=5 cellspacing=0>" << std::endl;
    for (int i = 7; i >= 0; --i)
    {
        out_file << "<TR>" << std::endl;
        for (int j = 0; j < RANKS; ++j)
        {
            out_file << squares[i][j].getHTML() << std::endl;
        }
        out_file << "</TR>" << std::endl;
    }
    out_file << "</TABLE>" << std::endl;
    out_file << "</body>" << std::endl;
    out_file << "</html>" << std::endl;
    out_file.close();
}

bool Chessboard::isValidEnemy(int file, int rank, int typeOfMat) const
{
    if (!checkForRange(file, rank) || !squares[file][rank].isThereMaterial())
        return false;
    Material *mat = squares[file][rank].getMaterial();
    // if(file == 4 && rank == 2)
    // std::cout << "mat: " << mat->getint() << "typeOfMat:" << typeOfMat << "&: " << (mat->getint() & typeOfMat) << std::endl;
    if (mat->getint() & typeOfMat)
    {
        return true;
    }
    return false;
}

bool Chessboard::isEmpty(int file, int rank) const
{
    return !squares[file][rank].isThereMaterial();
}

void Chessboard::moveMaterial(int file, int rank, Material *mat)
{
    squares[mat->file_][mat->rank_].setMaterial(nullptr);
    mat->file_ = file;
    mat->rank_ = rank;
    squares[file][rank].setMaterial(mat);
}

void Chessboard::removeMaterial(int file, int rank)
{
    squares[file][rank].removeMaterial();
}

bool Chessboard::isEnPassant(int file, int rank) const
{
    return squares[file][rank].isEnPassant();
}

void Chessboard::invalidateAttacked()
{
    for(int i = 0; i < FILES; ++i)
    {
        for(int j = 0; j < RANKS; ++j)
        {
            squares[i][j].setAttacked(false);
        }
    }
}

bool Chessboard::anyAttackedSquare() const
{
    for(int i = 0; i < FILES; ++i)
    {
        for(int j = 0; j < RANKS; ++j)
        {
            if(squares[i][j].isAttacked())
                return true;
        }
    }
    return false;
}

void Chessboard::clearEnPassant(int file, int rank)
{
    squares[file][rank].clearEnPassant();
}

bool Chessboard::isAttacked(int file, int rank)
{
    return squares[file][rank].isAttacked();
}