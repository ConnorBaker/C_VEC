//
// Created by Connor Baker on 2019-04-17.
//

#include "proj_defs.h"
#include <stdio.h>
#include <stdlib.h>

void double_me(int *n) { (*n) *= 2; }

void alt_sum_diff(int *n, int *acc) {
  // TODO: This is a great example of an area for improvement. How can reset
  //       such a variable when we're done invoking the function without
  //       adding in an additional parameter? If we invoke this function an
  //       odd number of times, the value is not reset to what it was
  //       previously.
  static unsigned int i = 1;
  *acc += ((i = (i + 1) & 1U) ? (-1 * (*n)) : (*n));
}

void alt_sum_diff_example() {
  const int len = 0xF;

  VEC(int) *v = REPEAT(int)(1, len);

  ITERATE(int)(v, double_me);

  printf("Positive powers of two:\n");
  PRINT(int)(v);

  printf("Alternating sum/difference folding left: %d\n",
         FOLDL(int)(v, alt_sum_diff, 0));
  printf("Alternating sum/difference folding right: %d\n",
         FOLDR(int)(v, alt_sum_diff, 0));

  printf("\n");

  DEL_VEC(int)(v);
}

int main() {
  alt_sum_diff_example();

  return 0;
}