#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include "Sudoku.h"
#include <string>
#include <cmath>
#include <ncurses.h>

using namespace std;

int main(){
    cout << "\n\n\n\033[8;60;210t";
    system("clear");

    Sudoku game;
    game.generateGrid(2);
    game.printGrid();
    // game.generateGrid(1);
    // game.printGrid();

    return 0;

    // const string MORE = "#################   #########   #########   #######\n##     ###     ##   ##     ##   ##     ##   ##\n##     ###     ##   ##     ##   ##     ##   ##\n##     ###     ##   ##     ##   ##          ######\n##     ###     ##   ##     ##   ##          ##\n##     ###     ##   ##     ##   ##          ##\n##      #      ##   #########   ##          #######";
    // cout << MORE;
    
    // "#################   #########   #########   #######"
    // "##     ###     ##   ##     ##   ##     ##   ##"
    // "##     ###     ##   ##     ##   ##     ##   ##"
    // "##     ###     ##   ##     ##   ##          ######"
    // "##     ###     ##   ##     ##   ##          ##"
    // "##     ###     ##   ##     ##   ##          ##"
    // "##      #      ##   #########   ##          #######"

    // "#########  ##     ##   #########"
    // "##         ##     ##   ##     ##"
    // "##         ##     ##   ##     ##"
    // "########   ##     ##   ##     ##"
    // "##         ##     ##   ##     ##"
    // "##         ##     ##   ##     ##"
    // "##         #########   ##     ##"

    // std::cout << "\e[31m" << "Red text" << "\e[0m\n";  // Output red text
    // std::cout << "\e[42m" << "Green background" << "\e[0m\n";  // Output green background
    // std::cout << "\033[3;10H" << "Text at row 3, column 10\n";  // Output text at row 3, column 10
    // char * str = "Hello My Friend!!!! Yeah!!! ANNAAAAAAAA ;3";
    // printf("%*s\n", 50, str + );
    // return 0;

    // std::string content = "Hello, world!";

    // // Calculate the width of the terminal
    // int termWidth;
    // cout << "\033[7;t";  // Send query for terminal window size
    // cin >> termWidth;

    // // Calculate the width of the content
    // int contentWidth = content.size();

    // // Calculate the number of spaces to insert before and after the content
    // int numSpaces = (termWidth - contentWidth) / 2;

    // // Output the spaces and the content
    // std::cout << std::setw(numSpaces) << "" << content << std::endl;

    // return 0;

    // Set terminal color to white text on a blue background
    cout << "\033[1;37;44m";

    // Print text to the left side of the terminal
    cout << "Left " << "\033[0m" << "\n\n\n\n" << "\033[1;37;44m" << "Text";

    // Move the cursor to the middle of the terminal
    cout << "\033[40G";

    // Print text to the middle of the terminal
    cout << "Middle Text";

    // Move the cursor to the right side of the terminal
    cout << "\033[70G";

    // Print text to the right side of the terminal
    cout << "Right Text";

    // Reset terminal color to default
    cout << "\033[0m";

    return 0;

    // cout << "\033[41m";

    // // Print some text with the red background
    // cout << "Hello, World!\n";

    // // Reset the color to the default
    // cout << "\033[0m";

    // return 0;
}