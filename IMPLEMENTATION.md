# Implementation Specifics

Overall structure:

* puzzle.h - api for the puzzle's structure and functions
* puzzle.c - the backend for that api
* sudoku.c - creates and solves puzzles

This is to keep the puzzle specific implementation details decoupled from the actual generator and solver.
Future versions of the solver may take advantages of better puzzle backends, so the exposed api in `puzzle.h` keeps this option open for now.


## puzzle.h

the puzzle data type
* constructor
* deconstructor
* printer
* move_checker


## sudoku.c

functions:
* create puzzle
* solve puzzle

