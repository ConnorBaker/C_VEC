#include <stdio.h>

#include "proj_functions.h"

void mult2(int *value, int *accumulator) {
  *accumulator = *accumulator * 2 + *value;
}

int main() {
  VEC(int) *v = NEW_VEC(int)(10);

  // Create the vector 1010110101
  v->dat[0] = 1;
  v->dat[1] = 0;
  v->dat[2] = 1;
  v->dat[3] = 0;
  v->dat[4] = 1;
  v->dat[5] = 1;
  v->dat[6] = 0;
  v->dat[7] = 1;
  v->dat[8] = 0;
  v->dat[9] = 1;

  printf("The vector 1010110101:\n");
  PRINT(int)(v);

  printf("Let's convert it to binary!\n");

  int result = FOLDL(int)(v, mult2, 0);
  printf("Result is %d.\n", result);

  DEL_VEC(int)(v);

  return 0;
}