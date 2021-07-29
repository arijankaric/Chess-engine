#include <square.hpp>
#include <iostream>

Square::Square() = default;
Square::Square(bool, char, char, Material *)
{
}

Square::~Square()
{

    // static int num=0;
    // std::cout << file_ << " " << rank_ << " " << ++num << std::endl;
    // std::cout << "delete chessman\n";
    // delete chessman_;
}

// Square& Square::operator=(const Square& o)
// {
//     if(chessman_ != nullptr)
//         delete chessman_;
//     chessman_ = createMaterial(o.chessman_->getint());
//     colored_ = o.colored_;
//     file_ = o.file_;
//     rank_ = o.rank_;
//     attacked_ = o.attacked_;
//     enPassant_ = o.enPassant_;
// }

// Material* Square::createMaterial(int typeOfMaterial)
// {
//     Material *materialPtr;
//     switch (typeOfMaterial)
//     {
//     case blackRook:
//         materialPtr = new Rook(file, rank, false);
//         break;
//     case blackKnight:
//         materialPtr = new Knight(file, rank, false);
//         break;
//     case blackBishop:
//         materialPtr = new Bishop(file, rank, false);
//         break;
//     case blackQueen:
//         materialPtr = new Queen(file, rank, false);
//         break;
//     case blackKing:
//         materialPtr = new King(file, rank, false);
//         break;
//     case whiteRook:
//         materialPtr = new Rook(file, rank, true);
//         break;
//     case whiteKnight:
//         materialPtr = new Knight(file, rank, true);
//         break;
//     case whiteBishop:
//         materialPtr = new Bishop(file, rank, true);
//         break;
//     case whiteQueen:
//         materialPtr = new Queen(file, rank, true);
//         break;
//     case whiteKing:
//         materialPtr = new King(file, rank, true);
//         break;
//     case blackPawn:
//         materialPtr = new Pawn(file, rank, false, false);
//         break;
//     case whitePawn:
//         materialPtr = new Pawn(file, rank, true, true);
//         break;
//     default:
//         std::cout << "Error in switch statement of function Square::createMaterial\n";
//         exit(1); // Or let it go on and see where it leads
//         break;
//     }
//     return materialPtr;
// }

void Square::setMaterial(Material *chessman)
{
    chessman_ = chessman;
}

void Square::removeMaterial()
{
    delete chessman_;
    chessman_ = nullptr;
}

void Square::init(int f, int r, bool colored)
{
    file_ = f;
    rank_ = r;
    colored_ = colored;
}

std::string Square::getHTML() const
{
    std::string color = colored_ ? "white" : "black";
    std::string chessman = chessman_ ? chessman_->getHTML() : "";
    std::string attackedDiv;
    if (attacked_)
    {
        if (chessman_ || enPassant_)
        {
            attackedDiv = "<div class=\"circle\"><div class=\"back\">" + chessman + "</div></div>";
        }
        else
        {
            attackedDiv = "<div class=\"circleempty\"></div>";
        }
    }
    else
    {
        attackedDiv = chessman;
    }
    return "<TD class=" + color + ">" + attackedDiv + "</TD>";
}
// <TD class="white"><div class="circleempty"></div></TD>

// <TD class="white">
//     <div class="circle"><div class="back">&#9815;</div></div>
// </TD>
bool Square::attackSquare(Material* attacker)
{
    if((attacker->getint() & (whitePawn | blackPawn)) && enPassant_)
    {
        std::cout << "Attacked enPassant position";
        attacked_ = true;    
    }
    else if(!chessman_)
    {
        std::cout << "Attacked empty square\n";
        attacked_ = true;
        return true;
    }
    else if(attacker->isEnemy(chessman_))
    {
        std::cout << "Attacked enemy\n";
        attacked_ = true;
    }
    return false;
}

void Square::setEnPassant()
{
    enPassant_ = true;
}

Material* Square::getMaterial() const
{
    // std::cout << "Inside getMaterial" << std::endl;
    // std::cout << "file: " << file_ << "rank: " << rank_ << std::endl;
    return chessman_;
}

// Worst function name ever
bool Square::isThereMaterial() const
{
    return chessman_ ? true : false;
}

bool Square::isEnPassant() const
{
    return enPassant_;
}

bool Square::isAttacked() const
{
    return attacked_;
}

void Square::setAttacked(bool attacked)
{
    attacked_ = attacked;
}

// void Square::pickUp()
// {
//     chessman_ = nullptr;
// }