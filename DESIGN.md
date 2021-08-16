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

## Puzzle Generation

[The general algorithm for making the solved puzzles](https://www.algosome.com/articles/create-a-solved-sudoku.html)
[the removing part](https://www.createclassicsudoku.com/helpcenter_how_to_make_a_sudoku_fillremovemethod.jsp)
  
The general idea here is to create a random, fully-solved sudoku and remove numbers carefully to generate an unsolved puzzle.

## Puzzle Solving

Use a simple backtracking algorithm. 

1. Fill the current square in a valid way.
2. Fill the next square
  a. if there are no valid ways to fill the square, backtrack to the previous square and redo (1) and choose the next valid number
  b. continue to the next square and do (1)

Repeat until all squares are filled. This is not elegant, but it does the job for 9x9 puzzles.

For the future: implement a stochastic solver.
