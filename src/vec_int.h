//
// Created by Connor Baker on 2019-04-17.
//
// This file allows you to easily start doing things with C_VEC if you happen
// to choose to use a pre-defined primitive type.

#ifndef VEC_INT_H
#define VEC_INT_H

#include "vec_prototypes.h"

DEFINE_VEC(int)

DEFINE_PROTO_NEW_VEC(int)

DEFINE_PROTO_DEL_VEC(int)

DEFINE_PROTO_REPEAT(int)

DEFINE_PROTO_FOLDL(int)

DEFINE_PROTO_FOLDR(int)

DEFINE_PROTO_ITERATE(int)

DEFINE_PROTO_CONCAT(int)

DEFINE_PROTO_PRINT(int)

DEFINE_PROTO_HEAD(int)

DEFINE_PROTO_LAST(int)

DEFINE_PROTO_MIN(int)

#endif //VEC_INT_H
