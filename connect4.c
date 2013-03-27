#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "connect4_engine.h"

#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define RESET "\033[0m"

/*
 * Converts input into integer for column selection
 */
int read_int(int *result)
{
	/* holds the input */
	char c, buff [ 13 ];
	
	/* 
	 * fget reads the line until the newline character and gets it
	 * from the keyboard (stdin). isspace checks for whitespace. 
	 */
	return fgets(buff, sizeof buff, stdin) && !isspace(*buff) &&
	sscanf(buff, "%d%c", result, &c) == 2 && (c == '\n' || c == '\0');
}

/*
 * Prompt player for input
 */
int prompt_player(int player, int num_rows, int num_columns, int game[num_rows][num_columns]) {
	
	int error = 1;
	int column;
	
	if (player == 0) {
		/* Prompts player 1 for input */
		fputs(MAGENTA "Player 1 enter a column: ", stdout);
			
			/* flushes the stdout and gets column number */
			fflush(stdout);
			read_int(&column);
			
			/* places the token if there is no error. if error 
			 * then the error code will be checked
			 */
			error = place_token(0,column,num_rows,num_columns,game);
			
			/* repeats input prompting until valid */
			while (error == 1) {
			fputs(MAGENTA "Player 1 enter a column: ", stdout);
			fflush(stdout);
			read_int(&column);
			error = place_token(0,column,num_rows,num_columns,game);
			}
	/* same for player 2 */
	} else {
		
		fputs(BLUE "Player 2 enter a column: ", stdout);
			fflush(stdout);
			read_int(&column);
			error = place_token(1,column,num_rows,num_columns,game);
			while (error == 1) {
				fputs(BLUE "Player 2 enter a column: ", stdout);
				fflush(stdout);
				read_int(&column);
				error = place_token(1,column,num_rows,num_columns,game);
			}
	}
}

/*
 * Main method to run connect 4 game
 */
int main(int argc, char **argv) {
	
	/* if no commands then default board
	 * and length to win sizes 
	 */
	if (argc == 1) {
		
		/* default setup */
		int game[8][8];
		int length_to_win = 4;
		int win = -1;
		
		
		initialize_board(8,8,game);
		
		while (win == -1) {
			
			/* prompt player 1 */
			prompt_player(0,8,8,game);
			
			/* checks if player won */
			win = winner(8,8,length_to_win,game);
			
			/* if win */
			if (win == 0) {
				printf(MAGENTA "Player 1 wins!\n" RESET);
				exit(0);
			}
			
			/* if tie */
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
			
			/* repeats same steps for player 2 */
			prompt_player(1,8,8,game);
			
			win = winner(8,8,length_to_win,game);
			if (win == 1) {
				printf(BLUE "Player 2 wins!\n" RESET);
				exit(0);
			}
			
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
		}
		
	/* 
	 * custom square board size and target to win
	 */
	} else if (argc == 3) {
		
		int board_size, length_to_win;
		int win = -1;
		
		
		/* gets board size if valid */
		if (sscanf (argv[1], "%d", &board_size) == 1) {
			
			/* board must be at least 3 */
			if (board_size < 3) {
				printf("Sorry board size must be at least 3\n");
				exit(1);
			}
			
		/* if invalid */
		} else {
			printf("Sorry invalid board size\n");
			exit(1);
		}
		
		/* gets length to win if valid */
		if (sscanf (argv[2], "%d", &length_to_win) == 1) {
			
			/* length to win must be at least 3 */
			if (length_to_win < 3) {
				printf("Sorry length to win must be at least 3\n");
				exit(1);
			}
			
		} else {
			printf("Sorry invalid length to win size\n");
			return -1;
		}
		
		/* if valid but impossible to win */
		if (length_to_win > board_size) {
			printf("Game will start but cannot be won\n");
		}
		
		/* initializes game */
		int game[board_size][board_size];
		initialize_board(board_size,board_size,game);
		
		/* takes turns */
		while (win == -1) {
			
			/* prompt player 1 */
			prompt_player(0,board_size,board_size,game);
			
			/* checks if player won */
			win = winner(board_size,board_size,length_to_win,game);
			
			/* if win */
			if (win == 0) {
				printf(MAGENTA "Player 1 wins!\n" RESET);
				exit(0);
			}
			
			/* if tie */
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
			
			/* repeats same steps for player 2 */
			prompt_player(1,board_size,board_size,game);
			
			win = winner(board_size,board_size,length_to_win,game);
			if (win == 1) {
				printf(BLUE "Player 2 wins!\n" RESET);
				exit(0);
			}
			
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
		}
		
	/* custom non square board */
	} else if (argc == 4) {
		
		int num_rows, num_columns, length_to_win;
		int win = -1;
		
		
		/* gets row size if valid */
		if (sscanf (argv[1], "%d", &num_rows) == 1) {
			
			/* board must be at least 3 */
			if (num_rows < 3) {
				printf("Sorry row must be at least 3\n");
				exit(1);
			}
			
		/* if invalid */
		} else {
			printf("Sorry invalid row size\n");
			exit(1);
		}
		
		/* gets column size if valid */
		if (sscanf (argv[2], "%d", &num_columns) == 1) {
			
			/* board must be at least 3 */
			if (num_columns < 3) {
				printf("Sorry column must be at least 3\n");
				exit(1);
			}
			
		/* if invalid */
		} else {
			printf("Sorry invalid column size\n");
			exit(1);
		}
		
		/* gets length to win if valid */
		if (sscanf (argv[3], "%d", &length_to_win) == 1) {
			
			/* length to win must be at least 3 */
			if (length_to_win < 3) {
				printf("Sorry length to win must be at least 3\n");
				exit(1);
			}
			
		} else {
			printf("Sorry invalid length to win size\n");
			return -1;
		}
		
		/* initializes game */
		int game[num_rows][num_columns];
		initialize_board(num_rows,num_columns,game);
		
		/* takes turns */
		while (win == -1) {
			
			/* prompt player 1 */
			prompt_player(0,num_rows,num_columns,game);
			
			/* checks if player won */
			win = winner(num_rows,num_columns,length_to_win,game);
			
			/* if win */
			if (win == 0) {
				printf(MAGENTA "Player 1 wins!\n" RESET);
				exit(0);
			}
			
			/* if tie */
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
			
			/* repeats same steps for player 2 */
			prompt_player(1,num_rows,num_columns,game);
			
			win = winner(num_rows,num_columns,length_to_win,game);
			if (win == 1) {
				printf(BLUE "Player 2 wins!\n" RESET);
				exit(0);
			}
			
			if (win == 2) {
				printf("Tie game!\n");
				exit(0);
			}
		}
		
	/* Invalid amount of arguements */
	} else if (argc > 4) {
		printf("Sorry invalid commands\n");
		return -1;
	}
	return 0;
}
