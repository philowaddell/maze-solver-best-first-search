
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

/* Access user defined .txt and determin size of maze */
void get_size(int* rows, int* cols, char* fin)
{
	// Initialise file pointer and attempt to open file with read-only
	FILE* fp;

	if (fopen_s(&fp, fin, "r") != NULL) {
		printf("File not found. Press enter to exit.");
		getchar();
		exit(0);
	}

	// Read in first two integers from .txt, [rows][cols] 
	fscanf_s(fp, "%d %d", rows, cols, 2);

	// Array size is equal to maze size plus first 3 definiton rows
	*rows += 3;

	fclose(fp);		// Close file
}

/* Arranges contents of .txt in maze array */
int get_array(int** maze_arr, int* rows, int* cols, char* ch, char* fin)
{
	enum tab { tab = 9 };
	enum space { space = 32 };
	enum line_feed { line_feed = 10 };
	enum unassigned { unassigned = -1 };

	int i = 0;		// Row number
	int j = 0;		// Column number
	int num;		// Number read in  from .txt

	int n_nums = 0;		// Tracks number of integers read in

	// Initialise file pointer and open file with read-only
	FILE* fp;
	fopen_s(&fp, fin, "r");

	/* Reads in two characters at a time from .txt, that is a number and the white
		space following it, continue until the 'End of File' identifier is read */
	while (fscanf_s(fp, "%d%c", &num, ch, 2) != EOF)
	{
		n_nums++;	// Increment quantity of numbers

		// Copy current number to defined location in maze array
		maze_arr[i][j] = num;

		// If last char was TAB or SPACE increment cols
		if (*ch == tab || *ch == space)
		{
			j++;
			// Check for white space at end of line of text
			if (j == *cols && *ch == space) {
				fscanf_s(fp, "%c", ch, 1);
			}
		}
		// If last char was NEW LINE increment rows
		if (*ch == line_feed)
		{
			// Overwrite remaining memory locations in array row
			for (j += 1; j < *cols; j++) {
				maze_arr[i][j] = unassigned;
			}
			i++;
			j = 0;
		}
	}
	fclose(fp);		// Close file

	// Return number of integers read
	return n_nums;
}

/* Writes solution charater array to user defined .txt file */
void export_solution(char* solution, char* fout)
{
	// Initialise file pointer and open file with write+ privilages
	FILE* fSolution;

	fopen_s(&fSolution, fout, "w+");

	// Print number of steps in solution folled by the solution itself on a new line
	fprintf_s(fSolution, "%d\n%s", strlen(solution), solution, strlen(solution) + 1);
	fclose(fSolution);	// Close file
	return;
}

