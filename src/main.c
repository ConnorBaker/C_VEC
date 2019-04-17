//
// Created by Connor Baker on 2019-04-08.
//

#include <omp.h> // For printing the OMP version TODO: ifdef this
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Your OpenMP version is from %d (YYYYMM)\n", _OPENMP);

  return 0;
}
