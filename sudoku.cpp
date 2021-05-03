#include "sudoku.h"
#include <iostream>
#include <random>
#include <chrono>
#define TRUE 1
#define FALSE 0
/*************************************************
* Function Title: Sudoku
* Summary: initializes the Sudoku with n numbers
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: the number to prepopulate
* Outputs: none
****************Pseudocode*********************
Begin
  create 3 random numbers
  loop for n times
    make sure we can place this number here
    table[random1(0-8)][random2(0-8)]=random3(1-9);
  if it fails run the loop n+1 times
  Show the grid
End
*************************************************/

Sudoku::Sudoku (int n) {
  //initialize a clock for random number
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();
  myclock::duration d = myclock::now() - beginning;
  //creating the random part
  unsigned seed2 = d.count();
  std::default_random_engine generator;
  //seeding the random part with the clock
  generator.seed (seed2);
  //give only numbers 1 through 9
  std::uniform_int_distribution<int> distribution(1,9);
  //create variables to store random numbers
  int randY,randX,randNum;
  //loop the random numbers as many times as user wants for numbers
  for (size_t i = 0; i < n; i++) {
    //assign random coordinate [0-8][0-8]
    randX = distribution(generator)-1;
    randY = distribution(generator)-1;
    //asign random value to location 1-9
    randNum = distribution(generator);
    //check if the position and value are valid moves
    if (isLegal(randX,randY,randNum)) {
      //sets value
      table[randX][randY] = randNum;
      //Says this is a fixed number
      fixed[randX][randY]=1;
    } else {
      //Do it again
      //removes 1 from increment so it will go again
      i--;
    }
  }
  printGrid();
}
/*************************************************
* Function Title: solve
*
* Summary: tries to solve the sudoku
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: none
* Outputs: Boolean of if the grid was solved
****************Pseudocode*********************
Begin
  make sure the grid isn't already full
    if it is full return TRUE
  check 1-9 on the empty cell
    if that worked call the function to solve the next cell
  if that doesn't work return false to back track
End
*************************************************/
int Sudoku::solve() {
  //create variables to store the next empty X and Y coordinate
  int nextEmptyX;
  int nextEmptyY;
  //if the grid is full then we're done so return TRUE
  //pass by reference to change values of next unnasigned
  if(full(&nextEmptyX, &nextEmptyY))
  return TRUE;
  //cycle through number 1 to 9
  for(int i=1;i<=NUM;i++)  {
    //if we can place it, try it (for now)
    if(isLegal(nextEmptyX, nextEmptyY, i)) {
      table[nextEmptyX][nextEmptyY] = i;
      //recursive call to self to find all possible values (backtracking)
      if(solve())
      return TRUE;
      //That didn't work, make it empty now and try again
      table[nextEmptyX][nextEmptyY]=0;
    }
  }
  //if we've tried all 9 numbers return false and
  //go back to previous call to solve
  return FALSE;
}
/*************************************************
* Function Title: printGrid
*
* Summary: prints out what is in the Sudoku
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: none
* Outputs: none (prints to screen)
****************Pseudocode*********************
Begin
  Go throw rows and columns
  after each row place extra |
  every 3rd colum place |
  if number is 0 replace with *
End
*************************************************/

void Sudoku::printGrid() {
  //cycles through all rows
  for (size_t i = 0; i < NUM; i++) {
    //every third row print the seperator
    if ((i%3==0)&&(i!=0)) {
      std::cout << "------------+-------------+------------\n";
    }
    //cycle all columns
    for (size_t j = 0; j < NUM; j++) {
      //every third column print the pipe
      if (j%3==0&&j!=0) {std::cout << "| ";}
      //if it has a value
      if (table[i][j] != 0) {
        //print the value with spaces for ASCII art
        std::cout << " " << table[i][j] << "  ";
      } else {
        //if value is 0 print an "*" in its place
        std::cout << " *  ";
      }
    }
    //after each row print the pipes for ASCII art
    std::cout << "\n            |             |\n";

  }
}
/*************************************************
* Function Title: isLegal
*
* Summary: checks if passed move is valid placement
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: x coordinate, y coordinate, and value to be set
* Outputs: bool: True if valid, FALSE if not valid placement
****************Pseudocode*********************
Begin
  check if the placement exists
  check if in same rows
  check same column
  check if in same cell
  Return true if we've reached this
End
*************************************************/

bool Sudoku::isLegal(int x,int y,int value) {
  //check if the coordinate that was passed already has a value
  if (table[x][y])
  return FALSE;
  //check if same number in similar row
  for (int i = 0; i <= 8; i++)
  if (table[i][y] == value)
  return FALSE;
  //check if same number in similar column
  for (int i = 0; i <= 8; i++)
  if (table[x][i] == value)
  return FALSE;
  //check if same number in similar cell
  int startRow = x - x % 3, startCol = y - y % 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (table[i + startRow][j + startCol] == value) {
        return FALSE;
      }
    }
  }
  //If you've gotten this far it's valid
  return TRUE;

}
/*************************************************
* Function Title: full
*
* Summary: checks if grid is full and if it isn't sets the
* value of the next empty cell
* Author: Weston Fausett
* Author A#: A02276419
* Inputs: Variable assigned to next empty Row and Column
* pass inputs by reference
* Outputs: Return TRUE if is full or FALSE if still going
****************Pseudocode*********************
Begin
  Go through each cell
    if cell is assigned continue
    find cell not assigned set it to next values
      return FALSE
  If gone through all values and all are filled then the grid is full
End
*************************************************/
int Sudoku::full(int *nextEmptyX, int *nextEmptyY) {
  //cycle through all rows
  for(int i=0;i< NUM;i++) {
    //cycles through all columns
    for(int j=0;j<NUM;j++) {
      //if cell is unassigned
      if(!table[i][j]) {
        //makes this the new empty place
        *nextEmptyX = i;
        *nextEmptyY = j;
        //we are not full yet
        return FALSE;
      }
    }
  }
  //All values have been assigned
  return TRUE;
}
