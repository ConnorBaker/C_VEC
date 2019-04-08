# C_Vec
Fancy "Generic" C arrays with some nice built-in operations

## General notes on C_Vec

+ These are not super performant -- this is an exercise in seeing what I can do with macros
+ I haven't created unit tests and debugging a macro is a notoriously difficult task -- there *are almost certainly* bugs
+ Though the functions make look cool, and I've certainly borrowed inspiration from Haskell in terms of naming, make no mistake: these are C macros. We don't have any of the niceties that higher-level languages provide. There's no possibility of composition as this is currently written (e.g. `VEC(VEC(int))` does NOT do what you think it does... unless your guess was "it doesn't compile because VEC_VEC_int isn't defined", in which case you should help me implement it). 

## Currently supported operations

+ `VEC(T)* NEW_VEC(T)(int length)`
  + Returns a pointer to a `VEC` struct, where `v->dat` is a reference to a `calloc`'d array of type `T` and length `length`. Since I use `calloc`, the elements of `v->dat` are initially zero.
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
  ~~~
  FOLDL(T)(v, f, acc) = f(v_0, f(v_1, ... f(v_n, acc) ... ))
  ~~~
+ `T FOLDR(T)(VEC(T) *v, void (f)(T *, T *), T accumulator)`
  + Applies some binary operation `f` to each element of `v`, starting at the low index, and storing the return value in `accumulator`. Let us denote each element `v->dat[n]` with `v_n` where `n` is the index, and write the accumulator as `acc`. Then in general,
  ~~~
  FOLDR(T)(v, f, acc) = f(v_n, f(v_n-1, ... f(v_0, acc) ... ))
  ~~~
+ `void PRINT(T)(VEC(T) *v)`
  + Prints out the contents of `v` delimited by spaces, assuming that it is of one of the following types:
    ~~~
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