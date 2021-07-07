// #include <attack.hpp>



// void verticalUp(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(++file, rank))
//     {
//     }
// }

// void verticalDown(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(--file, rank))
//     {
//     }
// }

// void horizontalLeft(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(file, --rank))
//     {
//     }
// }
// void horizontalRight(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(file, ++rank, mainBoard.getSquare(file, rank).getMaterial()))
//     {
//     }
// }

// // Horse attack
// void jumpingAttack(int file, int rank, Chessboard &mainBoard)
// {
//     mainBoard.attackSquare(file + 2, rank + 1);
//     mainBoard.attackSquare(file + 1, rank + 2);
//     mainBoard.attackSquare(file + 2, rank - 1);
//     mainBoard.attackSquare(file + 1, rank - 2);
//     mainBoard.attackSquare(file - 1, rank - 2);
//     mainBoard.attackSquare(file - 2, rank - 1);
//     mainBoard.attackSquare(file - 2, rank + 1);
//     mainBoard.attackSquare(file - 1, rank + 2);
// }

// void diagonallyNorthWest(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(++file, ++rank))
//     {
//     }
// }

// void diagonallyNorthEast(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(++file, --rank))
//     {
//     }
// }

// void diagonallySouthEast(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(--file, --rank))
//     {
//     }
// }
// void diagonallySouthWest(int file, int rank, Chessboard &mainBoard)
// {
//     while (mainBoard.attackSquare(--file, ++rank))
//     {
//     }
// }

// // King attack
// void allAround(int file, int rank, Chessboard &mainBoard)
// {
//     mainBoard.attackSquare(file + 1, rank + 1);
//     mainBoard.attackSquare(file + 1, rank);
//     mainBoard.attackSquare(file + 1, rank - 1);
//     mainBoard.attackSquare(file, rank - 1);
//     mainBoard.attackSquare(file - 1, rank - 1);
//     mainBoard.attackSquare(file - 1, rank);
//     mainBoard.attackSquare(file - 1, rank + 1);
//     mainBoard.attackSquare(file, rank + 1);
// }

// // White pawns
// void forward(int file, int rank, Chessboard &mainBoard)
// {
//     mainBoard.attackSquare(file + 1, rank + 1);
//     mainBoard.attackSquare(file + 1, rank - 1);
// }

// // Black pawns
// void backward(int file, int rank, Material* attacker)
// {
//     mainBoard.attackSquare(file - 1, rank + 1);
//     mainBoard.attackSquare(file - 1, rank - 1);
// }

// void bishopAttack(int file, int rank, Chessboard &mainBoard)
// {
//     diagonallyNorthEast(file, rank, mainBoard);
//     diagonallyNorthWest(file, rank, mainBoard);
//     diagonallySouthEast(file, rank, mainBoard);
//     diagonallySouthWest(file, rank, mainBoard);
// }

// void rookAttack(int file, int rank, Chessboard &mainBoard)
// {
//     verticalUp(file, rank, mainBoard);
//     verticalDown(file, rank, mainBoard);
//     horizontalLeft(file, rank, mainBoard);
//     horizontalRight(file, rank, mainBoard);
// }

// void queenAttack(int file, int rank, Chessboard &mainBoard)
// {
//     bishopAttack(file, rank, mainBoard);
//     rookAttack(file, rank, mainBoard);
// }
