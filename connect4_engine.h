
/* Places token */ 
int place_token(int player, int column, int num_rows, int num_columns,
				int board[num_rows] [num_columns]);

/* Check winner */
int winner(int num_rows, int num_columns, int length_to_win,
		   int array[num_rows] [num_columns]);

/* Initializes game board */
int initialize_board(int num_rows, int num_columns,
					 int board[num_rows][num_columns]);

/* Prints the board */
void print_board(int num_rows, int num_columns,
				 int board[num_rows][num_columns]);

/* Write last move */
void last_move(int row, int column);