//
// Created by Connor Baker on 2019-04-08.
//

#include "vec.h"

typedef unsigned int T0;

DEFINE_VEC(T0)

DEFINE_PROTO_NEW_VEC(T0)
DEFINE_PROTO_DEL_VEC(T0)
DEFINE_PROTO_REPEAT(T0)
DEFINE_PROTO_FOLDL(T0)

DEFINE_NEW_VEC(T0)
DEFINE_DEL_VEC(T0)
DEFINE_REPEAT(T0)
DEFINE_FOLDL(T0)

void and(T0 *n, T0 *acc) {
    *acc &= *n;
}

void or(T0 *n, T0 *acc) {
    *acc |= *n;
}

int main() {
    const int len = 0xF;

    VEC(T0) *v0 = REPEAT(T0)(0, len);
    VEC(T0) *v1 = REPEAT(T0)(1, len);

    printf("All 0's and'd with 1: %d\n", FOLDL(T0)(v0, and, 1));
    printf("All 1's and'd with 1: %d\n", FOLDL(T0)(v1, and, 1));
    printf("All 0's and'd with 0: %d\n", FOLDL(T0)(v0, and, 0));
    printf("All 1's and'd with 0: %d\n", FOLDL(T0)(v1, and, 0));
    printf("All 0's or'd with 1: %d\n", FOLDL(T0)(v0, or, 1));
    printf("All 1's or'd with 1: %d\n", FOLDL(T0)(v1, or, 1));
    printf("All 0's or'd with 0: %d\n", FOLDL(T0)(v0, or, 0));
    printf("All 1's or'd with 0: %d\n", FOLDL(T0)(v1, or, 0));

    DEL_VEC(v0);
    DEL_VEC(v1);
}
