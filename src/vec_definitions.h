//
// Created by Connor Baker on 2019-04-08.
//
// Includes all of the definitions of the functions supported by C_VEC.
// Generally, if you are working on a project, you'd include this header file
// and use the macros below to generate the definitions of all the functions
// that you'd want to work with (which happens at compile time, since these are
// all macros).
// For an example, see vec_int.c

#ifndef C_VEC_DEFINITIONS_H
#define C_VEC_DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For memcpy



#include "vec_nomenclature.h"



/**
 * DEFINES THE VECTOR STRUCTURE AND CREATION/DELETION
 */
void _Noreturn vec_creation_error(const char *error) {
  fprintf(stderr, "%s\n", error);
  exit(1);
}

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

#define DEFINE_DEL_VEC(T)                                                      \
  void DEL_VEC(T)(VEC(T) * v) {                                                \
    free(v->dat);                                                              \
    free(v);                                                                   \
  }

/**
 * DEFINES THE FOR_EACH FUNCTION
 */
#define DEFINE_FOR_EACH(T)                                                     \
  void FOR_EACH(T)(VEC(T) * v, void(f)(T *)) {                                 \
    for (int i = 0; i < v->len; i++) {                                         \
      f(v->dat + i);                                                           \
    }                                                                          \
  }

/**
 * DEFINES THE FOR_EACH_PAR FUNCTION, WHICH OPERATES IN PARALLEL
 */
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
    if (memcpy(v->dat + a_size, b->dat, sizeof(T) * b_size) == NULL) {         \
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

/**
 * DEFINES THE HEAD FUNCTION
 */
#define DEFINE_HEAD(T)                                                         \
  T HEAD(T)(VEC(T) * v) { return v->dat[0]; }

/**
 * DEFINES THE LAST FUNCTION
 */
#define DEFINE_LAST(T)                                                         \
  T LAST(T)(VEC(T) * v) { return v->dat[(v->len) - 1]; }

/**
 * DEFINES THE MIN FUNCTION
 * The function first takes a vector, and a comparison function
 * that takes two arguments of the generic type T and returns a
 * positive integer value if its first argument is "greater than"
 * its second argument.
 * The function returns the smallest element in the vector, according
 * to the comparison function.
 * This algorithm works by first assuming the vector's first argument
 * is its smallest and then goes from there.
 */
#define DEFINE_MIN(T)                                                          \
  T MIN(T)(VEC(T) * v, int(comp)(T, T)) {                                      \
    T min;                                                                     \
    min = v->dat[0];                                                           \
    for (int i = 1; i < (v->len); i++)                                         \
      if (comp(min, v->dat[i]) > 0)                                            \
        min = v->dat[i];                                                       \
    return min;                                                                \
  }

#endif // C_VEC_DEFINITIONS_H
