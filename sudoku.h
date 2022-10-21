#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* Added for Q1 */
bool is_complete(const char board[9][9]);

/* Added for Q2 */
void decode(const char position[], int& row, int& col);
bool validate_row(int col, char digit, const char board[9][9]);
bool validate_col(int row, char digit, const char board[9][9]);
bool validate_subgrid(int row, int col, char digit, const char board[9][9]);
bool validate_choice(int row, int col, char digit, const char board[9][9]);
bool validate_position(int row, int col);
bool make_move(const char position[], char digit, char board[9][9]);

/* Added for Q3 */
bool save_board(const char filename[], const char board[9][9]);

/* Added for Q4 */
bool get_next_position(char position[], const char board[9][9]);
void encode(char position[], int row, int col);
bool solve_board(char board[9][9]);

/* Added for Q5 */
bool solve_mystery_puzzle(char board[9][9], int& iterations);

#endif
