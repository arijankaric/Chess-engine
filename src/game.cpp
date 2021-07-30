#include <game.hpp>
#include <fstream>
#include <bitset>
#include <chrono>
#include <regex>
#include <functional>

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using ascii::space;
using x3::_attr;
using x3::phrase_parse;

// struct material_ : x3::symbols<unsigned>
// {
//     material_()
//     {
//         add("k", blackKing)("q", blackQueen)("r", blackRook)("b", blackBishop)("n", blackKnight)("p", blackPawn)("K", whiteKing)("Q", whiteQueen)("R", whiteRook)("B", whiteBishop)("N", whiteKnight)("P", whitePawn);
//     }

// } hundreds;

Game::Game() {}
Game::~Game()
{
    for (const auto &v : garbageCollectorWhite)
    {
        delete v;
    }
    for (const auto &v : garbageCollectorBlack)
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

    // std::cout << "Wanna open the file[Y/n]" << std::endl;
    // char choice;
    // std::cin >> choice;
    // if (toupper(choice) == 'Y')
    //     system("xdg-open ../output/output1.html");
    // else
    //     std::cout << "#cry" << std::endl;
}

void Game::selectPositionToMove()
{
    int file = 8;
    int rank = 8;
    char c;
    // std::cout << "Inside selectPosition file: " << file << " rank: " << rank << std::endl;
    while (!isValidAttackPosition(file, rank))
    {

        // std::cout << whosMove << std::endl;
        std::cout << "Select position of square where you want your selected material to move to\nEnter Rank/Column(a-h):";
        std::cin >> c;
        rank = c;
        std::cout << "Enter File/Row(1-8):";
        std::cin >> file;
        --file;
        rank -= 97;
    }
    ++halfMoveClock;
    if (!whosMove)
        ++fullMoveNumber;
    if ((selectedAttacker->getint() & (whitePawn | blackPawn)) || mainBoard.getSquare(file, rank).isThereMaterial())
        halfMoveClock = 0;
    if ((selectedAttacker->getint() & (whitePawn | blackPawn)) && abs(file - selectedAttacker->file_) == 2)
    {
        // std::cout << "Inside enPassant if\n";
        int enPassantFile = 0;
        // int enPassantArgument = 0;
        if (file == 3)
        {
            enPassantFile = 3;
            // enPassantArgument = 2;
        }
        else if (file == 4)
        {
            enPassantFile = 6;
            // enPassantArgument = 5;
        }
        else
            std::cout << "Error in enPassant if statement, value: " << file << std::endl;
        c = rank + 97;

        enPassant = c + std::to_string(enPassantFile);
        mainBoard.setEnPassant(enPassantFile - 1, rank);
        // std::cout << enPassant << std::endl;
    }
    else
    {
        enPassant = "-";
    }

    // std::cout << "file: " << file << " rank: " << rank << std::endl;
    // auto start = std::chrono::high_resolution_clock::now();
    auto distance = abs(rank - selectedAttacker->rank_);
    moveAttacker(file, rank);
    if ((selectedAttacker->getint() & (whiteKing | blackKing)) && distance == 2)
    {
        if (selectedAttacker->isColored())
        {
            castle = castle & (blackkingcastle | blackqueencastle);
        }
        else
        {
            castle = castle & (whitekingcastle | whitequeencastle);
        }

        if (rank == 2)
        {
            selectedAttacker = mainBoard.getSquare(file, 0).getMaterial();
            moveAttacker(file, rank + 1);
        }
        else if (rank == 6)
        {
            selectedAttacker = mainBoard.getSquare(file, 7).getMaterial();
            moveAttacker(file, rank - 1);
        }
    }

    // mainBoard.moveMaterial(file, rank, selectedAttacker);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "Time taken by function projectAttack: " << duration.count() << " microseconds" << std::endl;
    whosMove = !whosMove;
}

void Game::selectPosition()
{
    int file = 8;
    int rank = 8;
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
    selectedAttacker = mainBoard.getSquare(file, rank).getMaterial();
    mainBoard.invalidateAttacked();
    // std::cout << "file: " << file << " rank: " << rank << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    projectAttack(file, rank);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function projectAttack: " << duration.count() << " microseconds" << std::endl;
}

