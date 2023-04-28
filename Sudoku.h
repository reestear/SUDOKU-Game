#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Phrases.h"

using namespace std;

const int N = 9, B = 3;

#define MAGENTA_COLOR "\033[35m"
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define Wid "\033[82G";

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
    public:

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

        void clear(){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    grid[i][j] = Cell();
                }
            }
        }

        void generateGrid (int level){
            clear();

            fillDiagonalBoxes();
            fillRemaining(0, B);

            copyGird();

            switch (level)
            {
            case 1:
                removeK(55);
                break;
            case 2:
                removeK(60);
                break;
            case 3:
                removeK(65);
                break;
            default:
                break;
            }
        }

        void print(Cell board[N][N]){
            // clear();
            // system("clear");
            // cout << "\n\n\n\033[8;60;200t";
            // // cout << "some workd\nsdsdfsdfsf\n";
            // cout << setw(70) << left << "Left \nContent";

            cout << "\033[3;82H";
            // cout << "\n\n\n" << Wid;
            cout << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗" << endl; // 37 - length
            for(int i = 0; i < N; i++){
                cout << Wid;
                for(int j = 0; j < N; j++){
                    if(board[i][j].val != 0){
                        
                        if(j == 0 || j == 3 || j == 6) cout << "║ " << RED_COLOR << board[i][j].val << RESET_COLOR << " ";
                        else cout << "│ " << RED_COLOR << board[i][j].val << RESET_COLOR << " ";
                    }
                    else {
                        if(j == 0 || j == 3 || j == 6) cout << "║   ";
                        else cout << "│   ";
                    }
                }
                cout << "║\n";

                cout << Wid;
                if(i == 2 || i == 5) cout <<  "╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣" << endl;
                else if(i != 8) cout << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢" << endl;
            }
            cout << "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝" << endl;
        }

        void printGrid(){
            display(grid);
        }
        void printGridOriginal(){
            display(gridOriginal);
        }

        void printLeftSide(){
            cout << "\033[15G";
            cout << MORE << '\n';
            cout << "\n\n\n";
            cout << "\033[23G";
            cout << FUN;
        }

        void printRightSide(){
            cout << "\033[4;125H";
            cout << "\033[125G";
            cout << YEAH << "\n\n";
            cout << "\033[135G";
            cout << ACCOUNT << "\n\n\n\n\n";
        }

        void display(Cell board[N][N]){
            system("clear");
            cout << "\n\n\n\033[8;60;200t";
            // cout << setw(70) << left;

            printLeftSide();
            print(board);
            printRightSide();
        }
    
    ~Sudoku(){
    }
};