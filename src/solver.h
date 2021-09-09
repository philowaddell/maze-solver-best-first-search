#ifndef SOLVER
# define SOLVER

/* Exploration weighting on maze traversal decision */
enum exp_weight { exp_weight = 3 };

/* Exploration variable  */
typedef int weighted_exp;
#define yes exp_weight
#define no 0

/* 4-Way linked list node structure */
typedef struct node {
	weighted_exp explored;	// Node exploration status
	int val;				// Wall descirptor from maze_arr
	int h;					// Node distance from finish
	struct node* l;			// Pointer to left node
	struct node* r;			// Pointer to right node
	struct node* u;			// Pointer to above node	
	struct node* d;			// Pointer to below node
} node;

/* Tracks number of available moves in current position and returns the validilty of a given move */
weighted_exp is_valid(node* agent, int* valid_moves, char direction);

/* Move agent within linked list structure in give direction */
node make_step(node* agent, char direction);

/* Removes all pointers to the node the agent last occupied within the linked list structure */
void remove_nodes(node* agent, char direction);

/* Tracks number of times a node has been explored */
void mark_explored(node* agent);

/* Solves maze using two dimensional linked list structure */
void solver(int** maze_arr, char* solution);

#endif