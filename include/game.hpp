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
#include <vector>

#define blackqueencastle 0b0000'0001
#define blackkingcastle  0b0000'0010
#define whitequeencastle 0b0000'0100
#define whitekingcastle  1<<4


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
    void playGame();
    void selectPosition();
    bool moveAttacker(int, int);
    void selectPositionToMove();

    void parseFEN(std::string &input);
    void parseFENOld(std::string &input);
    void generateHTMLDOC();
    std::string generateFEN() const;

private:
    Chessboard mainBoard;
    Chessboard projectBoard;
    std::vector<Material*> garbageCollectorBlack;
    std::vector<Material*> garbageCollectorWhite;
    Material *selectedAttacker;
    // Material *blackMaterial[16];
    // Material *whiteMaterial[16];

    bool whosMove; // 0 - black, 1 - white
    int castle = 0b0000'0000;
    int halfMoveClock = 0;
    int fullMoveNumber = 1;
    std::string enPassant;
    bool hasMoves = false;


    void setEmpty(int file, int rank);


    // FILE represents a ROW in chess
    void parseFILE(std::string &input, int file);

    // Prolly won't need this since material is handled by the squares destructor
    void deleteMaterial(Material **parMaterial);

    Material *makeMaterial(int file, int rank, char materialCode);

    void projectAttack(int file, int rank);
    bool isValidAttackPosition(int, int) const;

    bool isCheckMate() const;
    bool anyMovesLeft();

    
    void setUpGame();

    void congratulateToWinner() const;
    bool draw();

    // Material *whiteQueen;
    // Material *blackQueen;
    // Material *whitePawns[8];
    // Material *blackPawns[8];
    Material *whiteKing_;
    Material *blackKing_;
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

    bool isVulnerable(bool);

    bool checkForAttackers(int, int, bool);

    bool horseAttackers(int, int, bool);

    bool queenAttackers(int, int, bool);

    bool pawnAttackers(int, int, bool);

    bool verticalUpAttacker(int, int, int);

    bool verticalDownAttacker(int, int, int);

    bool horizontalLeftAttacker(int, int, int);

    bool horizontalRightAttacker(int, int, int);

    bool diagonallyNorthWestAttacker(int, int, int);

    bool diagonallyNorthEastAttacker(int, int, int);

    bool diagonallySouthEastAttacker(int, int, int);

    bool diagonallySouthWestAttacker(int, int, int);

    bool attackSquare(int, int, Material*);

    bool kingAttacker(int, int, bool);



};