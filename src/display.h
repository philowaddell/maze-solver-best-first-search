#ifndef DISPLAY
# define DISPLAY

/* Prints contents of maze array into the console */
void print_arr(int** maze_arr, int* rows, int* cols);

/* Prints solution into the console */
void print_solution(char* solution);

/* Print maze structure to console identifying the start and finish locations */
void draw_maze(int** maze_arr, int* rows, int* cols);

#endif