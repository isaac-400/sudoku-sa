/* puzzle.c - an implementation of puzzle.h using simulated annealing
 *
 * See IMPLEMENTATION for more details
 *
 * Isaac Feldman 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/readlinep.h"


/* Global Types */
typedef struct puzzle {
  int size;
  int** values; // the values on the board
  int** prefilled; // 0 if prefilled, 1 if not
} puzzle_t; // the sudoku puzzle

/* Local functions */
puzzle_t* pick_neighbhours(puzzle_t* p);
bool copy_board(puzzle_t* p, puzzle_t* copy);
int energy(puzzle_t* p);


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

/* puzzle_load */
puzzle_t* puzzle_load(FILE* fp, const int size)
{
  if (fp == NULL || size <  9) {
    return NULL;
  }

  puzzle_t* p = puzzle_new(size);

  for (int i = 0; i < size; i++) {
    char* line = freadlinep(fp); // read a line
    char* tok = strtok(line, " "); // tokenize the line
    if (tok == NULL) {
      return NULL;
    }
    for (int j = 0; j < size; j++) {
      int val = atoi(tok);
      p->values[i][j] = val;    // save each number
      if (val != 0) {           // if there's a number, mark it as prefilled
      p->prefilled[i][j] = 1;
      }
    tok = strtok(NULL, " ");
    }
    free(line);
  }
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

/* pick_neighbour - find a candidate move */
puzzle_t* pick_neighbour(puzzle_t* p)
{
    
  puzzle_t* res = puzzle_new(p->size); // an empty neighbor

  int i = rand() % 9;     // pick a random cell 
  int j = rand() % 9;
  
  while (p->prefilled[i][j]) { // so it is not fixed
    i = rand() % 9;
    j = rand() % 9;
  }

  int k = (rand() % 3) - i % 3; // pick another cell that is not prefixed
  int l = (rand() % 3) - i % 3; // but also in the same square as (i,j)
  
  while (p->prefilled[k][l] || i == k || j == l) {
    k = (rand() % 3) - i % 3; 
    l = (rand() % 3) - j % 3;
  }
  
  if (!copy_board(p, res)) { return NULL; } // copy the values from p to res
  
  int temp_val = res->values[k][l];
  int temp_prefilled = res->prefilled[k][l];

  res->values[k][l] = p->values[i][j];
  res->values[i][j] = temp_val; 

  res->prefilled[k][l] = p->prefilled[i][j];
  res->prefilled[i][j] = temp_prefilled; 

  return res;

}

/* copy_board - copy the values and prefilled arrays from one puzzle to another */
bool copy_board(puzzle_t* p, puzzle_t* copy)
{
  if (p == NULL || copy == NULL){
    return false;
  } 

  if (p->size != copy->size)
  {
    return false;
  }

  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      copy->values[i][j] = p->values[i][j];
      copy->prefilled[i][j] = p->prefilled[i][j];
      // update scores for the swapped rows and cols
    }
  }
  return true;
}

/* energy - calc the cost func for a board */
int energy(puzzle_t* p) 
{
  if (p == NULL)
  {
    return -1;
  }
  int row_scores = 0;
  // calc row scores
  for (int i = 0; i < p->size; i++) {
    int row = 0;
    int reg[10] = {0,0,0,0,0,0,0,0,0,0};  // hold values [0-9]

    for (int j = 0; j < p->size; j++) {
      reg[p->values[i][j]] = 1; 
    }

    for (int j = 1; j < 10; j++) {
      if (reg[j] == 0) {
        row++;
      }
    }

    row_scores += row;
    }


  int col_scores = 0;
  // calc column scores
  for (int i = 0; i < p->size; i++) {
    int col = 0;
    int reg[10] = {0,0,0,0,0,0,0,0,0,0};  // hold values [0-9]

    for (int j = 0; j < p->size; j++) {
      reg[p->values[j][i]] = 1; 
    }

    for (int j = 1; j < 10; j++) {
      if (reg[j] == 0) {
        col++;
      }
    }

    col_scores += col;
    }


  return row_scores + col_scores;
  
 }




/* puzzle_print - print a sudoku to file */
int puzzle_print(puzzle_t* p, FILE* fp)
{
  if (p == NULL || fp == NULL){
    return -1;
  }

  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      fprintf(fp, "%d ", p->values[i][j]);
    }
    fputc('\n', fp);
  }

  fprintf(fp, "\nPuzzle Score: %d\n", energy(p));
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





