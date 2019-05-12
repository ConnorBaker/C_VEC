//
// Created by Connor Baker on 2019-05-12.
//

#include "gtest/gtest.h"
#include <iostream>

extern "C" {
#include "../src/vec_int.h"
}

TEST(Concat, HandlesSimpleConcat) {
  // [1]
  VEC(int) *a = REPEAT(int)(1, 1);
  // [2, 2]
  VEC(int) *b = REPEAT(int)(2, 2);
  // [3, 3, 3]
  VEC(int) *c = REPEAT(int)(3, 3);

  // [1, 2, 2]
  VEC(int) *d = CONCAT(int)(a, b);
  int operation1[] = {1, 2, 2};

  for (int i = 0; i < d->len; i++) {
    EXPECT_EQ(d->dat[i], operation1[i]);
  }

  // [1, 2, 2, 3, 3, 3]
  VEC(int) *e = CONCAT(int)(d, c);
  int operation2[] = {1, 2, 2, 3, 3, 3};

  for (int i = 0; i < e->len; i++) {
    EXPECT_EQ(e->dat[i], operation2[i]);
  }

  DEL_VEC(int)(a);
  DEL_VEC(int)(b);
  DEL_VEC(int)(c);
  DEL_VEC(int)(d);
  DEL_VEC(int)(e);
}