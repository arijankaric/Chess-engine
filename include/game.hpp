#pragma once

#include <chessboard.hpp>
#include <material.hpp>
#include <pawn.hpp>
#include <rook.hpp>
#include <knight.hpp>
#include <bishop.hpp>
#include <king.hpp>
#include <queen.hpp>
#include <pawn.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <regex>

class Game
{
public:
    Game();
    ~Game();
    // void init()
    // {
    //     // srand (time(NULL));
    //     // int side = rand() % 2;
    //     // std::cout << side << std::endl;
    //     // If you're bored in life and want to initialise your very own
    //     // game of chess and play with someone

    //     // How not to hard code init?
    //     for (int i = 0; i < 8; ++i)
    //     {
    //         //blackMaterial[i] = new Pawn()
    //         //whitePieces[i] = new Pawn();
    //     }
    // }

    void selectPosition();

    void parseFEN(std::string &input);
    void generateHTMLDOC();

private:
    Chessboard mainBoard;
    // Material *blackMaterial[16];
    // Material *whiteMaterial[16];

    void setEmpty(int file, int rank);

    void setMaterial(int file, int rank, char *materialCode);

    // FILE represents a ROW in chess
    void parseFILE(std::string &input, int file);

    // Prolly won't need this since material is handled by the squares destructor
    void deleteMaterial(Material **parMaterial);

    Material *makeMaterial(int file, int rank, char *materialCode);

    void projectAttack(int file, int rank);

    // Material *whiteQueen;
    // Material *blackQueen;
    // Material *whitePawns[8];
    // Material *blackPawns[8];
    // Material *whiteKing;
    // Material *blackKing;
    // Material *whiteBishop[2];
    // Material *blackBishop[2];
    // Material *whiteRook[2];
    // Material *blackRook[2];
    // Material *whiteKnight[2];
    // Material *blackKnight[2];

    void verticalUp(int file, int rank);
    void verticalDown(int file, int rank);

    void horizontalLeft(int file, int rank);
    void horizontalRight(int file, int rank);

    // Horse attack
    void jumpingAttack(int file, int rank);

    void diagonallyNorthWest(int file, int rank);

    void diagonallyNorthEast(int file, int rank);
    void diagonallySouthEast(int file, int rank);
    void diagonallySouthWest(int file, int rank);

    // King attack
    void allAround(int file, int rank);

    // White pawns
    void forward(int file, int rank);

    // Black pawns
    void backward(int file, int rank);

    void bishopAttack(int file, int rank);

    void rookAttack(int file, int rank);

    void queenAttack(int file, int rank);

};