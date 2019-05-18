//
// Created by Connor Baker on 2019-05-12.
//
// Includes all of the prototypes of the functions supported by C_VEC.
// Generally, if you are working on a project, you'd include this header file
// and use the macros below to generate prototypes of all the functions that
// you'd want to work with (which happens at compile time, since these are
// all macros).
// For an example, see vec_int.h

#ifndef C_VEC_PROTOTYPES_H
#define C_VEC_PROTOTYPES_H



#include "vec_nomenclature.h"



#define DEFINE_VEC(T)                                                          \
  typedef struct vec_##T {                                                     \
    T *dat;                                                                    \
    int len;                                                                   \
  } VEC(T);

void vec_creation_error(const char *);

#define DEFINE_PROTO_NEW_VEC(T) VEC(T) * NEW_VEC(T)(int);

#define DEFINE_PROTO_DEL_VEC(T) void DEL_VEC(T)(VEC(T) *);

#define DEFINE_PROTO_FOR_EACH(T) void FOR_EACH(T)(VEC(T) *, void(f)(T *));

#define DEFINE_PROTO_REPEAT(T) VEC(T) * REPEAT(T)(T, int);

#define DEFINE_PROTO_ITERATE(T) void ITERATE(T)(VEC(T) *, void(f)(T *));

#define DEFINE_PROTO_FOLDL(T) T FOLDL(T)(VEC(T) *, void(f)(T *, T *), T);

#define DEFINE_PROTO_FOLDR(T) T FOLDR(T)(VEC(T) *, void(f)(T *, T *), T);

#define DEFINE_PROTO_CONCAT(T) VEC(T) * CONCAT(T)(VEC(T) *, VEC(T) *);

#define DEFINE_PROTO_PRINT(T) void PRINT(T)(VEC(T) *);

#define DEFINE_PROTO_HEAD(T) T HEAD(T)(VEC(T) *);

#define DEFINE_PROTO_LAST(T) T LAST(T)(VEC(T) *);

#define DEFINE_PROTO_MIN(T) T MIN(T)(VEC(T) *, int (comp)(T, T));

#endif //C_VEC_PROTOTYPES_H
