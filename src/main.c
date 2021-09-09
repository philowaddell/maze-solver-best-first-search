
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "display.h"		// Handles all functions that output to console
#include "solver.h"			// Handles all funtions regarding the solving of the maze	
#include "io.h"				// Handels all funtions that interact externally to executable

/* Expecting execution with arguments: [-d] MazeFileName SolutionFileName
in which [-d] is the optional display argument */

void main(int argc, char** argv) {
	// Maximum file name length for secure access
	enum max_fname_length { max_fname_length = 50 };

	char ch;			// Character from .txt
	int arr_rows;		// Rows in .txt
	int arr_cols;		// Columns in .txt

	// Initialise maze display to false by default	
	bool display = false;

	// Dynamically allocated memory for input and output file names
	char* fin = (char*)malloc(sizeof(char) * max_fname_length);
	char* fout = (char*)malloc(sizeof(char) * max_fname_length);

	// Expecting MazeFileName and SolutionFileName, assume display = false
	if (argc == 3)
	{
		fin = argv[1];		// Input file name
		fout = argv[2];		// Output file name
		display = false;	// Set display boolean
	}
	// Expecting MazeFileName and SolutionFileName, verify first arg = "-d"
	else if (argc == 4 && strcmp(argv[1], "-d") == 0)
	{
		fin = argv[2];		// Input file name
		fout = argv[3];		// Output file name					
		display = true;		// Set display boolean
	}
	// Exit programm if any other combination of arguments supplied
	else
	{
		// Hold open console unil propted by user
		printf("Incorrect arguments provided, press enter to exit.");
		getchar();
		exit(0);
	}

	// Access user defined .txt and determin size of maze
	get_size(&arr_rows, &arr_cols, fin);

	// Dynamically allocated memory for 2d maze array to hold contents from .txt
	int** maze_arr = (int**)malloc(arr_rows * sizeof(int*));
	for (int i = 0; i < arr_rows; i++) {
		maze_arr[i] = (int*)malloc(arr_cols * sizeof(int));
	}

	// Dynamically allocated memory for char arry to contain solution
	char* solution = (char*)malloc(arr_cols * arr_rows * sizeof(char));

	// Import contents of user defined .txt in to maze array
	get_array(maze_arr, &arr_rows, &arr_cols, &ch, fin);

	// Determin solution for maze
	solver(maze_arr, &*solution);

	// Export soltuion to .txt with user arguments
	export_solution(&*solution, &*fout);

	// Display maze and solution in console
	if (display == true) {
		draw_maze(maze_arr, &arr_rows, &arr_cols);
		print_solution(&*solution);
	}

	// Free dynamically allocated memory for int types
	free(maze_arr);

	// Hold open console unil propted by user
	printf("\n\nPress enter to exit.");
	getchar();
	exit(0);
}


