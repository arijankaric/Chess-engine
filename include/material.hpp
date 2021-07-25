#pragma once

// These pieces are sometimes called chessmen, but most experienced players refer to their pieces as “material".

#include <string>


#define whiteQueen 1<<1
#define whiteKing 1<<2
#define whitePawn 1<<3
#define whiteBishop 1<<4
#define whiteKnight 1<<5
#define whiteRook 1<<6
#define blackQueen 1<<7
#define blackKing 1<<8
#define blackPawn 1<<9
#define blackBishop 1<<10
#define blackKnight 1<<11
#define blackRook 1<<12
// enum int : uint16_t
// {
//     whiteQueen = 1,
//     whiteKing = 2,
//     whitePawn = 4,
//     whiteBishop = 8,
//     whiteKnight = 16,
//     whiteRook = 32,
//     blackQueen = 64,
//     blackKing = 128,
//     blackPawn = 256,
//     blackBishop = 512,
//     blackKnight = 1024,
//     blackRook = 2048
// };

// constexpr enum int operator |( const enum int selfValue, const enum int inValue )
// {
//     return (enum int)(uint16_t(selfValue) | uint16_t(inValue));
// }

// constexpr enum int operator &( const enum int selfValue, const enum int inValue )
// {
//     return (enum int)(uint16_t(selfValue) & uint16_t(inValue));
// }

// 11 bits, how to fix this? probably don't need to enumerate all figures by power of 2 since not all figures will be mixed
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
    virtual int getint() = 0;
    virtual bool isColored() = 0;
    virtual bool isEnemy(Material* target) = 0;
    int file_;
    int rank_;
    protected:
    // int file_; // vertical row
    // int rank_; // horizontal row
    bool colored_; // true - white, false - black
};