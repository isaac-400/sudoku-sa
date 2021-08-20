/* Unit Tests for puzzle.[ch]
 *
 * Isaac Feldman 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "puzzle.h"

static int unit_tested = 0;     // number of test cases run
static int unit_failed = 0;     // number of test cases failed

// Checks 'condition', increments unit_tested, prints FAIL or PASS
void unit_expect(bool condition, int linenum)
{
   unit_tested++;
     if (condition) {
        printf("PASS test %03d at line %d\n", unit_tested, linenum);
    } else {
        printf("FAIL test %03d at line %d\n", unit_tested, linenum);
            unit_failed++;
    }
}

// a macro for shorthand calls to expect()
#define EXPECT(cond) { unit_expect((cond), __LINE__); }


int main()
{
  puzzle_t* puzzle = puzzle_new(9);
  EXPECT(puzzle != NULL);
  puzzle_print(puzzle, stdout);
  puzzle_delete(puzzle);
  
  FILE* fp = fopen("test_puzzle01", "r");
  if (fp == NULL) {
    fprintf(stderr, "Missing or unreadable: test_puzzle");
    exit(-1);
  }
  puzzle_t* puzzle1 = puzzle_load(fp, 9);
  fclose(fp);
  EXPECT(puzzle1 != NULL);
  puzzle_print(puzzle1, stdout);
  puzzle_delete(puzzle1);


  if (unit_failed > 0) {
       printf("FAILED %d of %d tests\n", unit_failed, unit_tested);
       return unit_failed;
   } 
   else {
       printf("PASSED all of %d tests\n", unit_tested);
       return 0;
   }
}
