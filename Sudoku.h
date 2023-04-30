#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Phrases.h"
#include <ncurses.h>
#include <vector>
#include <time.h>

using namespace std;

const int N = 9, B = 3;

#define MAGENTA_COLOR "\033[35m"
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define CYAN_COLOR "\033[36m"
#define WHITE_COLOR "\033[37m"

#define BACK_WHITE "\033[47m"
#define BACK_BLACK "\033[40m"

#define Wid "\033[82G";

void printTime(int seconds){
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds %= 60;

    cout << "The Time: " << hours/10 << hours%10 << ":" << minutes/10 << minutes%10 << ":" << seconds/10 << seconds%10 << "\n\n\n";
}

void printTopTime(int seconds){
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds %= 60;

    cout << hours/10 << hours%10 << ":" << minutes/10 << minutes%10 << ":" << seconds/10 << seconds%10 << "\n\n\n";
}

struct Cell{
    int val;
    bool fixed;
    Cell() : val(0), fixed(true) {

    }

    bool update(const int &newVal){
        val = newVal;
        return true;
    }
};

class Sudoku {
    private:
        Cell grid[N][N];
        Cell gridOriginal[N][N];
        int level;
        int cRow, cCol;
        int btnSwitch;
        bool *gameOver, *gameWon;
        int correctSum;
        vector <int> bestRecords;
        time_t startTimeS;
    public:

        Sudoku(bool &gameOver, bool &gameWon){
            this->gameOver = &gameOver;
            this->gameWon = &gameWon;
        }

        int randomNum(){
            return (int) rand() % N + 1;
        }

        bool notInBox(int row, int col, int num){
            for(int i = 0; i < B; i++){
                for(int j = 0; j < B; j++){
                    if(grid[row + i][col + j].val == num) return false;
                }
            }

            return true;
        }

        void fillBox(int row, int col){
            int num;
            for (int i = 0; i < B; i++)
            {
                for(int j = 0; j < B; j++){
                    do{
                        num = randomNum();
                    } while(!notInBox(row, col, num));

                    grid[row + i][col + j].val = num;
                }
            }
            
        }

        void fillDiagonalBoxes (){
            for(int i = 0; i < N; i += B){
                fillBox(i, i);
            }
        }

        // done with filling diagonal boxes

        bool checkSafe(int row, int col, int num){
            return notInRow(row, num) && notInCol(col, num) && notInBox(row - row % B, col - col % B, num);
        }

        bool notInRow(int row, int num){
            for(int i = 0; i < N; i++){
                if(grid[row][i].val == num) return false;
            }

            return true;
        }

        bool notInCol(int col, int num){
            for(int i = 0; i < N; i++){
                if(grid[i][col].val == num) return false;
            }

            return true;
        }

        bool fillRemaining(int i, int j){

            if (j >= N && i < N - 1) {
                i = i + 1;
                j = 0;
            }
            if (i >= N && j >= N) {
                return true;
            }
            if (i < B) {
                if (j < B) {
                    j = B;
                }
            }
            else if (i < N - B) {
                if (j == (int)(i / B) * B) {
                    j = j + B;
                }
            }
            else {
                if (j == N - B) {
                    i = i + 1;
                    j = 0;
                    if (i >= N) {
                        return true;
                    }
                }
            }
            for (int num = 1; num <= N; num++) {
                if (checkSafe(i, j, num)) {
                    grid[i][j].val = num;
                    if (fillRemaining(i, j + 1)) {
                        return true;
                    }
                    grid[i][j].val = 0;
                }
            }
            return false;
        }

        void removeK(int k){
            for(int i = 0; i < k; i++){
                int ind = (int) rand() % (N * N);
                int row = ind / N, col = ind % N;

                if(grid[row][col].fixed == false) i--;
                else grid[row][col].update(0), grid[row][col].fixed = false;
            }
        }

