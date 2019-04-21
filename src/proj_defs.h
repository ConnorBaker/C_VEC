//
// Created by Connor Baker on 2019-04-17.
//
// This file allows you to change the type of C_VEC.
// If you find functions you do not need, this is also
// the place to remove those functions: simply comment
// the corresponding "DEFINE_PROTO_" and "DEFINE_" macro
// calls of the function you do not want and the compiler
// will not compile those functions, if you need that kind
// of thing.
//

#ifndef VEC_C_PROJ_DEFS_H
#define VEC_C_PROJ_DEFS_H

// Change this to desired type
#define TYPE int

#include "vec.h"

DEFINE_VEC(TYPE)

DEFINE_PROTO_NEW_VEC(TYPE)
DEFINE_PROTO_DEL_VEC(TYPE)
DEFINE_PROTO_REPEAT(TYPE)
DEFINE_PROTO_FOLDL(TYPE)
DEFINE_PROTO_FOLDR(TYPE)
DEFINE_PROTO_ITERATE(TYPE)
DEFINE_PROTO_CONCAT(TYPE)
DEFINE_PROTO_PRINT(TYPE)
DEFINE_PROTO_HEAD(TYPE)
DEFINE_PROTO_LAST(TYPE)
DEFINE_PROTO_MIN(TYPE)

DEFINE_NEW_VEC(TYPE)
DEFINE_DEL_VEC(TYPE)
DEFINE_REPEAT(TYPE)
DEFINE_FOLDL(TYPE)
DEFINE_FOLDR(TYPE)
DEFINE_ITERATE(TYPE)
DEFINE_CONCAT(TYPE)
DEFINE_PRINT(TYPE)
DEFINE_HEAD(TYPE)
DEFINE_LAST(TYPE)
DEFINE_MIN(TYPE)

#endif //VEC_C_PROJ_DEFS_H
