//
// Created by Connor Baker on 2019-05-12.
//

#include "gtest/gtest.h"
#include <iostream>

extern "C" {
#include "../src/vec_int.h"
}

extern "C" {
void andFtn(int *, int *);
void orFtn(int *, int *);
}

void andFtn(int *n, int *acc) { *acc &= *n; }

void orFtn(int *n, int *acc) { *acc |= *n; }

TEST(foldl, HandlesAnd) {
  const int len = 0xF;

  //  A vector of all zeros
  VEC(int) *v0 = REPEAT(int)(0, len);
  for (int i = 0; i < v0->len; i++) {
    EXPECT_EQ(v0->dat[i], 0);
  }

  //  A vector of all ones
  VEC(int) *v1 = REPEAT(int)(1, len);
  for (int i = 0; i < v0->len; i++) {
    EXPECT_EQ(v1->dat[i], 1);
  }

  //  All 0's and'd with a 1 = 0
  ASSERT_EQ(FOLDL(int)(v0, andFtn, 1), 0);

  //  All 1's and'd with a 1 = 1
  ASSERT_EQ(FOLDL(int)(v1, andFtn, 1), 1);

  //  All 0's and'd with a 0 = 0
  ASSERT_EQ(FOLDL(int)(v0, andFtn, 0), 0);

  //  All 1's and'd with a 0 = 0
  ASSERT_EQ(FOLDL(int)(v1, andFtn, 0), 0);

  DEL_VEC(int)(v0);
  DEL_VEC(int)(v1);
}

TEST(foldl, HandlesOr) {
    const int len = 0xF;

    //  A vector of all zeros
    VEC(int) *v0 = REPEAT(int)(0, len);
    for (int i = 0; i < v0->len; i++) {
        EXPECT_EQ(v0->dat[i], 0);
    }

    //  A vector of all ones
    VEC(int) *v1 = REPEAT(int)(1, len);
    for (int i = 0; i < v0->len; i++) {
        EXPECT_EQ(v1->dat[i], 1);
    }

    //  All 0's or'd with a 1 = 1
    ASSERT_EQ(FOLDL(int)(v0, orFtn, 1), 1);

    //  All 1's or'd with a 1
    ASSERT_EQ(FOLDL(int)(v1, orFtn, 1), 1);

    //  All 0's or'd with a 0
    ASSERT_EQ(FOLDL(int)(v0, orFtn, 0), 0);

    //  All 1's or'd with a 0
    ASSERT_EQ(FOLDL(int)(v1, orFtn, 0), 1);

    DEL_VEC(int)(v0);
    DEL_VEC(int)(v1);
}