void Game::parseFENOld(std::string &input)
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
        // std::cout << send << std::endl;
        parseFILE(send, i);
    }

    std::regex t("[a-h][1-8]");
    // std::cout << "input enPassant: " << input << std::endl;
    std::sregex_iterator second(input.begin(), input.end(), t);
    if (!second->empty())
    {
        auto enPassant = second->str();
        // std::cout << enPassant << std::endl;
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
}

void Game::parseFEN(std::string &input)
{
    int file = 7;
    int rank = 0;
    // auto &m = mainBoard;
    auto setFullSquareLambda = [&](auto &ctx)
    {
        // std::cout << "Type of material\n" << _attr(ctx) << std::endl;
        Material *newMat = makeMaterial(file, rank, _attr(ctx));
        // garbageCollector.push_back(newMat);
        mainBoard.setSquare(file, rank, newMat);
        ++rank;
    };
    auto setEmptySquareLambda = [&](auto &ctx)
    {
        // std::cout << "EmptySquare: " << _attr(ctx) << std::endl;
        int i = 0;
        while (_attr(ctx) > i)
        {
            setEmpty(file, rank);
            ++rank;
            ++i;
        }
    };
    auto decrementFileLambda = [&](auto &ctx)
    {
        // std::cout << "Decrement file in lambda\n";
        --file;
        rank = 0;
    };
    auto setMoveLambda = [&](auto &ctx)
    {
        // std::cout << "inside setMoveLambda\n" << _attr(ctx) << std::endl;
        switch (boost::get<char>(_attr(ctx)))
        {
        case 'w':
            // std::cout << "Whites move\n";
            whosMove = true;
            break;
        case 'b':
            // std::cout << "Blacks move\n";
            whosMove = false;
            break;
        default:
            std::cout << "Error in setMoveLambda, val:" << _attr(ctx) << std::endl;
        }
    };
    auto setCastleLambda = [&](auto &ctx)
    {
        switch (boost::get<char>(_attr(ctx)))
        {
        case 'K':
            // std::cout << "White king side can castle\n";
            castle |= whitekingcastle;
            break;
        case 'Q':
            // std::cout << "White queen side can castle\n";
            castle |= whitequeencastle;
            break;
        case 'k':
            // std::cout << "Black king side can castle\n";
            castle |= blackkingcastle;
            break;
        case 'q':
            // std::cout << "Black queen side can castle\n";
            castle |= blackqueencastle;
            break;
        default:
            std::cout << "error in castle switch, val: " << boost::get<char>(_attr(ctx)) << std::endl;
        }
    };
    auto setEnPassantLambda = [&](auto &ctx)
    {
        // std::cout << _attr(ctx) << std::endl;
        int file = boost::fusion::at_c<1>(_attr(ctx));
        int rank = boost::fusion::at_c<0>(_attr(ctx));
        enPassant = char(rank) + file;
        // std::cout << "file: " << file << "rank: " << rank << std::endl;
        --file;
        rank -= 97;
        // std::cout << "file: " << file << "rank: " << rank << std::endl;
        mainBoard.setEnPassant(file, rank);
    };
    auto setHalfMoveClockLambda = [&](auto &ctx)
    {
        std::cout << _attr(ctx) << std::endl;
        Game::halfMoveClock = _attr(ctx);
    };
    auto setFullMoveNumberLambda = [&](auto &ctx)
    {
        std::cout << _attr(ctx) << std::endl;
        Game::fullMoveNumber = _attr(ctx);
    };

    auto itBegin = input.begin();
    auto itEnd = input.end();

    // rule<ID> const r = "some-name";
    // x3::rule<Chessboard, std::string> const FEN = "FEN";

    // auto const FEN_def =
    //     (+(+(x3::int8 [setEmptySquareLambda] | x3::alpha [setFullSquareLambda])
    //             >> (x3::char_('/'))  [decrementFileLambda])
    //             >> x3::string(" ")
    //             >> x3::char_('w' | 'b') [setMoveLambda]
    //             >> -x3::char_('K') [setCastleLambda]
    //             >> -x3::char_('Q') [setCastleLambda]
    //             >> -x3::char_('k') [setCastleLambda]
    //             >> -x3::char_('q') [setCastleLambda]
    //             >> x3::space
    //             >> -(x3::char_ >> x3::int_) [setEnPassantLambda]
    //     )
    //     ;

    // auto spaceLambda = [&](auto &ctx){std::cout << "space\n";};
    // x3::phrase_parse(itBegin, itEnd, FEN_def, space);
    x3::parse(itBegin, itEnd, (+(x3::int8[setEmptySquareLambda] | x3::alpha[setFullSquareLambda]) >> +(x3::char_('/')[decrementFileLambda] >> +(x3::int8[setEmptySquareLambda] | x3::alpha[setFullSquareLambda])) >> x3::space //[spaceLambda]
                               >> (x3::char_('w') | x3::char_('b'))[setMoveLambda] >> x3::space                                                                                                                                //[spaceLambda]
                               >> -x3::char_('K')[setCastleLambda] >> -x3::char_('Q')[setCastleLambda] >> -x3::char_('k')[setCastleLambda] >> -x3::char_('q')[setCastleLambda] >> x3::space                                    //[spaceLambda]
                               >> -(x3::char_ >> x3::int_)[setEnPassantLambda] >> x3::space >> x3::int8[setHalfMoveClockLambda] >> x3::space >> x3::int8[setFullMoveNumberLambda]));

    // bool res = parse(itBegin, itEnd, FEN);
    // if (res && itBegin == itEnd)
    // {
    //     std::cout << "-------------------------\n";
    //     std::cout << "Parsing succeeded\n";
    //     // std::cout << "result = " << result << std::endl;
    //     std::cout << "-------------------------\n";
    // }
    // else
    // {
    //     std::string rest(itBegin, itEnd);
    //     std::cout << "-------------------------\n";
    //     std::cout << "Parsing failed\n";
    //     std::cout << "stopped at: \": " << rest << "\"\n";
    //     std::cout << "-------------------------\n";
    // }

    // std::regex r("/| ");
    // for (int i = 7; i >= 0; --i)
    // {
    //     std::sregex_iterator first(input.begin(), input.end(), r);
    //     //int where = input.find("/");
    //     auto where = first->position();
    //     std::string send = input.substr(0, where);
    //     input.erase(0, where + 1);
    //     //std::cout << "input: " << input << std::endl;
    //     // std::cout << send << std::endl;
    //     parseFILE(send, i);
    // }

    // std::regex t("[a-h][1-8]");
    // // std::cout << "input enPassant: " << input << std::endl;
    // std::sregex_iterator second(input.begin(), input.end(), t);
    // if (!second->empty())
    // {
    //     auto enPassant = second->str();
    //     // std::cout << enPassant << std::endl;
    //     int rank = enPassant[0];
    //     int file = enPassant[1];
    //     // std::cout << "enPassant file: " << file << " rank: " << rank;
    //     Chessboard::convertPosition(rank, file);
    //     // std::cout << "After conversion enPassant file: " << file << " rank: " << rank << std::endl;
    //     mainBoard.setEnPassant(file, rank);
    // }
    // std::regex whosTurn("w|b");
    // std::sregex_iterator third(input.begin(), input.end(), whosTurn);
    // char whosMove = third->str()[0];
    // // std::cout << whosMove << std::endl;
    // if (whosMove == 'w')
    //     Game::whosMove = true;
    // else
    //     Game::whosMove = false;

    // std::regex castleRgx(" K?Q?k?q? ");
    // std::sregex_iterator fourth(input.begin(), input.end(), castleRgx);
    // if (!fourth->empty())
    // {
    //     auto castleStr = fourth->str();
    //     int i = 0;
    //     while (castleStr[++i] != ' ')
    //     {
    //         switch (castleStr[i])
    //         {
    //         case 'K':
    //             castle |= whitekingcastle;
    //             break;
    //         case 'Q':
    //             castle |= whitequeencastle;
    //             break;
    //         case 'k':
    //             castle |= blackkingcastle;
    //             break;
    //         case 'q':
    //             castle |= blackqueencastle;
    //             break;
    //         default:
    //             std::cout << "error in castle switch\n";
    //         }
    //     }
    // }
    // std::cout << "castle: " << std::bitset<8>(castle) << std::endl;

    // bool r = x3::phrase_parse(input.begin(), input.end(), );
}

