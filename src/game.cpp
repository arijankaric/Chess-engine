#include <game.hpp>
#include <fstream>
#include <bitset>
#include <chrono>

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

Game::Game() {}
Game::~Game()
{
    for (const auto &v : garbageCollector)
    {
        delete v;
    }
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

void Game::generateHTMLDOC()
{

    const char *s =
#include <head.html>
        ;
    std::ofstream out{"../output/output1.html"};

    out << s << std::endl;
    out.close();
    mainBoard.generateHTML("../output/output1.html");

    // std::string line;
    // std::ifstream ini_file {"../resources/head.html"};
    // std::ofstream out_file {"../output/output.html"};

    // if(ini_file && out_file){
    //     while(getline(ini_file, line))
    //     {
    //         out_file << line << "\n";
    //     }
    // }
    // else {
    //     printf("something went wrong inside Game::generateHTMLDOC");
    // }

    // ini_file.close();
    // out_file.close();

    // mainBoard.generateHTML("../output/output.html");

    // out_file.open("../output.html", std::ios_base::app);
    // out_file << "appendovanje";
    // out_file.close();

    std::cout << "Wanna open the file[Y/n]" << std::endl;
    char choice;
    std::cin >> choice;
    if (toupper(choice) == 'Y')
        system("xdg-open ../output/output1.html");
    else
        std::cout << "#cry" << std::endl;
}

void Game::selectPosition()
{
    int file = 8, rank = 8;
    char c;
    // std::cout << "Inside selectPosition file: " << file << " rank: " << rank << std::endl;
    while (!mainBoard.validAttacker(file, rank, whosMove))
    {

        // std::cout << whosMove << std::endl;
        std::cout << "Select position of attacking material\nEnter Rank/Column(a-h):";
        std::cin >> c;
        rank = c;
        std::cout << "Enter File/Row(1-8):";
        std::cin >> file;
        --file;
        rank -= 97;
    }

    // std::cout << "file: " << file << " rank: " << rank << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    projectAttack(file, rank);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function projectAttack: " << duration.count() << " microseconds" << std::endl;
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
    // std::cout << "input enPassant: " << input << std::endl;
    std::sregex_iterator second(input.begin(), input.end(), t);
    if (!second->empty())
    {
        auto enPassant = second->str();
        std::cout << enPassant << std::endl;
        int rank = enPassant[0];
        int file = enPassant[1];
        // std::cout << "enPassant file: " << file << " rank: " << rank;
        Chessboard::convertPosition(rank, file);
        // std::cout << "After conversion enPassant file: " << file << " rank: " << rank << std::endl;
        mainBoard.setEnPassant(file, rank);
    }
    std::regex whosTurn("w|b");
    std::sregex_iterator third(input.begin(), input.end(), whosTurn);
    char whosMove = third->str()[0];
    // std::cout << whosMove << std::endl;
    if (whosMove == 'w')
        Game::whosMove = true;
    else
        Game::whosMove = false;

    std::regex castleRgx(" K?Q?k?q? ");
    std::sregex_iterator fourth(input.begin(), input.end(), castleRgx);
    if (!fourth->empty())
    {
        auto castleStr = fourth->str();
        int i = 0;
        while (castleStr[++i] != ' ')
        {
            switch (castleStr[i])
            {
            case 'K':
                castle |= whitekingcastle;
                break;
            case 'Q':
                castle |= whitequeencastle;
                break;
            case 'k':
                castle |= blackkingcastle;
                break;
            case 'q':
                castle |= blackqueencastle;
                break;
            default:
                std::cout << "error in castle switch\n";
            }
        }
    }
    // std::cout << "castle: " << std::bitset<8>(castle) << std::endl;

    // bool r = x3::phrase_parse(input.begin(), input.end(), );
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
            Material *newMat = makeMaterial(file, rank, &input.at(i));
            garbageCollector.push_back(newMat);
            mainBoard.setSquare(file, rank, newMat);

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
    // std::cout << "Input: " << input << std::endl;
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
    // std::cout << "Inside function makeMaterial: " << materialCode[0] << std::endl;
    Material *materialPtr;
    switch (materialCode[0])
    {
    case 'r':
        materialPtr = new Rook(file, rank, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'n':
        materialPtr = new Knight(file, rank, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'b':
        materialPtr = new Bishop(file, rank, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'q':
        materialPtr = new Queen(file, rank, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'k':
        blackKing_ = materialPtr = new King(file, rank, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'R':
        materialPtr = new Rook(file, rank, true);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'N':
        materialPtr = new Knight(file, rank, true);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'B':
        materialPtr = new Bishop(file, rank, true);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'Q':
        materialPtr = new Queen(file, rank, true);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'K':
        whiteKing_ = materialPtr = new King(file, rank, true);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'p':
        materialPtr = new Pawn(file, rank, false, false);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'P':
        materialPtr = new Pawn(file, rank, true, true);
        // mainBoard.setSquare(file, rank, materialPtr);
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

    int typeOfAttackingMaterial = mainBoard.getSquare(file, rank).getMaterial()->getint();

    switch (typeOfAttackingMaterial)
    {
    case whiteKing:
        std::cout << "White King is attacking\n";
        allAround(file, rank);
        break;
    case whiteQueen:
        std::cout << "White Queen is attacking\n";
        queenAttack(file, rank);
        break;
    case whiteBishop:
        std::cout << "White Bishop is attacking\n";
        bishopAttack(file, rank);
        break;
    case whiteKnight:
        std::cout << "White Knight is attacking\n";
        jumpingAttack(file, rank);
        break;
    case whitePawn:
        std::cout << "White Pawn is attacking\n";
        forward(file, rank);
        break;
    case whiteRook:
        std::cout << "White Rook is attacking\n";
        rookAttack(file, rank);
        break;
    case blackKing:
        std::cout << "Black King is attacking\n";
        allAround(file, rank);
        break;
    case blackQueen:
        std::cout << "Black Queen is attacking\n";
        queenAttack(file, rank);
        break;
    case blackBishop:
        std::cout << "Black Bishop is attacking\n";
        bishopAttack(file, rank);
        break;
    case blackKnight:
        std::cout << "Black Knight is attacking\n";
        jumpingAttack(file, rank);
        break;
    case blackPawn:
        std::cout << "Black Pawn is attacking\n";
        backward(file, rank);
        break;
    case blackRook:
        std::cout << "Black Rook is attacking\n";
        rookAttack(file, rank);
        break;
    default:
        std::cout << "Error in Game::projectAttack, switch statement\n";
    }
}

void Game::verticalUp(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(++file, rank, attacker))
    {
    }
}

void Game::verticalDown(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(--file, rank, attacker))
    {
    }
}

void Game::horizontalLeft(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(file, --rank, attacker))
    {
    }
}
void Game::horizontalRight(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(file, ++rank, attacker))
    {
    }
}

// Horse attack
void Game::jumpingAttack(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    attackSquare(file + 2, rank + 1, attacker);
    attackSquare(file + 1, rank + 2, attacker);
    attackSquare(file + 2, rank - 1, attacker);
    attackSquare(file + 1, rank - 2, attacker);
    attackSquare(file - 1, rank - 2, attacker);
    attackSquare(file - 2, rank - 1, attacker);
    attackSquare(file - 2, rank + 1, attacker);
    attackSquare(file - 1, rank + 2, attacker);
}

void Game::diagonallyNorthWest(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(++file, ++rank, attacker))
    {
    }
}

void Game::diagonallyNorthEast(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(++file, --rank, attacker))
    {
    }
}

void Game::diagonallySouthEast(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    // While loops, blocking functions are really really bad practice
    // So need a solution for that
    while (attackSquare(--file, --rank, attacker))
    {
    }
}
void Game::diagonallySouthWest(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    while (attackSquare(--file, ++rank, attacker))
    {
    }
}

// King attack
void Game::allAround(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    attackSquare(file + 1, rank + 1, attacker);
    attackSquare(file + 1, rank, attacker);
    attackSquare(file + 1, rank - 1, attacker);
    bool queenCastle = attackSquare(file, rank - 1, attacker);
    attackSquare(file - 1, rank - 1, attacker);
    attackSquare(file - 1, rank, attacker);
    attackSquare(file - 1, rank + 1, attacker);
    bool kingCastle = attackSquare(file, rank + 1, attacker);

    if (isVulnerable(attacker->isColored()))
        return;

    if (attacker->isColored())
    {
        if ((whitekingcastle & castle) && kingCastle)
            attackSquare(file, rank + 2, attacker);
        if ((whitequeencastle & castle) && queenCastle)
            attackSquare(file, rank - 2, attacker);
    }
    else
    {
        if ((blackkingcastle & castle) && kingCastle)
            attackSquare(file, rank + 2, attacker);
        if ((blackqueencastle & castle) && queenCastle)
            attackSquare(file, rank - 2, attacker);
    }
}

// White pawns
void Game::forward(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    if (!mainBoard.isEmpty(file + 1, rank + 1))
        attackSquare(file + 1, rank + 1, attacker);
    if (!mainBoard.isEmpty(file + 1, rank - 1))
        attackSquare(file + 1, rank - 1, attacker);
    if (mainBoard.isEmpty(file + 1, rank))
    {
        attackSquare(file + 1, rank, attacker);
        if (file == 1 && mainBoard.isEmpty(file + 2, rank))
            attackSquare(file + 2, rank, attacker);
    }
}

// Black pawns
void Game::backward(int file, int rank)
{
    Material *attacker = mainBoard.getSquare(file, rank).getMaterial();
    if (!mainBoard.isEmpty(file - 1, rank + 1) || mainBoard.isEnPassant(file -1, rank +1))
        attackSquare(file - 1, rank + 1, attacker);
    if (!mainBoard.isEmpty(file - 1, rank - 1) || mainBoard.isEnPassant(file-1, rank -1))
        attackSquare(file - 1, rank - 1, attacker);
    if (mainBoard.isEmpty(file - 1, rank))
    {
        attackSquare(file - 1, rank, attacker);
        if (file == 6 && mainBoard.isEmpty(file - 2, rank))
            attackSquare(file - 2, rank, attacker);
    }
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

bool Game::isVulnerable(bool color)
{
    if (color)
    {
        return checkForAttackers(whiteKing_->file_, whiteKing_->rank_, true);
    }
    else
    {
        return checkForAttackers(blackKing_->file_, blackKing_->rank_, false);
    }
}

bool Game::checkForAttackers(int file, int rank, bool colored)
{
    // std::cout << "checkForAttackers file: " << file << "rank: " << rank << std::endl;
    return horseAttackers(file, rank, colored) || queenAttackers(file, rank, colored) || pawnAttackers(file, rank, colored) || kingAttacker(file, rank, colored);
}

bool Game::horseAttackers(int file, int rank, bool colored)
{
    int knight = colored ? blackKnight : whiteKnight;
    return projectBoard.isValidEnemy(file + 2, rank + 1, knight) ||
           projectBoard.isValidEnemy(file + 2, rank - 1, knight) ||
           projectBoard.isValidEnemy(file + 1, rank + 2, knight) ||
           projectBoard.isValidEnemy(file + 1, rank - 2, knight) ||
           projectBoard.isValidEnemy(file - 2, rank - 1, knight) ||
           projectBoard.isValidEnemy(file - 2, rank + 1, knight) ||
           projectBoard.isValidEnemy(file - 1, rank - 2, knight) ||
           projectBoard.isValidEnemy(file - 1, rank + 2, knight);
}

bool Game::queenAttackers(int file, int rank, bool colored)
{
    int queen = colored ? blackQueen : whiteQueen;
    int rook = colored ? blackRook : whiteRook;
    int bishop = colored ? blackBishop : whiteBishop;
    // std::cout << "queenAttackers: " << (queen | rook) << std::endl;

    return verticalUpAttacker(file, rank, (queen | rook)) ||
           verticalDownAttacker(file, rank, (queen | rook)) ||
           horizontalLeftAttacker(file, rank, (queen | rook)) ||
           horizontalRightAttacker(file, rank, (queen | rook)) ||
           diagonallyNorthEastAttacker(file, rank, (queen | bishop)) ||
           diagonallyNorthWestAttacker(file, rank, (queen | bishop)) ||
           diagonallySouthEastAttacker(file, rank, (queen | bishop)) ||
           diagonallySouthWestAttacker(file, rank, (queen | bishop));
}

bool Game::verticalUpAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(++file, rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::verticalDownAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(--file, rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::horizontalLeftAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(file, --rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::horizontalRightAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(file, ++rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::diagonallyNorthEastAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(++file, --rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::diagonallyNorthWestAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(++file, ++rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::diagonallySouthEastAttacker(int file, int rank, int typeOfMat)
{
    // std::cout << "entered southeastattacker\n";
    // std::cout << "southeastattacker: " << file << " " << rank << std::endl;

    while (projectBoard.isEmpty(--file, --rank))
    {
        // std::cout << "southeastattacker: " << file << " " << rank << std::endl;
    }
    // std::cout << "southeastattacker: " << file << " " << rank << std::endl;
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::diagonallySouthWestAttacker(int file, int rank, int typeOfMat)
{
    while (projectBoard.isEmpty(--file, ++rank))
    {
    }
    return projectBoard.isValidEnemy(file, rank, typeOfMat);
}

bool Game::attackSquare(int file, int rank, Material *attacker)
{
    if (!mainBoard.checkForRange(file, rank))
        return false;
    int savedFile = attacker->file_;
    int savedRank = attacker->rank_;
    projectBoard = mainBoard;
    if (mainBoard.isEmpty(file, rank) || mainBoard.getSquare(file, rank).getMaterial()->isEnemy(attacker) || mainBoard.isEnPassant(file, rank))
        projectBoard.moveMaterial(file, rank, attacker);
    if (!isVulnerable(attacker->isColored()))
        mainBoard.attackSquare(file, rank, attacker);
    projectBoard.moveMaterial(savedFile, savedRank, attacker);
    if (mainBoard.isEmpty(file, rank))
        return true;
    return false;
}

bool Game::pawnAttackers(int file, int rank, bool color)
{
    if (color)
        return projectBoard.isValidEnemy(file + 1, rank - 1, blackPawn) ||
               projectBoard.isValidEnemy(file + 1, rank + 1, blackPawn);
    else
        return projectBoard.isValidEnemy(file - 1, rank - 1, whitePawn) ||
               projectBoard.isValidEnemy(file - 1, rank + 1, whitePawn);
}

bool Game::kingAttacker(int file, int rank, bool color)
{
    int king = color ? blackKing : whiteKing;
    return projectBoard.isValidEnemy(file + 1, rank - 1, king) ||
           projectBoard.isValidEnemy(file + 1, rank, king) ||
           projectBoard.isValidEnemy(file + 1, rank + 1, king) ||
           projectBoard.isValidEnemy(file, rank - 1, king) ||
           projectBoard.isValidEnemy(file, rank + 1, king) ||
           projectBoard.isValidEnemy(file - 1, rank - 1, king) ||
           projectBoard.isValidEnemy(file - 1, rank, king) ||
           projectBoard.isValidEnemy(file - 1, rank + 1, king);
}