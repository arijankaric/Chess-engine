#include <game.hpp>

Game::Game() {}
Game::~Game()
{
    // delete mainBoard;
    // Squares should handle this and they're deleted automatically since they're killed in chessboard since they're on the stack and we handle killing chessboard
    // deleteMaterial(blackMaterial);
    // deleteMaterial(whiteMaterial);
}
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

void Game::selectPosition()
{
    int file = 8, rank = 8;
    char c;
    std::cout << "Inside selectPosition file: " << file << " rank: " << rank << std::endl;
    while (!mainBoard.validAttacker(file, rank))
    {
        
        std::cout << "Select position of attacking material\nEnter Rank/Column(a-h):";
        std::cin >> c;
        rank = c;
        std::cout << "Enter File/Row(1-8):";
        std::cin >> file;
        --file;
        rank -= 97;
    }


    std::cout << "file: " << file << " rank: " << rank << std::endl;
    projectAttack(file, rank);
}

void Game::parseFEN(std::string &input)
{
    std::regex r("/| ");
    for (int i = 7; i >= 0; --i)
    {
        std::sregex_iterator first(input.begin(), input.end(), r);
        //int where = input.find("/");
        auto where = first->position();
        std::string send = input.substr(0, where);
        input.erase(0, where + 1);
        //std::cout << "input: " << input << std::endl;
        parseFILE(send, i);
    }
    std::regex t("[a-h][1-8]");
    std::cout << "input enPassant: " << input << std::endl;
    std::sregex_iterator second(input.begin(), input.end(), t);
    if(!second->empty())
    {
    auto enPassant = second->str();
    std::cout << enPassant << std::endl;
    int file = enPassant[0];
    int rank = enPassant[1];
    std::cout << "enPassant file: " << file << " rank: " << rank;
    Chessboard::convertPosition(rank, file);
    std::cout << "After conversion enPassant file: " << file << " rank: " << rank << std::endl;
    }
}

void Game::setEmpty(int file, int rank)
{
    mainBoard.setSquare(file, rank, nullptr);
}

void Game::setMaterial(int file, int rank, char *materialCode)
{
    makeMaterial(file, rank, materialCode);
    // Material *argMaterial = makeMaterial(file, rank, materialCode);
    // mainBoard.setSquare(file, rank, argMaterial);
}

// FILE represents a ROW in chess
void Game::parseFILE(std::string &input, int file)
{
    // int numOfRanks = 8; // Describes number of places in a file. Probably should use the definition from chessboard.hpp
    int rank = 0; // Should probably abstract this as rows/columns so that people that use class game don't need to keep that kind of stuff in memory?
    for (long unsigned int i = 0; i < input.length(); ++i)
    {
        if (isdigit(input[i]))
        {

            int num = input[i] - 48;
            //std::cout << num << std::endl;
            for (int i = num; i > 0; --i)
            {
                setEmpty(file, rank);
                ++rank;
                // Game::setEmpty(int file, int rank);
            }
        }
        else if (isalpha(input[i]))
        {
            makeMaterial(file, rank, &input.at(i));
            ++rank;
        }
        //std::cout << "testType is alpha: " << isalpha(testType) << std::endl;
        //std::cout << "testType is digit: " << isdigit(testType) << std::endl;

        // Or we could let class Game handle this
        // Game::setPiece(char material, int file, int rank);
        // method setPiece should be able to manipulate both
        // squares of the chessboard or chessboard and material
        // on the chessboard
        // Also should we make these functions anonymous functions
        // so we can capture object of class Game
        // Seems kinda immature to pass object of class Game
        // by reference don't you think.
    }
    std::cout << "Input: " << input << std::endl;
}

// Prolly won't need this since material is handled by the squares destructor
void Game::deleteMaterial(Material **parMaterial)
{
    for (int i = 0; i < 16; ++i)
    {
        delete parMaterial[i];
    }
}

