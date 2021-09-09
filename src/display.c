
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "global.h"

/* Prints contents of maze array into the console */
void print_arr(int** maze_arr, int* rows, int* cols)
{
	// Cycle through rows
	for (int i = 0; i < rows; i++)
	{
		printf("\n ");		// Next row
		// Cycle through cols
		for (int j = 0; j < cols; j++)
			printf("%d ", maze_arr[i][j]);	// Print cell contents
	}
	printf("\n ");	// Print newline
}

/* Prints solution into the console */
void print_solution(char* solution)
{
	printf("\n\nSOLUTION \n");
	// Cycle through cells of char array
	for (int i = 0; i <= strlen(solution); i++) {
		printf("%c ", solution[i]);		// Print cell contents
	}
}

/* Print maze structure to console identifying the start and finish locations */
void draw_maze(int** maze_arr, int* rows, int* cols)
{
	enum wall_above { wall_above = 8 };
	enum wall_left { wall_left = 4 };

	// Starting point of wall definitions in maze_arr array
	location wall_def_start = { .x = 3, .y = 0 };
	// Location of start of maze
	location start = { .x = maze_arr[1][1],.y = maze_arr[1][0] + 3 };
	// Location of end of maze
	location end = { .x = maze_arr[2][1],.y = maze_arr[2][0] + 3 };

	printf("\n\x20\x20");		// Indent

	// Cycle rows of array containing wall definitions 
	for (int i = wall_def_start.x; i < *rows; i++)
	{
		// Repeat vertical walls twice
		for (int d = 0; d < 2; d++)
		{
			// Cycle columns of array
			for (int j = wall_def_start.y; j < *cols; j++)
			{
				// Printing horizontal walls (when d = 0)
				if (d == 0)
				{
					// If wall above print block
					if (maze_arr[i][j] >= wall_above)
						printf("\xDB\xDB\xDB\xDB");
					// Else if wall left print block
					else if (maze_arr[i][j] % wall_above >= wall_left)
						printf("\xDB\xDB\x20\x20");
					else if (maze_arr[i - 1][j] % wall_above >= wall_left)
						printf("\xDB\xDB\x20\x20");
					// Else if wall left-above print block
					else if (maze_arr[i][j - 1] >= wall_above)
						printf("\xDB\xDB\x20\x20");
					// Print space
					else
						printf("\x20\x20\x20\x20");
				}
				// If at start...
				else if (i == start.y && j == start.x)
				{
					if ((maze_arr[i][j] % wall_above) >= wall_left)
						printf("\xDB\xDB\ST");	// ... print block 'ST'
					else
						printf("\x20\x20\ST");	// ... print space 'ST'
				}
				// If at end...
				else if (i == end.y && j == end.x)
				{
					if ((maze_arr[i][j] % wall_above) >= wall_left)
						printf("\xDB\xDB\FN");	// ... print block 'FN'
					else
						printf("\x20\x20\FN");	// ... print space 'FN'
				}
				// Printing vertical walls (when d != 0)
				else
				{
					// If wall left print block, else print space
					if ((maze_arr[i][j] % wall_above) >= wall_left)
						printf("\xDB\xDB\x20\x20");
					else
						printf("\x20\x20\x20\x20");
				}
			}
			// Start new line
			printf("\xDB\xDB\n\x20\x20");
		}
	}
	// Draw bottom of maze for length of columns
	for (int d = 0; d < *cols; d++)
	{
		printf("\xDB\xDB\xDB\xDB");
	}
	printf("\xDB\xDB");
}


