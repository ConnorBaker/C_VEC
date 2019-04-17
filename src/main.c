//
// Created by Connor Baker on 2019-04-08.
//

#include "vec.h"
#include <omp.h> // For printing the OMP version TODO: ifdef this
#include <stdio.h>
#include <stdlib.h>

typedef int T0;

DEFINE_VEC(T0)

DEFINE_PROTO_NEW_VEC(T0)
DEFINE_PROTO_DEL_VEC(T0)
DEFINE_PROTO_REPEAT(T0)
DEFINE_PROTO_FOLDL(T0)
DEFINE_PROTO_FOLDR(T0)
DEFINE_PROTO_ITERATE(T0)
DEFINE_PROTO_CONCAT(T0)
DEFINE_PROTO_PRINT(T0)

DEFINE_NEW_VEC(T0)
DEFINE_DEL_VEC(T0)
DEFINE_REPEAT(T0)
DEFINE_FOLDL(T0)
DEFINE_FOLDR(T0)
DEFINE_ITERATE(T0)
DEFINE_CONCAT(T0)
DEFINE_PRINT(T0)

void and (T0 * n, T0 *acc) { *acc &= *n; }

void or (T0 * n, T0 *acc) { *acc |= *n; }

void and_or_example() {
  const int len = 0xF;

  VEC(T0) *v0 = REPEAT(T0)(0, len);
  printf("A vector of all zeros:\n");
  PRINT(T0)(v0);
  VEC(T0) *v1 = REPEAT(T0)(1, len);
  printf("A vector of all ones:\n");
  PRINT(T0)(v1);

  printf("All 0's and'd with a 1: %d\n", FOLDL(T0)(v0, and, 1));
  printf("All 1's and'd with a 1: %d\n", FOLDL(T0)(v1, and, 1));
  printf("All 0's and'd with a 0: %d\n", FOLDL(T0)(v0, and, 0));
  printf("All 1's and'd with a 0: %d\n", FOLDL(T0)(v1, and, 0));
  printf("All 0's or'd with a 1: %d\n", FOLDL(T0)(v0, or, 1));
  printf("All 1's or'd with a 1: %d\n", FOLDL(T0)(v1, or, 1));
  printf("All 0's or'd with a 0: %d\n", FOLDL(T0)(v0, or, 0));
  printf("All 1's or'd with a 0: %d\n", FOLDL(T0)(v1, or, 0));

  printf("\n");

  DEL_VEC(T0)(v0);
  DEL_VEC(T0)(v1);
}

void double_me(T0 *n) { (*n) *= 2; }

void alt_sum_diff(T0 *n, T0 *acc) {
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

  VEC(T0) *v = REPEAT(T0)(1, len);

  ITERATE(T0)(v, double_me);

  printf("Positive powers of two:\n");
  PRINT(T0)(v);

  printf("Alternating sum/difference folding left: %d\n",
         FOLDL(T0)(v, alt_sum_diff, 0));
  printf("Alternating sum/difference folding right: %d\n",
         FOLDR(T0)(v, alt_sum_diff, 0));

  printf("\n");

  DEL_VEC(T0)(v);
}

void concat_example() {
  VEC(T0) *a = REPEAT(T0)(1, 1);
  VEC(T0) *b = REPEAT(T0)(2, 2);
  VEC(T0) *c = REPEAT(T0)(3, 3);

  printf("vec a:\n");
  PRINT(T0)(a);

  printf("vec b:\n");
  PRINT(T0)(b);

  printf("vec c:\n");
  PRINT(T0)(c);

  VEC(T0) *d = CONCAT(T0)(a, b);

  printf("vec d:\n");
  PRINT(T0)(d);

  VEC(T0) *e = CONCAT(T0)(d, c);

  printf("vec e:\n");
  PRINT(T0)(e);

  DEL_VEC(T0)(a);
  DEL_VEC(T0)(b);
  DEL_VEC(T0)(c);
  DEL_VEC(T0)(d);
  DEL_VEC(T0)(e);

  printf("\n");
}

int main() {
  printf("Your OpenMP version is from %d (YYYYMM)\n", _OPENMP);

  and_or_example();

  alt_sum_diff_example();

  concat_example();

  return 0;
}
