/* puzzle.c - an implementation of puzzle.h using simulated annealing
 *
 * See IMPLEMENTATION for more details
 *
 * Isaac Feldman 2021
 */

#include <stdlib.h>
#include <stdio.h>


/* Global Types */
typedef struct puzzle {
  int size;
  int** values; // the values on the board
  int** prefilled; // 0 if prefilled, 1 if not
} puzzle_t; // the sudoku puzzle


void *
assertp(void *p)  // assert that a pointer is not null
{
  if (p == NULL) {
    fprintf(stderr, "MALLOC FAILED\n");
    exit (99);
  }
  return p;
}


/* puzzle_new - create and allocate a blank puzzle */
puzzle_t* puzzle_new(const int size)
{
  if (size < 9) {
    return NULL;
  }

  puzzle_t* p = assertp(calloc(1, sizeof(puzzle_t)));
  
  p->values = assertp(calloc(size, sizeof(int*)));
  p->prefilled = assertp(calloc(size, sizeof(int*)));

  for (int i = 0; i < size; i++) {
    int* row = assertp(calloc(size, sizeof(int)));
    int* prefilled_row = assertp(calloc(size, sizeof(int)));
    p->values[i] = row;
    p->prefilled[i] = prefilled_row;
  }

  p->size = size;
  return p;
}

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

/* puzzle_print - print a sudoku to file */
int puzzle_print(puzzle_t* p, FILE* fp)
{
  if (p == NULL || fp == NULL){
    return -1;
  }

  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      fprintf(fp, "%d", p->values[i][j]);
    }
    fputc('\n', fp);
  }
  return 0;
}


/* puzzle_delete - cleans up the memory footprint of the puzzle */
int puzzle_delete(puzzle_t* p) 
{
  if (p == NULL) {
    return -1;
  }

  for (int i = 0; i < p->size; i++) {
    free(p->values[i]);
    free(p->prefilled[i]);
  }

  free(p->values);
  free(p->prefilled);
  free(p);

  return 0;
}





