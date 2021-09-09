#ifndef IO
# define IO

/* Access user defined .txt and determin size of maze */
void get_size(int* r, int* c, char* fin);

/* Arranges contents of .txt in maze array */
int get_array(int** txtArr, int* r, int* c, char* ch, char* fin);

/* Writes solution charater array to user defined .txt file */
void export_solution(char* solution, char* fout);


#endif