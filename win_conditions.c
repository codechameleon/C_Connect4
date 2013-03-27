#include <stdio.h>

/*
 * Checks for row wins (-). Returns -1 for no win,
 * 0 for player 1 win, 1 for player 2 win
 */
int check_row_win(int currentR, int currentC, int num_rows, int num_columns,
				  int length_to_win, int array[num_rows][num_columns]) {
	
	int m;
	int size = 0;
	
	/* temp row array to check */
	int check_row[num_columns];
	
	/* create the row from the last dropped token */
	for (m = 0; m < num_columns; ++m) {
		check_row[m] = array[currentR][m]; 
		size++;
	}
	
    return x_in_a_row(check_row,size,length_to_win);
}

/*
 * Checks for column wins (|). Returns -1 for no win,
 * 0 for player 1 win, 1 for player 2 win
 */
int check_column_win(int currentR, int currentC, int num_rows, int num_columns,
					 int length_to_win, int array[num_rows][num_columns]) {
	
	int n;
	int size = 0;
	
	/* temp column array arraw to check */
	int check_col[num_rows];
	
	/* create the column from the last dropped token */
	for (n = 0; n < num_rows; ++n) {
		check_col[n] = array[n][currentC];
		size++;
	}
	
	return x_in_a_row(check_col,size,length_to_win);
}

/*
 * Checks for forward diaginal win (\). Returns -1 for no win,
 * 0 for player 1 win, 1 for player 2 win
 */
int check_forward_diaginal_win(int currentR, int currentC, int num_rows, int num_columns,
							   int length_to_win, int array[num_rows][num_columns]) {
	
	int m;
	int size = 0;
	
	/* temp array to check win */
	int check_forw_diaginal[num_columns];
	
	/* check bottom half of board for left diaginal (\) */
	if (currentR > currentC) {
		
		/* get the row number of the first diaginal */
		while (currentC != 0) {
			currentC--;
			currentR--;
		}
		
		/* start from the spot of first diaginal. Then decrement down the diaginal bottom */
		for (m = 0; currentR < num_rows; ++m, ++currentR) {
			check_forw_diaginal[m] = array[currentR][m];
			size++;
		}
		
	/* check to see if it is on upper part of board */
	} else if ( currentC > currentR) {
		
		/* get the column number of the first diaginal */
		while (currentR != 0) {
			currentR--;
			currentC--;
		}
		
		for (m = 0; currentC < num_columns; ++m, ++currentC) {
			check_forw_diaginal[m] = array[m][currentC];
			size++;
		}
		
	/* We know that it falls in the middle diaginal */
	} else {
		for (m = 0; m < num_columns; ++m) {
			check_forw_diaginal[m] = array[m][m];
			size++;
		}
	}
	
	return x_in_a_row(check_forw_diaginal,size,length_to_win);
	
}

/*
 * Checks for backward diaginal win (/). Returns -1 for no win,
 * 0 for player 1 win, 1 for player 2 win
 */
int check_backward_diaginal_win(int currentR, int currentC, int num_rows, int num_columns,
								int length_to_win, int array[num_rows][num_columns]) {
	int m;
	int size = 0;
	
	/* temp array to check for win */
	int check_back_diaginal[num_columns];
	
	/* 
	 * while the left and bottom board boundaries are not hit. If
	 * initial spot is in column 0 then move on. If initial spot
	 * is not in column zero then try and find the bottom row or
	 * until column zero is hit. 
	 */
	while (currentC  > 0 && currentR < num_rows - 1) {
		currentC--;
		currentR++;
	}
	
	/*
	 * Gets the diaginal from the diagnal spot starting at the bottom left.
	 * We keep getting the diaginal position and adding it to a temp array
	 * until either the top row is hit or the farthest right column is hit.
	 */
	for (m = 0; currentC < num_columns && currentR >= 0; ++m, ++currentC, --currentR) {
		check_back_diaginal[m] = array[currentR][currentC];
		size++;
	}
		
	return x_in_a_row(check_back_diaginal,size,length_to_win);
}

/*
 * Checks if game board is full and there is a tie.
 * Returns -1 for no tie and 2 for tie
 */
int check_tie(int num_rows, int num_columns, int array[num_rows][num_columns]) {
	
	/* n and m cyle threw board. T is for tie */
	int n,m,t;
	t = 2;
	
	for (n = 0; n < num_rows; ++n) {
		for (m = 0; m < num_columns; ++m) {
			
			/* if there is an open spot left there is no tie */
			if (array[n][m] == -1) {
				t = -1;
			}
		}
	}
	return t;
}
