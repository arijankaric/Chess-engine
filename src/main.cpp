#include <functional>
#include <iostream>
#include <string>
#include <regex>
#include <ctype.h>
#include <game.hpp>
#include <algorithm>
#include <chrono>




void test()
{
    
}

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

        auto start = std::chrono::high_resolution_clock::now();
        m.parseFEN(input);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by function parseFen: " << duration.count() << " microseconds" << std::endl;

        m.selectPosition();
        m.generateHTMLDOC();
        std::cout << "Wanna parse more FEN notations[Y\\n]: ";
        std::cin >> choice;
        std::cin.ignore(1, '\n');
    } while (tolower(choice) == 'y');
}