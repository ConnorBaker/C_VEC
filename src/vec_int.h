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

#ifndef VEC_INT_H
#define VEC_INT_H

#include "vec_prototypes.h"

//#include "vec_defs.h"

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
