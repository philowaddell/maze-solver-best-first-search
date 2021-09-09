
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "solver.h"


/* Tracks number of available moves in current position and returns the
validilty of a given move */
weighted_exp is_valid(node* agent, int* valid_moves, char direction) {
	// Switch on direction
	switch (direction)
	{
		// Direction is UP
	case 'U':
		// If UP node isn't NULL
		if (agent->u != NULL) {
			*valid_moves += 1;	// Increase number of valid moves
			return true;
		}
		else
			return false;
		// Direction is LEFT
	case 'L':
		// If LEFT node isn't NULL
		if (agent->l != NULL) {
			*valid_moves += 1;	// Increase number of valid moves
			return true;
		}
		else
			return false;
		// Direction is DOWN
	case 'D':
		// If DOWN node isn't NULL
		if (agent->d != NULL) {
			*valid_moves += 1;	// Increase number of valid moves
			return true;
		}
		else
			return false;
		// Direction is RIGHT
	case 'R':
		// If RIGHT node isn't NULL
		if (agent->r != NULL) {
			*valid_moves += 1;	// Increase number of valid moves
			return true;
		}
		else
			return false;
	}
}

/* Move agent within linked list structure in give direction */
node make_step(node* agent, char direction) {
	// Switch on direction
	switch (direction)
	{
		// Change agent location one node ABOVE
	case 'U':
		agent = agent->u;
		break;
		// Change agent location one node LEFT
	case 'L':
		agent = agent->l;
		break;
		// Change agent location one node DOWN
	case 'D':
		agent = agent->d;
		break;
		// Change agent location one node RIGHT
	case 'R':
		agent = agent->r;
		break;
	}
	// Return agents new location
	return *agent;
}

/* Removes all pointers to the node the agent last occupied within the linked list structure */
void remove_nodes(node* agent, char direction)
{
	// Switch on direction
	switch (direction)
	{
		// Remove all pointers to node BELOW agent, providing they exhist
	case 'U':
		agent->d = NULL;
		if (agent->l != NULL)
			agent->l->r->d = NULL;
		if (agent->r != NULL)
			agent->r->l->d = NULL;
		if (agent->u != NULL)
			agent->u->d->d = NULL;
		break;
		// Remove all pointers to node RIGHT of agent, providing they exhist
	case 'L':
		agent->r = NULL;
		if (agent->l != NULL)
			agent->l->r->r = NULL;
		if (agent->u != NULL)
			agent->u->d->r = NULL;
		if (agent->d != NULL)
			agent->d->u->r = NULL;
		break;
		// Remove all pointers to node ABOVE agent, providing they exhist
	case 'D':
		agent->u = NULL;
		if (agent->l != NULL)
			agent->l->r->u = NULL;
		if (agent->r != NULL)
			agent->r->l->u = NULL;
		if (agent->d != NULL)
			agent->d->u->u = NULL;
		break;
		// Remove all pointers to node LEFT of agent, providing they exhist
	case 'R':
		agent->l = NULL;
		if (agent->r != NULL)
			agent->r->l->l = NULL;
		if (agent->u != NULL)
			agent->u->d->l = NULL;
		if (agent->d != NULL)
			agent->d->u->l = NULL;
		break;
	default:
		break;
	}
	return;
}

/* Tracks number of times a node has been explored */
void mark_explored(node* agent)
{
	agent->explored = yes;
	if (agent->r != NULL)
		agent->r->l->explored = yes;
	else if (agent->u != NULL)
		agent->u->d->explored = yes;
	else if (agent->d != NULL)
		agent->d->u->explored = yes;
	return;
}

