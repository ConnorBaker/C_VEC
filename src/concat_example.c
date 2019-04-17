//
// Created by Connor Baker on 2019-04-17.
//

#include "proj_defs.h"
#include <stdio.h>
#include <stdlib.h>

void concat_example() {
  VEC(int) *a = REPEAT(int)(1, 1);
  VEC(int) *b = REPEAT(int)(2, 2);
  VEC(int) *c = REPEAT(int)(3, 3);

  printf("vec a:\n");
  PRINT(int)(a);

  printf("vec b:\n");
  PRINT(int)(b);

  printf("vec c:\n");
  PRINT(int)(c);

  VEC(int) *d = CONCAT(int)(a, b);

  printf("vec d:\n");
  PRINT(int)(d);

  VEC(int) *e = CONCAT(int)(d, c);

  printf("vec e:\n");
  PRINT(int)(e);

  DEL_VEC(int)(a);
  DEL_VEC(int)(b);
  DEL_VEC(int)(c);
  DEL_VEC(int)(d);
  DEL_VEC(int)(e);

  printf("\n");
}

int main() {
  concat_example();

  return 0;
}
