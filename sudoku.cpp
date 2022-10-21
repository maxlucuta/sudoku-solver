#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* ------------------------- Question 1 ------------------------- */

/* Function that takes a 9x9 sudoku board as an
   argument, and returns True if the board is
   filled with digits, and false if there are
   empty spaces denoted by '.'  */
bool is_complete(const char board[9][9]) {

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (!isdigit(board[row][col])) {
	return false;
      }
    }
  }
  return true;
}

/* ------------------------- Question 2 ------------------------- */

/* helper function */
/* takes a letter - number string that denotes a position on
   a sudoku board (eg I8), and converts this into two integers
   which will allow for indexing the board. Function also takes
   the row and column references allowing them to be modified
   in place */
void decode(const char position[], int& row, int& col) {

  row = static_cast<int>(position[0]) - 65;
  col = static_cast<int>(position[1]) - 49;
}

/* helper function */
/* returns false if any row with a column value 'col' already has
   a digit in it equal to 'digit' (violates sudoku rules). Returns
   true otherwise  */
bool validate_row(int col, char digit, const char board[9][9]) {

  for (int r = 0; r < 9; r++) {
    if (digit == board[r][col]) {
      return false;
    }
  }
  return true;
}

/* helper function */
/* returns false if there is any column with a row value 'row'
   which has a digit in it equal to 'digit', as this violates 
   the rules of sudoku. Returns true otherwise */
bool validate_col(int row, char digit, const char board[9][9]) {

  for (int c = 0; c < 9; c++) {
    if (digit == board[row][c]) {
      return false;
    }
  }
  return true;
}

/* helper function */
/* takes the row and column of the square of interest, and finds out which
   3x3 subgrid it belongs in the sudoku grid. It then iterates through this
   grid to see if any value exists within it that equals the digit we want
   to place. If this is the case, false is returned as it violates sudoku
   rules, otherwise it will return true */
bool validate_subgrid(int row, int col, char digit, const char board[9][9]) {
  
  // defines the boundries of the 3x3 subgrid //
  int subgrid_row_start = row - (row % 3);
  int subgrid_col_start = col - (col % 3);

  // iterates through the 3x3 subgrid // 
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (digit == board[row + subgrid_row_start][col + subgrid_col_start]) {
	return false;
      }
    }
  }
  return true;
}

/* helper function */
/* checks if the row and column are within bounds
   of the 9x9 sudoku grid, if not the function will
   return false */
bool validate_position(int row, int col) {

  if (row < 0 || row > 8 || col < 0 || col > 8) {
    return false;
  }
  return true;
}

/* helper function */
/* calls all 4 validation functions mentioned above for a specified row, 
   column and digit, if all validation checks pass (ie they are all true)
   the function returns true, otherwise false */
bool validate_choice(int row, int col, char digit, const char board[9][9]) {

  bool is_valid_row = validate_row(col, digit, board);
  bool is_valid_col = validate_col(row, digit, board);
  bool is_valid_subgrid = validate_subgrid(row, col, digit, board);
  bool is_valid_position = validate_position(row, col);
  
  return is_valid_row && is_valid_col && is_valid_subgrid && is_valid_position;
}

/* main function */
/* takes a letter-digit position code and a digit of interest as 
   arguments, if the digit can be placed at the specified location
   without violating the rules of sudoku, the board will be updated
   with that digit and the function will return true. Otherwise 
   the board is not updated and the function returns false */
bool make_move(const char position[], char digit, char board[9][9]) {

  // decodes the charecter - integer position code //
  // to an indexable row, column integer //
  int row, col;
  decode(position, row, col);

  // if the we can place a digit without violating sudoku //
  // rules, update the board with the digit // 
  if (validate_choice(row, col, digit, board)) {
    board[row][col] = digit;
    return true;
  }
  return false;
}

/* ------------------------- Question 3 ------------------------- */

