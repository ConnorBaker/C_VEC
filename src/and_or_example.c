//
// Created by Connor Baker on 2019-04-17.
//

#include "proj_defs.h"
#include <stdio.h>
#include <stdlib.h>

void and (int *n, int *acc) { *acc &= *n; }

void or (int *n, int *acc) { *acc |= *n; }

void and_or_example() {
  const int len = 0xF;

  VEC(int) *v0 = REPEAT(int)(0, len);
  printf("A vector of all zeros:\n");
  PRINT(int)(v0);
  VEC(int) *v1 = REPEAT(int)(1, len);
  printf("A vector of all ones:\n");
  PRINT(int)(v1);

  printf("All 0's and'd with a 1: %d\n", FOLDL(int)(v0, and, 1));
  printf("All 1's and'd with a 1: %d\n", FOLDL(int)(v1, and, 1));
  printf("All 0's and'd with a 0: %d\n", FOLDL(int)(v0, and, 0));
  printf("All 1's and'd with a 0: %d\n", FOLDL(int)(v1, and, 0));
  printf("All 0's or'd with a 1: %d\n", FOLDL(int)(v0, or, 1));
  printf("All 1's or'd with a 1: %d\n", FOLDL(int)(v1, or, 1));
  printf("All 0's or'd with a 0: %d\n", FOLDL(int)(v0, or, 0));
  printf("All 1's or'd with a 0: %d\n", FOLDL(int)(v1, or, 0));

  printf("\n");

  DEL_VEC(int)(v0);
  DEL_VEC(int)(v1);
}

int main() {
  and_or_example();

  return 0;
}
