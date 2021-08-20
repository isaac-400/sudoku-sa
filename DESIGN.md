# Sudoku Solver Design Document

## Tasks:
  * Puzzle data structure
  * Generation
  * Solving
    * Algorithm (backtracking)



## Puzzle Data Strucuture

Requirements: puzzle is implemented as a 9x9 plaintext grid of ints from 0-9 such that zero represents an open square.

Key Problems:
  * store the puzzle so accessing is easy
  * store the puzzle as to not change already filled sections

Approach: Internally, the puzzle is stored as an array and some accompanying data structures to help speed up solving

### Arrays

#### Value Array
To store the values for each cell, the straightforward approach is to use a 2D array. 
So for row i and column j we can set and fetch the value in the puzzle in constant time.

#### Editable Array
As to not disturb the puzzle's pre-filled in clues, we implement a secondary array which stores whether a value is mutable.

### Sets
Essential for determining if a move is valid is checking if a number is already included in the row, column or neighborhood. 
For each of these sections will will maintain a set. 
These sets will likely be implemented with arrays as we know exactly how many items at most will be in the set and we have integer keys.

```
valid move(n, i, j):
  if n not in row i:
    if n not in row j:
      if n not in neighborhood N(i,j):
        return true
  return false
```

## Puzzle Generation

First create a solved sudoku puzzle. This can be done by filling a grid with the proper numbers and performing random swaps until the board is valid.  
 
Follow the simulated annealing process as defined by the attached paper.

## Puzzle Solving

Use a simple backtracking algorithm. 

1. Fill the current square in a valid way.
2. Fill the next square
  a. if there are no valid ways to fill the square, backtrack to the previous square and redo (1) and choose the next valid number
  b. continue to the next square and do (1)

Repeat until all squares are filled. This is not elegant, but it does the job for 9x9 puzzles.

For the future: implement a stochastic solver.
