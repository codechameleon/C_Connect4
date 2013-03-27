 
/* checks row for win */
int check_row_win(int currentR, int currentC, int num_rows, int num_columns,
				  int length_to_win, int array[num_rows][num_columns]);

/* checks column for win */
int check_column_win(int currentR, int currentC, int num_rows, int num_columns,
					 int length_to_win, int array[num_rows][num_columns]);

/* checks forward diaginal for win \ */
int check_forward_diaginal_win(int currentR, int currentC, int num_rows, int num_columns,
							   int length_to_win, int array[num_rows][num_columns]);

/* checks backward diaginal for win / */
int check_backward_diaginal_win(int currentR, int currentC, int num_rows, int num_columns,
								int length_to_win, int array[num_rows][num_columns]);

/* checks for a tie */
int check_tie(int num_rows, int num_columns, int array[num_rows][num_columns]);