//
// Created by Connor Baker on 2019-04-08.
//

#ifndef C_VEC_H
#define C_VEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For memcpy

/**
 * DEFINES THE VECTOR STRUCTURE AND CREATION/DELETION
 */
#define VEC(T) VEC_##T

#define DEFINE_VEC(T)                                                          \
  typedef struct vec_##T {                                                     \
    T *dat;                                                                    \
    int len;                                                                   \
  } VEC(T);

void vec_creation_error(const char *);
void _Noreturn vec_creation_error(const char *error) {
  fprintf(stderr, "%s\n", error);
  exit(1);
}

#define NEW_VEC(T) NEW_VEC_##T

#define DEFINE_PROTO_NEW_VEC(T) VEC(T) * NEW_VEC(T)(int);

#define DEFINE_NEW_VEC(T)                                                      \
  VEC(T) * NEW_VEC(T)(int length) {                                            \
    if (length <= 0) {                                                         \
      vec_creation_error("Unable to create non-positive length NEW_VEC");      \
    }                                                                          \
    VEC(T) *v = (VEC(T) *)calloc(1, sizeof(VEC(T)));                           \
    if (v == NULL) {                                                           \
      vec_creation_error("Unable to allocate memory for NEW_VEC");             \
    }                                                                          \
    v->dat = (T *)calloc(length, sizeof(T));                                   \
    if (v->dat == NULL) {                                                      \
      vec_creation_error("Unable to allocate memory for NEW_VEC->dat");        \
    }                                                                          \
    v->len = length;                                                           \
    return v;                                                                  \
  }

#define DEL_VEC(v) DEL_VEC_##T

#define DEFINE_PROTO_DEL_VEC(T) void DEL_VEC(T)(VEC(T) *);

#define DEFINE_DEL_VEC(T)                                                      \
  void DEL_VEC(T)(VEC(T) * v) {                                                \
    free(v->dat);                                                              \
    free(v);                                                                   \
  }

/**
 * DEFINES THE FOR_EACH FUNCTION
 */
#define FOR_EACH(T) FOR_EACH_##T

#define DEFINE_PROTO_FOR_EACH(T) void FOR_EACH(T)(VEC(T) *, void(f)(T *));

#define DEFINE_FOR_EACH(T)                                                     \
  void FOR_EACH(T)(VEC(T) * v, void(f)(T *)) {                                 \
    for (int i = 0; i < v->len; i++) {                                         \
      f(v->dat + i);                                                           \
    }                                                                          \
  }

/**
 * DEFINES THE FOR_EACH_PAR FUNCTION, WHICH OPERATES IN PARALLEL
 */
#define FOR_EACH_PAR(T) FOR_EACH_PAR_##T

#define DEFINE_PROTO_FOR_EACH_PAR(T)                                           \
  void FOR_EACH_PAR(T)(VEC(T) *, void(f)(T *));

#define DEFINE_FOR_EACH_PAR(T)                                                 \
  void FOR_EACH_PAR(T)(VEC(T) * v, void(f)(T *)) {                             \
    _Pragma("omp parallel for default(none) shared(v, f)") for (int i = 0;     \
                                                                i < v->len;    \
                                                                i++) {         \
      f(v->dat + i);                                                           \
    }                                                                          \
  }

/**
 * DEFINES THE REPEAT FUNCTION
 */
#define REPEAT(T) REPEAT_##T

#define DEFINE_PROTO_REPEAT(T) VEC(T) * REPEAT(T)(T, int);

#define DEFINE_REPEAT(T)                                                       \
  VEC(T) * REPEAT(T)(T t, int length) {                                        \
    VEC(T) *v = NEW_VEC(T)(length);                                            \
    for (int i = 0; i < v->len; i++) {                                         \
      (v->dat)[i] = t;                                                         \
    }                                                                          \
    return v;                                                                  \
  }

/**
 * DEFINES THE ITERATE FUNCTION
 */
#define ITERATE(T) ITERATE_##T

#define DEFINE_PROTO_ITERATE(T) void ITERATE(T)(VEC(T) *, void(f)(T *));

#define DEFINE_ITERATE(T)                                                      \
  void ITERATE(T)(VEC(T) * v, void(f)(T *)) {                                  \
    for (int i = 0; i < v->len; i++) {                                         \
      for (int j = 0; j < i; j++) {                                            \
        f(v->dat + i);                                                         \
      }                                                                        \
    }                                                                          \
  }