Material *Game::makeMaterial(int file, int rank, char *materialCode)
{
    std::cout << "Inside function makeMaterial: " << materialCode[0] << std::endl;
    Material *materialPtr;
    switch (materialCode[0])
    {
    case 'r':
        materialPtr = new Rook(file, rank, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'n':
        materialPtr = new Knight(file, rank, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'b':
        materialPtr = new Bishop(file, rank, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'q':
        materialPtr = new Queen(file, rank, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'k':
        materialPtr = new King(file, rank, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'R':
        materialPtr = new Rook(file, rank, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'N':
        materialPtr = new Knight(file, rank, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'B':
        materialPtr = new Bishop(file, rank, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'Q':
        materialPtr = new Queen(file, rank, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'K':
        materialPtr = new King(file, rank, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'p':
        materialPtr = new Pawn(file, rank, false, false);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'P':
        materialPtr = new Pawn(file, rank, true, true);
        mainBoard.setSquare(file, rank, materialPtr);
        break;
    default:
        std::cout << "Error in switch statement of function makeMaterial\n";
        exit(1); // Or let it go on and see where it leads
        break;
    }
    return materialPtr;
}

void Game::projectAttack(int file, int rank)
{
    // mainBoard.getSquare(file, rank).getMaterial()->projectAttack(mainBoard);



    char typeOfAttackingMaterial = mainBoard.getSquare(file, rank).getMaterial()->getTypeOfMaterial();

    switch(typeOfAttackingMaterial) 
    {
        case 'K':
        std::cout << "White King is attacking\n";
        allAround(file, rank);
        break;
        case 'Q':
        std::cout << "White Queen is attacking\n";
        queenAttack(file, rank);
        break;
        case 'B':
        std::cout << "White Bishop is attacking\n";
        bishopAttack(file, rank);
        break;
        case 'N':
        std::cout << "White Knight is attacking\n";
        jumpingAttack(file, rank);
        break;
        case 'P':
        std::cout << "White Pawn is attacking\n";
        backward(file, rank);
        break;
        case 'R':
        std::cout << "White Rook is attacking\n";
        rookAttack(file, rank);
        break;
        case 'k':
        std::cout << "Black King is attacking\n";
        allAround(file, rank);
        break;
        case 'q':
        std::cout << "Black Queen is attacking\n";
        queenAttack(file, rank);
        break;
        case 'b':
        std::cout << "Black Bishop is attacking\n";
        bishopAttack(file, rank);
        break;
        case 'n':
        std::cout << "Black Knight is attacking\n";
        jumpingAttack(file, rank);
        break;
        case 'p':
        std::cout << "Black Pawn is attacking\n";
        forward(file, rank);
        break;
        case 'r':
        std::cout << "Black Rook is attacking\n";
        rookAttack(file, rank);
        break;
        default:
        std::cout << "Error in Game::projectAttack, switch statement\n";
    }
}

void Game::verticalUp(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(++file, rank, attacker))
    {
    }
}

void Game::verticalDown(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(--file, rank, attacker))
    {
    }
}

void Game::horizontalLeft(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(file, --rank, attacker))
    {
    }
}
void Game::horizontalRight(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(file, ++rank, attacker))
    {
    }
}

// Horse attack
void Game::jumpingAttack(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    mainBoard.attackSquare(file + 2, rank + 1, attacker);
    mainBoard.attackSquare(file + 1, rank + 2, attacker);
    mainBoard.attackSquare(file + 2, rank - 1, attacker);
    mainBoard.attackSquare(file + 1, rank - 2, attacker);
    mainBoard.attackSquare(file - 1, rank - 2, attacker);
    mainBoard.attackSquare(file - 2, rank - 1, attacker);
    mainBoard.attackSquare(file - 2, rank + 1, attacker);
    mainBoard.attackSquare(file - 1, rank + 2, attacker);
}

void Game::diagonallyNorthWest(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(++file, ++rank, attacker))
    {
    }
}

void Game::diagonallyNorthEast(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(++file, --rank, attacker))
    {
    }
}

void Game::diagonallySouthEast(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    // While loops, blocking functions are really really bad practice
    // So need a solution for that
    while (mainBoard.attackSquare(--file, --rank, attacker))
    {
    }
}
void Game::diagonallySouthWest(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (mainBoard.attackSquare(--file, ++rank, attacker))
    {
    }
}

// King attack
void Game::allAround(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    mainBoard.attackSquare(file + 1, rank + 1, attacker);
    mainBoard.attackSquare(file + 1, rank, attacker);
    mainBoard.attackSquare(file + 1, rank - 1, attacker);
    mainBoard.attackSquare(file, rank - 1, attacker);
    mainBoard.attackSquare(file - 1, rank - 1, attacker);
    mainBoard.attackSquare(file - 1, rank, attacker);
    mainBoard.attackSquare(file - 1, rank + 1, attacker);
    mainBoard.attackSquare(file, rank + 1, attacker);
}

// White pawns
void Game::forward(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    mainBoard.attackSquare(file + 1, rank + 1, attacker);
    mainBoard.attackSquare(file + 1, rank - 1, attacker);
}

// Black pawns
void Game::backward(int file, int rank)
{
    Material* attacker = mainBoard.getSquare(file, rank).getMaterial();
    mainBoard.attackSquare(file - 1, rank + 1, attacker);
    mainBoard.attackSquare(file - 1, rank - 1, attacker);
}

void Game::bishopAttack(int file, int rank)
{
    diagonallyNorthEast(file, rank);
    diagonallyNorthWest(file, rank);
    diagonallySouthEast(file, rank);
    diagonallySouthWest(file, rank);
}

void Game::rookAttack(int file, int rank)
{
    verticalUp(file, rank);
    verticalDown(file, rank);
    horizontalLeft(file, rank);
    horizontalRight(file, rank);
}

void Game::queenAttack(int file, int rank)
{
    bishopAttack(file, rank);
    rookAttack(file, rank);
}
