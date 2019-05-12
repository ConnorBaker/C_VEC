//
// Created by Connor Baker on 2019-05-12.
//
// Includes all of the name-creation macros that are used to construct both
// the prototypes and definitions of C_VEC.

#ifndef C_VEC_NOMENCLATURE_H
#define C_VEC_NOMENCLATURE_H

#define VEC(T) VEC_##T

#define NEW_VEC(T) NEW_VEC_##T

#define DEL_VEC(T) DEL_VEC_##T

#define FOR_EACH(T) FOR_EACH_##T

#define FOR_EACH_PAR(T) FOR_EACH_PAR_##T

#define REPEAT(T) REPEAT_##T

#define ITERATE(T) ITERATE_##T

#define FOLDL(T) FOLDL_##T

#define FOLDR(T) FOLDR_##T

#define CONCAT(T) CONCAT_##T

#define PRINT(T) PRINT_##T

#define HEAD(T) HEAD_##T

#define LAST(T) LAST_##T

#define MIN(T) MIN_##T

#endif //C_VEC_NOMENCLATURE_H
