#include <functional>
#include <iostream>
#include <string>
#include <regex>
#include <ctype.h>
#include <game.hpp>

int main(int argc, char *argv[])
{
    // std::cout << argc << std::endl;
    if(argc > 1)
    {
        for(int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;
    }
    std::string input;
    char choice;
    do
    {
        Game m;
        std::cout << "Input Forsyth-Edwards chess notation: ";
        std::getline(std::cin, input);
        m.parseFEN(input);
        m.selectPosition();
        m.generateHTMLDOC();
        std::cout << "Wanna parse more FEN notations[Y\\n]: ";
        std::cin >> choice;
        std::cin.ignore(1, '\n');
    } while (tolower(choice) == 'y');
}