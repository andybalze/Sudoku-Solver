#ifndef SUDOKU_H
#define SUDOKU_H
#define NUM 9
class Sudoku {
  private:
    int table[NUM][NUM] = {0};
    bool fixed[NUM][NUM] = {0};
    int numberNotAssigned = 0;
    bool isLegal(int x,int y, int value);
    int full(int *row, int *col);
  public:
    Sudoku(int n);
    int solve();
    void printGrid();
};
#endif
