#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include "Sudoku.h"
#include <string>
#include <cmath>
#include <ncurses.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <thread>

bool gameOver = false, gameWon = false;
Sudoku game(gameOver, gameWon);

using namespace std;

vector <int> records;

void clearCin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void input(){
    keypad(stdscr, TRUE);
    nodelay(stdscr, true); // make getch() non-blocking
    timeout(1000);

    int ch = getch();
    flushinp(); 
    
    if(ch == ERR) return;
    else game.handleKey(ch);

}

void parseRecords(int lvl){
    fstream infile("records.txt");

    records.erase(records.begin(), records.end());

    int gameLvl, timeS;

    while(infile >> gameLvl >> timeS){
        if(gameLvl == lvl){
            records.push_back(timeS);
        }
    }

    sort(records.begin(), records.end());
}

void playNext(){
    game.clearGame();
    gameOver = gameWon = false;
    cout << MAGENTA_COLOR;
    cout << "Choose the level EASY/MEDIUM/HARD (e/m/h): " << RESET_COLOR;

    char res;
    std::cin >> res;
    clearCin();

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    switch (res)
    {
    case 'e':
        parseRecords(1);
        game.start(1, records);
        break;
    case 'm':
        parseRecords(2);
        game.start(2, records);
        break;
    case 'h':
        parseRecords(3);
        game.start(3, records);
        break;
    default:
        break;
    }

    refresh();

    // time_t start_time = time(NULL);
    int elapsed_time = 0;

    while(!gameOver){
        game.display();
        input();

        pair <int, bool> ret = game.checkForWin();
        if(ret.second) gameOver = true, gameWon = true;
        elapsed_time = ret.first;
    }

    endwin();

    if(!gameWon){
        game.displayWithAnswers();

        cout << "\n\n\n\033[96G TRY AGAIN!\n\n\n\033[90G   ";
        printTime(elapsed_time);
    }   
    else{
        system("clear");
        cout << "\n\n\n\t\t\t\t\tYOU WON!\t";
        if(records.empty() || elapsed_time < records[0]) cout << "It is new record ";

        if(game.getLevel() == 1) cout << " on Easy!!!\t";
        else if(game.getLevel() == 1) cout << " on Medium!!!\t";
        else cout << " on Hard!!!\t";

        printTime(elapsed_time);

        ofstream outfile("records.txt", fstream::in | fstream::out | fstream::app);
        outfile << game.getLevel() << ' ' << elapsed_time << '\n';
    }

    cout << MAGENTA_COLOR << "Do you want to play again? YES/NO (y/n): ";


    std::cin >> res;
    clearCin();
    switch (res)
    {
    case 'y':
        system("clear");
        game.clearGame();
        playNext();
        break;
    
    default:
        break;
    }

}

int main(){
    srand(time(0));

    cout << "\n\n\n\033[8;60;210t";
    system("clear");

    cout << BLUE_COLOR << "\n\t\t\tWelcome to the Simple Sudoku Game :3\n\n";

    playNext();

    return 0;
}