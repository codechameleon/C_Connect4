#include <stdio.h>
#include "x_in_a_row.h"
#include "win_conditions.h"

#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define RESET "\033[0m"


/* Global variables to store position of last inserted token */
int global_row,global_column;

/*
 * Prints the board to the terminal
 */
void print_board(int num_rows, int num_columns, int board[num_rows][num_columns]) {
	
	/* traverse threw the multidimensional array */
	int n,m;
	
	printf("\n");
	printf(MAGENTA "Player 1\n");
	printf(BLUE "Player 2\n" RESET);
	
	/* cycles threw the full board. printing X for blank, and colored 0's for players */
	for (n = 0; n < num_rows; ++n) {
		for (m = 0; m < num_columns; ++m) {
			switch (board[n][m]) {
				case -1: 
					printf("X ");
					break;
				case 0:
					printf(MAGENTA "0 " RESET);
					break;
				case 1:
					printf(BLUE "0 " RESET);
					break;
			}
		}
		printf("\n");
	}
	
	/* print column number heads below board if less than 10 */
	if (num_columns < 10) { 
		
		/* prints bottom row of board with (=) */
		for (m = 0; m < num_columns; ++m) {
			printf("= ");
		} 
		printf("\n");
		
		/* prints the column numbers below board */
		for (m = 0; m < num_columns; ++m) {
			printf("%d ", m);
		} 
	}
	printf("\n");
}

/*
 * Updates global variables to last token dropped location
 */
void last_move(int row, int column) {
	global_row = row;
	global_column = column;
}


/* 
 * Checks win conditions to determine if player who just placed token won
 */
int winner(int num_rows, int num_columns, int length_to_win, int array[num_rows] [num_columns]) {
	
	int win, currentC, currentR;
	
	currentC = global_column;
	currentR = global_row;
	
	/* check if there is a tie. Returns 2 if true */
	win = check_tie(num_rows, num_columns, array);
	if (win != -1) {
		return win;
	}
	
	/* check if a row win */
	win = check_row_win(currentR, currentC, num_rows, num_columns,
						length_to_win, array);
	if (win != -1) {
		return win;
	}
	
	/* check if a column win */
	win = check_column_win(currentR, currentC, num_rows, num_columns,
						   length_to_win, array);
	if (win != -1) {
		return win;
	}
	
	/* check if a forward diaginal win */
	win = check_forward_diaginal_win(currentR, currentC, num_rows, num_columns,
									 length_to_win, array);
	if (win != -1) {
		return win;
	}
	
	/* check if a backward diaginal win */
	win = check_backward_diaginal_win(currentR, currentC, num_rows, num_columns,
									  length_to_win, array);
	if (win != -1) {
		return win;
	}

	/* if no win */
	return -1;
}

/*
 * Places the token into the game. Returns 0 if token placed, 1 if it was not 
 */
int place_token(int player, int column, int num_rows, int num_columns, int board[num_rows] [num_columns]) {
	
	/* traverse threw the multidimensional array */
	int n,m;
	
	/* If column is valid */
	if (column < num_columns) {
		
		/*
		* We know the column number. So we loop threw the rows starting at the bottom
		* and look for an open spot in that column to place the token
		*/
		for (n = num_rows-1; n >= 0; --n) {
			
			/* if open spot */
			if (board[n][column] == -1) {
				
				/* insert player of token */
				if (player == 0) {
					board[n][column] = 0;
				} else {
					board[n][column] = 1;
				}
				
				/* print the board and set location of last token */
				print_board(num_rows,num_columns,board);
				last_move(n, column);
				return 0;
			} 
		}
		
		/* Column must be full */
		printf("\nSorry column full. Please try a different column\n");
		return 1;
		
	/* Column does not exist */
	} else {
		printf("\nSorry column does not exist. Please try a different column\n");
		return 1;
	}
}

 /*
 * Initial setup of board that makes everything empty(-1)
 */
int initialize_board(int num_rows, int num_columns, int board[num_rows][num_columns]) {
  
	/* traverse threw the multidimensional array */
	int n,m;
  
	/* Loop threw the board and set to empty (-1) */
	for (n = 0; n < num_rows; ++n) {
		for (m = 0; m < num_columns; ++m) {
			board[n][m] = -1;
		}
	}
	
	/* print the initial empty board */
	print_board(num_rows,num_columns,board);
	return 0;
}






