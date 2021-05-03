#include "sudoku.h"
#include <iostream>

using namespace std;

/*************************************************
* Function Title: main
*
* Summary: Prompts for prepopulated sqaure amount and
* start Sudoku
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: none
* Outputs: 0 for success
****************Pseudocode*********************
Begin
  //Welcome the user
  //ask for their number they want
  //initialize the Sudoku
  if the sudoku is solved
    print the grid
  else
  give error
End
*************************************************/


int main(void) {
  int n;
  //Welcome the user
  cout << "Welcome to SudokuSolver!!" << endl;
  cout << "Enter number of squares to prepopulate: ";
  //ask for their number they want
  cin >> n;
  //initialize the Sudoku
  Sudoku s(n);
  //if the sudoku is solved
  if (s.solve()) {
    cout << "Solved!" << endl;
    //print grid
    s.printGrid();
  }
  else {
    //give error
    cout << "Sorry, unsolvable..." << endl;
  }
  //return 0 for complete successfully
  return 0;
}
