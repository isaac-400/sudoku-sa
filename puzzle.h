/* puzzle.h - api for sudoku puzzles
 *
 * See IMPLEMENTATION for more details
 *
 * Isaac Feldman 2021
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdlib.h>
#include <stdio.h>

/* Global Types */
typedef struct puzzle puzzle_t; // the sudoku puzzle

/* puzzle_new - create and allocate a blank puzzle
 *
 * Creates a blank puzzle. 
 *
 * params: size - the width and height of the puzzle
 * returns: a pointer to a blank puzzle_t or NULL on error
 * memory contract: the puzzle returned must be free'd by the caller using puzzle_delete()
 */
puzzle_t* puzzle_new(const int size);


/* puzzle_load - read a puzzle in from file 
 *
 * loads a puzzle from file.
 * the puzzle must be valid or errors will occur
 *
 * params:fp - a FILE to read the puzzle from 
 *        size - the width and height of the puzzle
 * returns: a pointer to a blank puzzle_t or NULL on error
 * memory contract: the puzzle returned must be free'd by the caller using puzzle_delete()
 */
puzzle_t* puzzle_load(FILE* fp, const int size);


/* puzzle_generate - generate an unsolved sudoku
 * 
 * Generates a puzzle_t with some prefilled squares and some empty squares
 *
 * params: puzzle a blank puzzle
 *         num_filled is the number of clues in the puzzle (17<n<40)
 * returns: 0 on successful filling, -1 on failure
 * memory contract: none
 */
int puzzle_generate(puzzle_t* p, int num_filled);

/* puzzle_solve - solve an unfilled sudoku
 *
 * Solves a puzzle. The puzzle must have a valid number of clues and have a solution.
 *
 * params: p - puzzle to be solved
 *         max_moves - the max number of iterations, if 0 infinite
 * returns: number of solutions or -1 if falure; if max_moves has been reached without solved returns 0
 * memory contract: none
 */
int puzzle_solve(puzzle_t* p, int max_moves);

/* puzzle_print - print a sudoku to file 
 *
 * Prints the puzzle to the specified file pointer
 *
 * params: p - the puzzle to print
 *         fp - a FILE to print the puzzle to
 *returns: 0 on success, -1 on failure
 * memory contract: none
 */
int puzzle_print(puzzle_t* p, FILE* fp);

/* puzzle_delete - cleans up the memory footprint of the puzzle
 *
 * Frees the allocated memory of the data strucutre
 *
 * params: p - the puzzle to delete
 * returns: 0 on success, -1 on failure
 * memory contract: p must be in dynamic memory
 */
int puzzle_delete(puzzle_t* p);

#endif