void Game::setEmpty(int file, int rank)
{
    mainBoard.setSquare(file, rank, nullptr);
}

// void Game::parseChar()
// {}

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
            Material *newMat = makeMaterial(file, rank, input.at(i));
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

Material *Game::makeMaterial(int file, int rank, char materialCode)
{
    // std::cout << "Inside function makeMaterial: " << materialCode << std::endl;
    Material *materialPtr;
    switch (materialCode)
    {
    case 'r':
        materialPtr = new Rook(file, rank, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'n':
        materialPtr = new Knight(file, rank, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'b':
        materialPtr = new Bishop(file, rank, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'q':
        materialPtr = new Queen(file, rank, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'k':
        blackKing_ = materialPtr = new King(file, rank, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'R':
        materialPtr = new Rook(file, rank, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'N':
        materialPtr = new Knight(file, rank, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'B':
        materialPtr = new Bishop(file, rank, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'Q':
        materialPtr = new Queen(file, rank, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'K':
        whiteKing_ = materialPtr = new King(file, rank, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'p':
        materialPtr = new Pawn(file, rank, false, false);
        garbageCollectorBlack.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    case 'P':
        materialPtr = new Pawn(file, rank, true, true);
        garbageCollectorWhite.push_back(materialPtr);
        // mainBoard.setSquare(file, rank, materialPtr);
        break;
    default:
        std::cout << "Error in switch statement of function makeMaterial\n"
                  << materialCode << std::endl;
        exit(1); // Or let it go on and see where it leads
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
    bool queenCastle = attackSquare(file, rank - 1, attacker) && mainBoard.isAttacked(file, rank - 1);
    attackSquare(file - 1, rank - 1, attacker);
    attackSquare(file - 1, rank, attacker);
    attackSquare(file - 1, rank + 1, attacker);
    bool kingCastle = attackSquare(file, rank + 1, attacker) && mainBoard.isAttacked(file, rank + 1);

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
    if (!mainBoard.isEmpty(file + 1, rank + 1) || mainBoard.isEnPassant(file + 1, rank + 1))
        attackSquare(file + 1, rank + 1, attacker);
    if (!mainBoard.isEmpty(file + 1, rank - 1) || mainBoard.isEnPassant(file + 1, rank - 1))
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
    if (!mainBoard.isEmpty(file - 1, rank + 1) || mainBoard.isEnPassant(file - 1, rank + 1))
        attackSquare(file - 1, rank + 1, attacker);
    if (!mainBoard.isEmpty(file - 1, rank - 1) || mainBoard.isEnPassant(file - 1, rank - 1))
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
    if (mainBoard.isEmpty(file, rank) || mainBoard.getSquare(file, rank).getMaterial()->isEnemy(attacker))
        projectBoard.moveMaterial(file, rank, attacker);
    if (!isVulnerable(attacker->isColored()))
    {
        hasMoves = true;
        mainBoard.attackSquare(file, rank, attacker);
    }
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

bool Game::moveAttacker(int file, int rank)
{
    if (!isValidAttackPosition(file, rank))
        return false;

    Material *defeated = mainBoard.getSquare(file, rank).getMaterial();

    if (mainBoard.isEnPassant(file, rank))
    {
        if (whosMove)
        {
            defeated = mainBoard.getSquare(file - 1, rank).getMaterial();
            mainBoard.removeMaterial(file - 1, rank);
        }
        else
        {
            defeated = mainBoard.getSquare(file + 1, rank).getMaterial();
            mainBoard.removeMaterial(file + 1, rank);
        }
    }

    if (whosMove)
        garbageCollectorBlack.erase(std::remove(garbageCollectorBlack.begin(), garbageCollectorBlack.end(), defeated), garbageCollectorBlack.end());
    else
        garbageCollectorWhite.erase(std::remove(garbageCollectorWhite.begin(), garbageCollectorWhite.end(), defeated), garbageCollectorWhite.end());

    mainBoard.removeMaterial(file, rank);
    mainBoard.moveMaterial(file, rank, selectedAttacker);

    return true;
}

bool Game::isValidAttackPosition(int file, int rank) const
{
    if (mainBoard.checkForRange(file, rank))
        return mainBoard.getSquare(file, rank).isAttacked();
    return false;
}

bool Game::anyMovesLeft()
{
    if (whosMove)
    {
        for (const auto &v : garbageCollectorWhite)
        {
            projectAttack(v->file_, v->rank_);
            if (mainBoard.anyAttackedSquare())
                return true;
        }
        return false;
    }
    else
    {
        for (const auto &v : garbageCollectorBlack)
        {
            projectAttack(v->file_, v->rank_);
            if (mainBoard.anyAttackedSquare())
                return true;
        }
        return false;
    }
}

void Game::playGame()
{
    char choice;
    while (true)
    {
        setUpGame();
        while (anyMovesLeft())
        {
            mainBoard.invalidateAttacked();
            if (draw())
                return;
            generateHTMLDOC();
            hasMoves = false;
            while (!hasMoves)
                selectPosition();
            generateHTMLDOC();
            selectPositionToMove();
            mainBoard.invalidateAttacked();
            generateHTMLDOC();
            std::cout << "FEN record:" << generateFEN() << std::endl;
        }
        congratulateToWinner();
        while (true)
        {
            std::cout << "Wanna play more games[Y\\n]? ";
            std::cin >> choice;
            if (tolower(choice) == 'n')
            {
                std::cout << "Good luck traveler\n";
                return;
            }
            else if (toupper(choice) == 'Y')
            {
                std::cout << "YAAAAAAAAAAY\n";
                break;
            }
            else
            {
                std::cout << "Typo?\n";
            }
        }
    }
}

bool Game::draw()
{
    char input;
    if (Game::halfMoveClock >= 50)
    {
        while (true)
        {
            std::cout << "Wanna claim a draw?[Y/n]" << std::endl;
            std::cin >> input;
            if (toupper(input) == 'Y')
                return true;
            else if (tolower(input) == 'n')
                return false;
            else
                std::cout << "Typo?" << std::endl;
        }
    }
    return false;
}

void Game::congratulateToWinner() const
{
    if (whosMove)
    {
        std::cout << "Black won by checkmate" << std::endl;
    }
    else
    {
        std::cout << "White won by checkmate" << std::endl;
    }
}

void Game::setUpGame()
{
    while (true)
    {
        std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        std::string inputFEN;
        int choice;
        std::cout << "Wanna play a new game or continue/resume from a FEN record\n0 - New game\n1 - Resume" << std::endl;
        std::cin >> choice;
        std::cin.ignore(1, '\n');
        switch (choice)
        {
        case 0:
            parseFEN(startingFEN);
            return;
        case 1:
            std::cout << "Input FEN record for continuation: ";
            std::getline(std::cin, inputFEN);
            parseFEN(inputFEN);

            return;
        default:
            std::cout << "Inproper selection. Select again please pretty." << std::endl;
        }
    }
}

std::string Game::generateFEN() const
{
    std::string returnStr;
    int countOfEmpty = 0;
    for (int i = 7; i > -1; --i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (!mainBoard.getSquare(i, j).isThereMaterial())
                ++countOfEmpty;
            else
            {
                if (countOfEmpty > 0)
                {
                    returnStr += std::to_string(countOfEmpty);
                    countOfEmpty = 0;
                }
                returnStr += mainBoard.getSquare(i, j).getMaterial()->getchar();
            }
        }
        if (countOfEmpty > 0)
        {
            returnStr += std::to_string(countOfEmpty);
            countOfEmpty = 0;
        }
        if (i > 0)
            returnStr += "/";
        else
            returnStr += " ";
    }
    if (whosMove)
        returnStr += "w ";
    else
        returnStr += "b ";

    if (castle & whitekingcastle)
        returnStr += "K";
    if (castle & whitequeencastle)
        returnStr += "Q";
    if (castle & blackkingcastle)
        returnStr += "k";
    if (castle & blackqueencastle)
        returnStr += "q";
    if (!castle)
        returnStr += "-";
    returnStr += " ";

    returnStr += enPassant;

    returnStr += " ";

    returnStr += std::to_string(halfMoveClock);

    returnStr += " ";

    returnStr += std::to_string(fullMoveNumber);

    return returnStr;
}
