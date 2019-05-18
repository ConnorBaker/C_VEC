# Supported Operations

+ `VEC(T)* NEW_VEC(T)(int length)`
  + Returns a pointer to a `VEC` structure, where `v->dat` is a reference to a `calloc`'d array of type `T` and length `length`. Since I use `calloc`, the elements of `v->dat` are initially zero.
+ `void DEL_VEC(T)(VEC(T) *v)`
  + Releases the memory held by `v`.
+ `void FOR_EACH(T)(VEC(T) *v, void (f)(T *))`
  + Applies a function `f` to each element of type `T` of `v`'s `v->dat`.
+ `void FOR_EACH_PAR(T)(VEC(T) *v, void (f)(T *))`
  + The same as the above, but uses the `_Pragma("omp parallel for default(none) shared(v, f)")` macro to allow the process to be done in parallel.
+ `VEC(T)* REPEAT(T)(T t, int length)`
  + Identical behavior to `NEW_VEC`, but each element of `v->dat` is initialized to `t`.
+ `void ITERATE(T)(VEC(T) *v, void (f)(T *))`
  + The function `f` is applied to each element of `v->dat` a number of times equal to the element's index. As an example:
  
  ~~~c
  void addOne(int *n) {
    (*n)++;
  }
  int main(void) {
    VEC(int) *v = NEW_VEC(int)(8);
    ITERATE(int)(v, addOne);
    // v->dat = [0, 1, 2, 3, 4, 5, 6, 7] 
  }
  ~~~

+ `T FOLDL(T)(VEC(T) *v, void (f)(T *, T *), T accumulator)`
  + Applies some binary operation `f` to each element of `v`, starting at the high index, and storing the return value in `accumulator`. Let us denote each element `v->dat[n]` with `v_n` where `n` is the index, and write the accumulator as `acc`. Then in general,

  ~~~c
  FOLDL(T)(v, f, acc) = f(v_0, f(v_1, ... f(v_n, acc) ... ))
  ~~~

+ `T FOLDR(T)(VEC(T) *v, void (f)(T *, T *), T accumulator)`
  + Applies some binary operation `f` to each element of `v`, starting at the low index, and storing the return value in `accumulator`. Let us denote each element `v->dat[n]` with `v_n` where `n` is the index, and write the accumulator as `acc`. Then in general,

  ~~~c
  FOLDR(T)(v, f, acc) = f(v_n, f(v_n-1, ... f(v_0, acc) ... ))
  ~~~

+ `VEC(T) * CONCAT(T)(VEC(T) * a, VEC(T) * b)`
  + Concatenates two vectors, returning a new vector which is the result of appending `b` to `a`.

+ `void PRINT(T)(VEC(T) *v)`
  + Prints out the contents of `v` delimited by spaces, assuming that it is of one of the following types:

    ~~~c
    #define FORMAT_STR(T) _Generic(T,   \
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
        default *: "%p")
    ~~~

+ `T HEAD(T)(VEC(T) *v)`
  + Returns the first element of the vector.

+ `T LAST(T)(VEC(T) *v)`
  + Returns the last element of the vector.

+ `T MIN(T)(VEC(T) *v, int (comp)(T, T))`
  + Returns the smallest element in the vector. The function first takes a vector `v`, and a comparison function `int comp(T, T)` that returns a positive integer value if its first argument is "greater than" its second argument.