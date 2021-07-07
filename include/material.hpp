#pragma once

// These pieces are sometimes called chessmen, but most experienced players refer to their pieces as “material".

#include <string>

class Chessboard;

class Material {
    public:
    Material();
    Material(int file, int rank, bool colored);
    virtual ~Material();
    // virtual binded at run-time
    // non-virtual binded at compile-time
    // virtual void projectAttack(Chessboard&) = 0;
    virtual std::string getHTML() = 0;
    virtual char getTypeOfMaterial() = 0;
    virtual bool isColored() = 0;
    virtual bool isEnemy(Material* target) = 0;
    protected:
    int file_; // vertical row
    int rank_; // horizontal row
    bool colored_; // true - white, false - black
};