        void copyGird(){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    gridOriginal[i][j].val = grid[i][j].val;
                }
            }
        }

        void clearGame(){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    grid[i][j] = Cell();
                }
            }
        }

        void generateGrid (int level){
            clearGame();

            fillDiagonalBoxes();
            fillRemaining(0, B);

            copyGird();

            switch (level)
            {
            case 0:
                removeK(1); // devOption
                break;
            case 1:
                removeK(45);
                break;
            case 2:
                removeK(50);
                break;
            case 3:
                removeK(55);
                break;
            default:
                break;
            }
        }

        void print(Cell board[N][N]){

            cout << "\033[3;82H";
            // cout << "\n\n\n" << Wid;
            cout << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗" << endl; // 37 - length
            for(int i = 0; i < N; i++){
                cout << Wid;
                for(int j = 0; j < N; j++){

                    string backgroundColor, textColor;
                    if(i == cRow && j == cCol) backgroundColor = BACK_WHITE;
                    else RESET_COLOR;

                    if(btnSwitch != -1) backgroundColor = BACK_BLACK;

                    if(grid[i][j].fixed) textColor = RED_COLOR;
                    else textColor = RESET_COLOR;

                    if(board[i][j].val != 0){

                        if(j == 0 || j == 3 || j == 6) cout << "║" << textColor << backgroundColor << ' ' << board[i][j].val << " " << RESET_COLOR;
                        else cout << "│" << textColor << backgroundColor << ' ' << board[i][j].val << " " << RESET_COLOR;
                    }
                    else {
                        if(j == 0 || j == 3 || j == 6) cout << "║" << backgroundColor << "   " << RESET_COLOR;
                        else cout << "│" << backgroundColor << "   " << RESET_COLOR;
                    }
                }
                cout << "║\n";

                cout << Wid;
                if(i == 2 || i == 5) cout <<  "╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣" << endl;
                else if(i != 8) cout << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢" << endl;
            }
            cout << "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝" << endl;
        }

        void printLeftSide(){
            cout << "\033[4;15H";
            cout << "\033[15G";
            cout << BLUE_COLOR;
            cout << MORE << '\n';
            cout << "\n\n\n";
            cout << "\033[23G";
            cout << YELLOW_COLOR;
            cout << FUN;
            cout << RESET_COLOR;
        }

        void printRightSide(){
            cout << "\033[4;125H";
            cout << "\033[125G";
            cout << YELLOW_COLOR;
            cout << YEAH << "\n\n";
            cout << "\033[135G";
            cout << GREEN_COLOR;
            cout << ACCOUNT << "\n\n\n";
            cout << RESET_COLOR;
        }

        void printButtons(){
            string backColorAgain = (btnSwitch == 0) ? BACK_WHITE : RESET_COLOR;
            string backColorSolution = (btnSwitch == 1) ? BACK_WHITE : RESET_COLOR;

            cout << CYAN_COLOR;
            cout << "\n\033[82G";
            cout << "╔═══════════════╗   ╔═══════════════╗\n\033[82G";
            cout << "║ " << backColorAgain << CYAN_COLOR << "    AGAIN    " << RESET_COLOR << CYAN_COLOR << " ║   ║ " << backColorSolution << CYAN_COLOR << "   SOLUTION  " << RESET_COLOR << CYAN_COLOR << " ║\n\033[82G";
            cout << CYAN_COLOR;
            cout << "╚═══════════════╝   ╚═══════════════╝\n";
            cout << RESET_COLOR;

        }

        void printBestRecords(){
            cout << "\n\033[82G    Top 5 the Best Records on ";
            if(level == 1) cout << "easy:";
            else if(level == 2) cout << "medium:";
            else cout << "hard:";
            cout << "\n\n\n";

            for(int i = 0; i < 5 && i < bestRecords.size(); i++){
                cout << "\033[88G" << "       #" << i + 1 << ": ";
                printTopTime(bestRecords[i]);
                cout << "\n\n";
            }
        }

        void showTimer(){
            cout << "\n\n\n\033[93G Timer: ";
            printTopTime(time(NULL) - startTimeS);
        }

        int getLevel(){
            return level;
        }

        void display(){
            system("clear");
            // clear();
            cout << "\n\n\n\033[8;60;210t";
            // cout << setw(70) << left;

            printLeftSide();
            print(grid);
            printRightSide();
            printButtons();

            showTimer();
        
            printBestRecords();
        }

        void displayWithAnswers(){
            system("clear");
            // clear();
            cout << "\n\n\n\033[8;60;200t";
            // cout << setw(70) << left;

            printLeftSide();
            print(gridOriginal);
            printRightSide();
        }

        void enterNumber(int key){
            if(0 <= cRow && cRow < N && 0 <= cCol && cCol < N && btnSwitch == -1){
                if(!grid[cRow][cCol].fixed){

                    if(grid[cRow][cCol].val != key - '0' && key - '0' == gridOriginal[cRow][cCol].val) correctSum++;
                    else if(grid[cRow][cCol].val != key - '0' && grid[cRow][cCol].val == gridOriginal[cRow][cCol].val) correctSum--;

                    grid[cRow][cCol].val = key - '0';
                }
            }
        }
        
        void delNumber(){
            if(0 <= cRow && cRow < N && 0 <= cCol && cCol < N && btnSwitch == -1){
                if(!grid[cRow][cCol].fixed){

                    if(grid[cRow][cCol].val == gridOriginal[cRow][cCol].val) correctSum--;

                    grid[cRow][cCol].val = 0;
                }
            }
        }

        void switchToButtons(int n){
            btnSwitch = n / 5;
        }

        void switchToCells(){
            btnSwitch = -1;
        }

        void startAgain(){
            clearGame();
            start(level, bestRecords);
        }

        void endGameShowingSolutions(){
            *gameOver = true;
            *gameWon = false;
            displayWithAnswers();
        }

        void handleKey(int key){
            switch (key)
            {
            case 'W' | 'w':
                if(btnSwitch != -1) switchToCells();
                else cRow = (cRow > 0) ? cRow - 1 : 0;

                break;
                
            case 'S' | 's':
                if(cRow < N - 1) cRow++;
                else switchToButtons(cCol);

                break;

            case 'A' | 'a':
                if(btnSwitch != -1) btnSwitch = 0;
                else cCol = (cCol > 0) ? cCol - 1 : 0;

                break;

            case 'D' | 'd':
                if(btnSwitch != -1) btnSwitch = 1;
                else cCol = (cCol < N - 1) ? cCol + 1 : N - 1;

                break;
            case '\n':
                if(btnSwitch == 0) startAgain();
                else if(btnSwitch == 1) endGameShowingSolutions();

            default:
                break;
            }

            if('0' <= key && key <= '9') enterNumber(key);
            else if(key == 127) delNumber();
            else if(key == 'q' || key == 'Q'){
                endwin();
                system("clear");
                exit(0);
            }
            
        }

        int getRem(int lvl){
            if(lvl == 0) return 81 - 1; // devOption

            if(lvl == 1) return 81 - 45;

            if(lvl == 2) return 81 - 50;

            return 81 - 55;
        }

        bool checkForWin(){
            refresh();
            return correctSum == N * N;
        }

        void start(int lvl, vector <int> records){
            level = lvl; // devOption
            // level = lvl;
            bestRecords = records;
            startTimeS = time(NULL);
            cRow = cCol = 4;
            btnSwitch = -1;
            correctSum = getRem(level);

            cout << "\n\n\n\033[8;60;210t";
            // system("clear");
            // clear();

            generateGrid(level);
            display();
        }
    
    ~Sudoku(){
    }
};