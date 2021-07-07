#include <square.hpp>
#include <iostream>

Square::Square() = default;
Square::Square(bool, char, char, Material *)
{
}

Square::~Square()
{
    delete chessman_;
}

void Square::setMaterial(Material *chessman)
{
    chessman_ = chessman;
}

void Square::init(int f, int r, bool colored)
{
    file_ = f;
    rank_ = r;
    colored_ = colored;
}

std::string Square::getHTML()
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
    if(!chessman_)
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

Material* Square::getMaterial()
{
    std::cout << "Inside getMaterial" << std::endl;
    return chessman_;
}

// Worst function name ever
bool Square::isThereMaterial()
{
    return chessman_ ? true : false;
}