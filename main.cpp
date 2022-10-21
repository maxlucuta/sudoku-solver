#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";
  display_board(board);

  // write more tests

  /* Test 1: Check invalid move */
  /* Here we will give a grid coordinate that is out of bounds by letter*/
  /* Expected result: invalid move */
  cout << "===== Test 1 =====\n";
  cout << "Putting '1' into J7 is ";
  if (!make_move("J7", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 2: Check invalid move */
  /* Use an out of bounds grid coordinate by number */
  /* Expected result: invalid move */
  cout << "===== Test 2 =====\n";
  cout << "Putting '4' into B0 is ";
  if (!make_move("B0", '4', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 3: Check invalid move: by row */
  /* Place a number in a grid square that already has that number
     within the same row, see if it catches it out */
  /* Expected result: invalid move */
  cout << "===== Test 3 =====\n";
  cout << "Putting '1' into C6 is ";
  if (!make_move("C6", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 4: Check invalid move: by col */
  /* Place a number in a grid square that already has that number
     in the same column, see if this raises an error */
  /* expected result: invalid move */
  cout << "===== Test 4 =====\n";
  cout << "Putting '1' into D4 is ";
  if (!make_move("D4", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 5: check invalid move: by subgrid */
  /* Place a number in a grid square, that already exists
     within the parent 3x3 subgrid */
  /* Expected result: invalid move */
  cout << "===== Test 5 =====\n";
  cout << "Putting '7' into H3 is ";
  if (!make_move("H3", '7', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 6: check invalid input: non-empty square */
  /* Try place a number in a square that is already occupied
     by a number */
  /* expected result: invalid move */
  cout << "===== Test 6 =====\n";
  cout << "Putting '2' into B1 is ";
  if (!make_move("B1", '2', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n\n";
  /* result as expected */

  /* Test 7: check invalid input: parse number instead of letter */
  /* Instead of 'I8' which corresponds to a valid grid square, lets
     see what happens if I put '78' instead, which is not a valid
     grid code as the first charevter is not a capitalised letter 
     between A and I */
  /* Expected result: invalid move */
  cout << "===== Test 7 =====\n";
  cout << "Putting '1' into 78 is ";
  if (!make_move("78", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move\n\n";
  /* result as expected */

  
  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n'; 

  cout << "=================== Question 4 ===================\n\n";

  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  
  // write more tests //

  cout << "=================== Question 5 ===================\n\n";

  // write more tests

  /* For these tests, the number of times the function needs to 
     backtrack to reach a solution is used as to proxy how
     difficult the board is, where the greater number of iterations
     means higher difficulty, this number is stored in the mystery
     variables. */
  
  // Test 1: Mystery 1 // 
  int mystery1 = 0;
  load_board("mystery1.dat", board);
  if (solve_mystery_puzzle(board, mystery1)) {
    cout << "The 'mystery1' board has a solution:\n";
    cout << "It took " << mystery1 << " iterations.\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  // Extremely hard - most iterations //

  // Test 2: Mystery 2 //
  int mystery2 = 0;
  load_board("mystery2.dat", board);
  if (solve_mystery_puzzle(board, mystery2)) {
    cout << "The 'mystery2' board has a solution:\n";
    cout << "It took " << mystery2 << " iterations.\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  // Impossible - function returned false //
  
  // Test 3: Mystery 3 //
  int mystery3 = 0;
  load_board("mystery3.dat", board);
  if (solve_mystery_puzzle(board, mystery3)) {
    cout << "The 'mystery3' board has a solution:\n";
    cout << "It took " << mystery3 << " iterations.\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  // Hard - least number of iterations //
  
  return 0;
}
