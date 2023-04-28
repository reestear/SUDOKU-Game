#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
using namespace std;
const int N = 9, B = 3;

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

        void generateGrid (int level){
            fillDiagonalBoxes();
            fillRemaining(0, B);
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

        void print(){
            cout << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗" << endl;
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    // cout << grid[i][j].val << ' ';
                    if(grid[i][j].val != 0){
                        if(j == 0 || j == 3 || j == 6) printf("║ %i ", grid[i][j].val);
                        else printf("│ %i ", grid[i][j].val);
                    }
                    else {
                        if(j == 0 || j == 3 || j == 6) printf("║   ");
                        else printf("│   ");
                    }
                }
                cout << "║\n";
                
                if(i != 8) cout << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢" << endl;
            }
            cout << "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝" << endl;
        }
};

int main(){

    Sudoku game;
    game.generateGrid(1);
    game.print();

    return 0;
}