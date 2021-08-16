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
For each of these sections will will maintain a set (hashset):

```
valid move(n, i, j):
  if n not in row i:
    if n not in row j:
      if n not in neighborhood N(i,j):
        return true
  return false
```

