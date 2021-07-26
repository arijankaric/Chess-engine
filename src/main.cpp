#include <functional>
#include <iostream>
#include <string>
#include <regex>
#include <ctype.h>
#include <game.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>




void benchmark()
{
    std::string line;
    std::ifstream ini_file {"../resources/testFEN.txt"};
    std::chrono::microseconds sum = std::chrono::microseconds(0);
    uint8_t count = 0;
    if(ini_file){
        while(getline(ini_file, line))
        {
            Game m;
            std::cout << line << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            m.parseFEN(line);
            m.selectPosition();
            m.generateHTMLDOC();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << duration.count() << std::endl;
            sum += duration;
            ++count;
            // m.generateHTMLDOC();
        }
    }
    else {
        printf("something went wrong inside test");
    }

    ini_file.close();
    std::cout << "Average duration: " << sum.count()/count << std::endl;
}

int main(int argc, char *argv[])
{

    benchmark();
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
        // auto fp = std::bind(&Game::parseFEN, m, std::placeholders::_1);
        // auto fp1 = std::bind(&Game::generateHTMLDOC, m);
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