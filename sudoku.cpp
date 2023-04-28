#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
using namespace std;
const int N = 9, B = 3;

struct Cell{
    int val;
    bool fixed;
    Cell() : val(0), fixed(false) {

    }

    bool update(const int &newVal){
        val = newVal;
        return true;
    }
};

class Sudoku {
    private:
        Cell grid[N][N];
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

        void generateGrid (int level){
            fillDiagonalBoxes();
            fillRemaining(0, B);
        }

        void print(){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    cout << grid[i][j].val << ' ';
                }
                cout << '\n';
            }
        }
};

int main(){

    Sudoku game;
    game.generateGrid(1);
    game.print();

    return 0;
}