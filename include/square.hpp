#pragma once

#include <material.hpp>

class Material;

class Square
{
public:
    Square();
    Square(bool, char, char, Material*);
    ~Square();
    void setMaterial(Material *chessman);
    void init(int f, int r, bool colored);
    std::string getHTML();
    // <TD class="white"><div class="circleempty"></div></TD>

    // <TD class="white">
    //     <div class="circle"><div class="back">&#9815;</div></div>
    // </TD>
    bool attackSquare(Material* attacker);
    void setEnPassant();
    Material* getMaterial();
    bool isThereMaterial();

private:
    Material* chessman_{nullptr};
    bool colored_;       // false - black, true - white or in our case false - green, true yellowgreenish I guess
    int file_; // Probably don't need this since chessboard handles this
    int rank_;
    bool attacked_{false};
    bool enPassant_{false};
};