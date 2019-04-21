# C_VEC

Fancy "Generic" C arrays with some nice built-in operations.

The goal is to eventually get parity, through macros, with most of the functions that Haskell provides for operations on lists.

## General notes on C_VEC

+ These are not performance-oriented implementations -- this is an exercise in seeing what I can do with macros
+ I haven't created unit tests and debugging a macro is a notoriously difficult task -- there *are almost certainly* bugs
+ Though the functions make look cool, and I've certainly borrowed inspiration from Haskell in terms of naming, make no mistake: these are C macros. We don't have any of the niceties that higher-level languages provide
. There's no possibility of composition as this is currently written (e.g. `VEC(VEC(int))` does NOT do what you think it does... unless your guess was "it doesn't compile because `VEC_VEC_int` isn't defined", in which case you should help me implement it).

### More pressing matters

Due to the way that we emulate "generic" functions (sting concatenation with token pasting using macros) there's a lot of conflict with function names. One way around this is to create a header which includes `vec.h` and to use every definition macro with all the types you could need. It's ugly, but at I'm at a loss for a better solution.

## Currently supported operations

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

## Arriving Soon*

The following is a wish-list of sorts of Haskell functions on lists that I'd like to implement:

+ `++` (list concatenation)
  + Done! See `CONCAT`.
+ `:` (cons)
+ `head` (returns the first element of a list)
  + Done!
+ `last` (returns the last element of a list)
+ `init` (returns all but the last element of a list)
+ `tail` (returns all but the first element of a list)
+ `reverse` (reverses the list, possibly in place)
+ `drop` (returns a new list with some number of elements from the front gone)
  + `dropWhile` (returns a new list with elements dropped from the front while a condition holds)
+ `take` (returns a new list made of some number of elements from the front)
  + `takeWhile` (returns a new list made of elements front while a condition holds)
+ `min` (returns the minimum of the list)
+ `max` (returns the maximum of the list)
+ `sum` (returns the sum of the list)
+ `prod` (returns the product of the list)
+ `elem` (returns the index of the element, or -1 if not found -- this is different when compared to Haskell, which returns a boolean value)
+ `cycle` (creates a list of some length by repeatedly cycling through a given list)
+ `FILTER` (returns a list of elements that satisfy some filter)
+ `RANGE` (perhaps using Haskell's `..` as syntactic sugar?)
+ `zip` (zip two lists together -- we'd need tuples for this though, and OH BOY that can get complicated pretty quickly)
+ `sort` (sort the list -- possibly in place?)

However, anything that involves lists of lists, or lists of tuples is out of reach at the moment. There's only so much that the preprocessor can do... that I know how to make it do.

## Future directions

+ Open up the `ITERATE` function so that it can have state. See the TODO in `main.c` for more information.