/* Solves maze using two dimensional linked list structure */
void solver(int** maze_arr, char* solution)
{
	enum wall_above { wall_above = 8 };
	enum wall_left { wall_left = 4 };
	enum wall_below { wall_below = 2 };
	enum wall_right { wall_right = 1 };

	enum maze_arr_offset { maze_arr_offset = 3 };

	// Start location of maze
	location start = { .x = maze_arr[1][1],.y = maze_arr[1][0] };
	// End location of maze
	location end = { .x = maze_arr[2][1],.y = maze_arr[2][0] };
	// Size of maze
	location size = { .x = maze_arr[0][1],.y = maze_arr[0][0] };

	int h_min;				// Holds distance of closest node to finish from all nodes adjacent to agent
	int valid_moves;		// Tracks numbe of valid moves from agents position
	int solution_step = 0;	// Tracks number of steps in current exploration and final solution
	char direction = '0';	// Used to pass directional information between funtions and record solution

	/* Dynamically allocated memory for 2d array with same dimentions as the maze itself.
	Each cell contains a node structure and corresponds to a location within the maze */
	struct node** maze = (struct node**)malloc(size.y * sizeof(struct node*));
	for (int i = 0; i < size.y; i++) {
		maze[i] = (struct node*)malloc(size.x * sizeof(struct node));
	}

	/* Builds two dimensional linked list structure using array cells as node referances */
	// Cycles through rows
	for (int i = 0; i < size.y; i++)
	{
		// Cycles through columns
		for (int j = 0; j < size.x; j++)
		{
			// Copy wall descriptor from maze_arr
			maze[i][j].val = maze_arr[i + maze_arr_offset][j];
			// Calculate node distance from finish
			maze[i][j].h = abs(end.x - j) + abs(end.y - i);
			// Set explored equal to no (0) by default
			maze[i][j].explored = no;
			// If wall ABOVE...
			if (maze[i][j].val >= wall_above)
				maze[i][j].u = NULL;	// ... set pointer to NULL
										// Else point to node ABOVE
			else
				maze[i][j].u = &maze[i - 1][j];
			// If wall LEFT...
			if ((maze[i][j].val % wall_above) >= wall_left)
				maze[i][j].l = NULL;	// ... set pointer to NULL
										// Else point to node LEFT
			else
				maze[i][j].l = &maze[i][j - 1];
			// If wall BELOW ...
			if (((maze[i][j].val % wall_above) % wall_left) >= wall_below)
				maze[i][j].d = NULL;	// ... set pointer to NULL
										// Else point to node BELOW
			else
				maze[i][j].d = &maze[i + 1][j];
			// If wall RIGHT...
			if (((maze[i][j].val % wall_above) % wall_left) % wall_below >= wall_right)
				maze[i][j].r = NULL;   // ... set pointer to NULL
									   // Else point to node RIGHT
			else
				maze[i][j].r = &maze[i][j + 1];
		}
	}

	// Set agents position within maze equal to start position
	node agent = maze[start.y][start.x];

	// While the distance to the finish is not zero
	while (agent.h != 0)
	{
		valid_moves = 0;			// Zero valid moves for new position
		h_min = size.y * size.x;	// Make h_min large
		mark_explored(&agent);		// Mark current position as explored

		// If UP is a valid move AND next position is closest available, prioritising unexplored nodes
		if (is_valid(&agent, &valid_moves, 'U') && agent.u->h + agent.u->explored <= h_min) {
			direction = 'U';
			// Update distance + exploration of closest node
			h_min = agent.u->h + agent.u->explored;
		}
		// If LEFT is a valid move AND next position is closest available, prioritising unexplored nodes
		if (is_valid(&agent, &valid_moves, 'L') && agent.l->h + agent.l->explored <= h_min) {
			direction = 'L';
			// Update distance + exploration of closest node
			h_min = agent.l->h + agent.l->explored;
		}
		// If DOWN is a valid move AND next position is closest available, prioritising unexplored nodes
		if (is_valid(&agent, &valid_moves, 'D') && agent.d->h + agent.d->explored <= h_min) {
			direction = 'D';
			// Update distance + exploration of closest node
			h_min = agent.d->h + agent.d->explored;
		}
		// If RIGHT is a valid move AND next position is closest available, prioritising unexplored nodes
		if (is_valid(&agent, &valid_moves, 'R') && agent.r->h + agent.r->explored <= h_min) {
			direction = 'R';
			// Update distance + exploration of closest node
			h_min = agent.r->h + agent.r->explored;
		}

		// Move agent within linked list structure
		agent = make_step(&agent, direction);

		// If only one move was available or the location has been explored twice
		if (agent.explored == yes && valid_moves == 1) {
			// Remove all pointers to agents last location 
			remove_nodes(&agent, direction);
		}

		//	Record last movement into solution character array
		solution[solution_step] = direction;

		// Solution step back / step forward
		if (agent.explored == no) {
			solution_step++;
		}
		else {
			solution_step--;
		}
	}

	// Terminate solution string with null terminator
	solution[solution_step] = '\0';

	// Free dynamically allocated memory
	free(maze);
	return;
}