/**
 * DEFINES THE FOLDL FUNCTION.
 * The function takes the address of a vector, a function, and an
 * accumulator.
 * The vector holds the data that we'll fold over.
 * The function void (f)(T *, T *) takes as arguments an element of
 * the vector and the address of the accumulator.
 * The accumulator passed in contains the initial value.
 * FOLDL(T)(v, f, acc) = f(v_0, f(v_1, ... f(v_n, acc) ... ))
 */
#define FOLDL(T) FOLDL_##T

#define DEFINE_PROTO_FOLDL(T) T FOLDL(T)(VEC(T) *, void(f)(T *, T *), T);

#define DEFINE_FOLDL(T)                                                        \
  T FOLDL(T)(VEC(T) * v, void(f)(T *, T *), T accumulator) {                   \
    for (int i = v->len - 1; i >= 0; i--) {                                    \
      f(v->dat + i, &accumulator);                                             \
    }                                                                          \
    return accumulator;                                                        \
  }

/**
 * DEFINES THE FOLDR FUNCTION.
 * The function takes the address of a vector, a function, and an
 * accumulator.
 * The vector holds the data that we'll fold over.
 * The function void (f)(T *, T *) takes as arguments an element of
 * the vector and the address of the accumulator.
 * The accumulator passed in contains the initial value.
 * FOLDR(T)(v, f, acc) = f(v_n, f(v_n-1, ... f(v_0, acc) ... ))
 */
#define FOLDR(T) FOLDR_##T

#define DEFINE_PROTO_FOLDR(T) T FOLDR(T)(VEC(T) *, void(f)(T *, T *), T);

#define DEFINE_FOLDR(T)                                                        \
  T FOLDR(T)(VEC(T) * v, void(f)(T *, T *), T accumulator) {                   \
    for (int i = 0; i < v->len; i++) {                                         \
      f(v->dat + i, &accumulator);                                             \
    }                                                                          \
    return accumulator;                                                        \
  }

/**
 * DEFINES THE CONCAT FUNCTION
 */
#define CONCAT(T) CONCAT_##T

#define DEFINE_PROTO_CONCAT(T) VEC(T) * CONCAT(T)(VEC(T) *, VEC(T) *);

#define DEFINE_CONCAT(T)                                                       \
  VEC(T) * CONCAT(T)(VEC(T) * a, VEC(T) * b) {                                 \
    const int a_size = a->len;                                                 \
    const int b_size = b->len;                                                 \
    VEC(T) *v = NEW_VEC(T)(a_size + b_size);                                   \
    /* TODO: Opportunity to use omp_target_memcpy() here? */                   \
    if (memcpy(v->dat, a->dat, sizeof(T) * a_size) == NULL) {                  \
      vec_creation_error("Unable to copy memory contents from first VEC\n");   \
    }                                                                          \
    /* TODO: Opportunity to use omp_target_memcpy() here? */                   \
    if (memcpy(v->dat + a_size, b->dat, sizeof(T0) * b_size) == NULL) {        \
      vec_creation_error("Unable to copy memory contents from second VEC\n");  \
    }                                                                          \
    return v;                                                                  \
  }

/**
 * DEFINES THE PRINT FUNCTION
 */
#define FORMAT_STR(T)                                                          \
  _Generic(T,   \
    char: "%c",                     \
    signed char: "%hhd",            \
    unsigned char: "%hhu",          \
    signed short: "%hd",            \
    unsigned short: "%hu",          \
    signed int: "%d",               \
    unsigned int: "%u",             \
    long int: "%ld",                \
    unsigned long int: "%lu",       \
    long long int: "%lld",          \
    unsigned long long int: "%llu", \
    float: "%f",                    \
    double: "%f",                   \
    long double: "%Lf",             \
    char *: "%s",                   \
    void *: "%p",                   \
    default: "%p")

#define PRINT(T) PRINT_##T

#define DEFINE_PROTO_PRINT(T) void PRINT(T)(VEC(T) *);

#define DEFINE_PRINT(T)                                                        \
  void PRINT(T)(VEC(T) * v) {                                                  \
    const char *format_str = FORMAT_STR(v->dat[0]);                            \
    for (int i = 0; i < v->len - 1; i++) {                                     \
      printf(format_str, v->dat[i]);                                           \
      printf(" ");                                                             \
    }                                                                          \
    printf(format_str, v->dat[v->len - 1]);                                    \
    printf("\n");                                                              \
  }

#endif // C_VEC_H
