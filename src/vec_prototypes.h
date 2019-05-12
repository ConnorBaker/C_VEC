//
// Created by Connor Baker on 2019-05-12.
//

#ifndef C_VEC_PROTOTYPES_H
#define C_VEC_PROTOTYPES_H

#define VEC(T) VEC_##T

#define DEFINE_VEC(T)                                                          \
  typedef struct vec_##T {                                                     \
    T *dat;                                                                    \
    int len;                                                                   \
  } VEC(T);

void vec_creation_error(const char *);

#define NEW_VEC(T) NEW_VEC_##T
#define DEFINE_PROTO_NEW_VEC(T) VEC(T) * NEW_VEC(T)(int);

#define DEL_VEC(T) DEL_VEC_##T
#define DEFINE_PROTO_DEL_VEC(T) void DEL_VEC(T)(VEC(T) *);

#define FOR_EACH(T) FOR_EACH_##T
#define DEFINE_PROTO_FOR_EACH(T) void FOR_EACH(T)(VEC(T) *, void(f)(T *));

#define FOR_EACH_PAR(T) FOR_EACH_PAR_##T
#define DEFINE_PROTO_FOR_EACH_PAR(T)                                           \
  void FOR_EACH_PAR(T)(VEC(T) *, void(f)(T *));

#define REPEAT(T) REPEAT_##T
#define DEFINE_PROTO_REPEAT(T) VEC(T) * REPEAT(T)(T, int);

#define ITERATE(T) ITERATE_##T
#define DEFINE_PROTO_ITERATE(T) void ITERATE(T)(VEC(T) *, void(f)(T *));

#define FOLDL(T) FOLDL_##T
#define DEFINE_PROTO_FOLDL(T) T FOLDL(T)(VEC(T) *, void(f)(T *, T *), T);

#define FOLDR(T) FOLDR_##T
#define DEFINE_PROTO_FOLDR(T) T FOLDR(T)(VEC(T) *, void(f)(T *, T *), T);

#define CONCAT(T) CONCAT_##T
#define DEFINE_PROTO_CONCAT(T) VEC(T) * CONCAT(T)(VEC(T) *, VEC(T) *);

#define PRINT(T) PRINT_##T
#define DEFINE_PROTO_PRINT(T) void PRINT(T)(VEC(T) *);

#define HEAD(T) HEAD_##T
#define DEFINE_PROTO_HEAD(T) T HEAD(T)(VEC(T) *);

#define LAST(T) LAST_##T
#define DEFINE_PROTO_LAST(T) T LAST(T)(VEC(T) *);

#define MIN(T) MIN_##T
#define DEFINE_PROTO_MIN(T) T MIN(T)(VEC(T) *, int (comp)(T, T));

#endif //C_VEC_PROTOTYPES_H
