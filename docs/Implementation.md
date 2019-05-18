# Implementation Details

`C_VEC` is essentially a header-only library. There are three headers which compose the library

+ `vec_nomenclature.h`
+ `vec_prototypes.h`
+ `vec_definitions.h`

## Nomenclature

The file `vec_nomenclature.h` defines the names of the type (currently just one) and functions supported by the library. As such, it is included by both `vec_prototypes.h` and `vec_definitions.h`. Consider the first few lines (excluding `ifndefs` and `include`s):

~~~c
#define VEC(T) VEC_##T

#define NEW_VEC(T) NEW_VEC_##T

#define DEL_VEC(T) DEL_VEC_##T

#define FOR_EACH(T) FOR_EACH_##T
~~~

Here we can see the real magic: concatenation. Using `##` in a macro allows for the pasting of tokens used in the macro.

As an example, if one were to use the macro, replacing `T` with a different type, like `int`, we would see every occurrence of `VEC(T)` be replaced by `VEC_int`, and every use of `NEW_VEC(T)` replaced by `NEW_VEC_int`, and so on. This effectively allows us to generate the names of new types and functions at compile-time.

## Prototypes

The file `vec_prototypes.h` provides macros for all of the functions supported by `C_VEC`, as well as the definition of the `VEC` `struct`. Consider the first few lines (excluding `ifndef`s and `include`s):

~~~c
#define DEFINE_VEC(T)                                                          \
  typedef struct vec_##T {                                                     \
    T *dat;                                                                    \
    int len;                                                                   \
  } VEC(T);

void vec_creation_error(const char *);

#define DEFINE_PROTO_NEW_VEC(T) VEC(T) * NEW_VEC(T)(int);

#define DEFINE_PROTO_DEL_VEC(T) void DEL_VEC(T)(VEC(T) *);
~~~

We have a macro which defines what is essentially an array which knows its own size, a function which we use to exit the program if we are unable to allocate memory for any reason, and two macros which generate the prototypes for functions which allow for the creation and deletion of vectors.

## Definitions

The file `vec_definitions.h` provides macros for all of the functions supported by `C_VEC`, as well as the definition of the `VEC` `struct`. Consider the first few lines (excluding `ifndef`s and `include`s):

~~~c
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
~~~

These lines give us the definition for the `vec_creation_error` function whose prototype we looked at earlier, as well as the definitions for `NEW_VEC(T)` and `DEL_VEC(T)`.