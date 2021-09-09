# maze-solver-best-first-search
Originally written April 2018 in C.

A maze solving program that interprets a maze structure from a given text file and returns to the user a sequence of moves that describe a solution.

Run the .exe using the sytax below:

```
solver.exe -d MazeFileName SolutionFileName
```

The -d flag text is optional, but can be used to diplay the maze in the console.

----------------------------------------------------------------------------------------------------

The format of the input text file is defined as follows:
-	First three lines contain two integers each. These describe the rows and columns (in that order) of the maze size, start position and end position
- All subsequent lines (one for each row) contain a set of integers (one for each column) which is the sum of variables that indicate the presence or absence of a wall: 
  - If the location has a wall above it, 8 has been added. 
  - If the location has a wall left of it, 4 has been added.
  - If the location has a wall below it, 2 has been added.
  - If the location has a wall right of it, 1 has been added