/* function that takes a file name string literal, and a sudoku board
   as arguments, and outputs the sudoku board to the file, maintaining
   a 9x9 structure */
bool save_board(const char filename[], const char board[9][9]) {

  ofstream out_stream;
  out_stream.open(filename);

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (out_stream.fail()) {
	return false;
      }
      out_stream << board[row][col];
    }
    // make a new line after we finish each row //
    out_stream << "\n";
  }

  out_stream.close();
  return true;
}

/* ------------------------- Question 4 ------------------------- */

/* helper function */
/* iterates through the sudoku board and updates a specified row and
   column in place via reference. If a charecter on the sudoku board
   is not a digit, then we have found the next empty box, and so the 
   function will return true, whilst updating the row and col. If not
   it means we have reached the end of the board, or the board is full
   and the function return false  */
bool get_next_position(int& row, int& col, const char board[9][9]) {

  for (row = 0; row < 9; row++) {
    for (col = 0; col < 9; col++) {
      if (!isdigit(board[row][col])) {
	return true;
      }
    }
  }
  return false;
}

/* helper function */
/* opposite of decode function, it turns a specified row and
   column into an letter-number string, which can be interpreted
   by the 'make_move' function mentioned above. A given position
   string is modified in place to reflect the encoding, and it is
   updated every time the function is called with unique row/col
   values */
/* Example input: position = "B6" , row = 1, col = 1 (these are
   the new row and columns). Position changes to "A1" to reflect
   the new row and col */
void encode(char position[], int row, int col) {

  char row_letter = static_cast<char>(row + 65);
  char col_number = static_cast<char>(col + 49);

  position[0] = row_letter;
  position[1] = col_number;
}

/* solves the sudoku board recursively by first finding an empty
   position, trying all digits from 1-9, and backtracking if a 
   decision made previously resulted in a 'bad choice'. The board is
   deemed solvable if the board is filled with digits, and the 
   get_next_position function returns true, otherwise, the recusive
   function will exhaust itself of all possible combinations and will
   return false */
bool solve_board(char board[9][9]) {

  // First we need to get the position of the //
  // next empty square, and convert this to //
  // an letter-number string //
  char position[3];
  int row, col;
  // if there are no more empty squares, we have //
  // completed the board, and hense return true //
  if (!get_next_position(row, col, board)) {
    return true;
  }
  encode(position, row, col);

  // try all digits from 1-9 and check if they can //
  // be placed in the empty square // 
  for (int i = 1; i < 10; i++) {
    // convert integer to equivalent charecter digit //
    char digit = static_cast<int>(i + 48);

    // if we can make a move, we update the board //
    // (see make_move function) and check if the //
    // proceeding move is successfull, if it is we //
    // return true //
    if (make_move(position, digit, board)) {
      if (solve_board(board)) {
	return true;
      }
      // if the proceeding attempt is unsuccessfull //
      // we need to backtrack by resetting the square //
      // to 'empty' and try other combinations //
      board[row][col] = '.';
    }
  }
  return false;
}
	  
/* ------------------------- Question 5 ------------------------- */

/* function with identical logic to solve_board() function */
/* has additional parameter 'iteration' which references a
   variable assigned in main(), this tracks the number of times
   the function needs to backtrack in order to solve the board,
   this is used as a proxy to find the complexity of the board */
bool solve_mystery_puzzle(char board[9][9], int& iterations) {

  char position[3];
  int row, col;
  if (!get_next_position(row, col, board)) {
    return true;
  }
  encode(position, row, col);

  for (int i = 1; i < 10; i++) {
    char digit = static_cast<int>(i + 48);
    if (make_move(position, digit, board)) {
      if (solve_mystery_puzzle(board, iterations)) {
	return true;
      }
      board[row][col] = '.';
      // increment when we backtrack //
      // ie. when we make a bad choice //
      iterations++;
    }
  }
  return false;
}

    
    
	
	
	
