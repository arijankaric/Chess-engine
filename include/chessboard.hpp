#pragma once

#include <stdlib.h>
#include <square.hpp>
#include <functional>
#define FILES 8
#define RANKS 8
#define NUMOFSQUARES FILES*RANKS

class Square;
class Material;

class Chessboard
{
public:
    Chessboard();
    ~Chessboard();
    // If we use this method for attack it will be a tad bit slower since we'll need to traverse the whole chessboard
    // And how do we check is the attacking material visible, probably looping like we did with the opposite method
    void transformSquare(int file, int rank, std::function<void(Square *)> transform);
    void setSquare(int file, int rank, Material *chessman);

    bool validAttacker(int file, int rank, bool color);
    const Square& getSquare(int file, int rank) const;

    void attackingSquare(int file, int rank);
    // We need to account for En passant target square
    bool attackSquare(int file, int rank, Material* attacker);
    static void convertPosition(int&, int&);
    void setEnPassant(int, int);
    void generateHTML(const std::string);
    bool isValidEnemy(int file, int rank, int typeOfMat) const;
    bool isEmpty(int file, int rank) const;
    bool projectMove(int file, int rank);
    void moveMaterial(int file, int rank, Material* mat);
    bool checkForRange(int file, int rank) const;
    bool isEnPassant(int, int) const;
    void removeMaterial(int file, int rank);
    void invalidateAttacked();
    bool anyAttackedSquare() const;



private:
    Square squares[FILES][RANKS];
    //Square *squares2 = (Square*) malloc(FILES*RANKS*sizeof(Square));
    // we'll see how we can manipulate this later and is it a better option and why
    // and all the other options how this could be done/improved
    void init();

    // Returns false if out of range, true if in range, kinda not intuitive, should change that

};