#include <functional>
#include <iostream>
#include <string>
#include <regex>
#include <ctype.h>
#include <game.hpp>


int main(void)
{
    Game m;
    // m.generateHTMLDOC();
    std::string input;
    std::cout << "Input Forsyth-Edwards chess notation: ";
    std::getline(std::cin, input);
    m.parseFEN(input);
    m.selectPosition();
    m.generateHTMLDOC();
}