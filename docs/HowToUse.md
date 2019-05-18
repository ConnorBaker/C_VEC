# How to use `C_VEC`

In general, to use the library, one would create a header file in which they include `vec_prototypes.h` and use whichever macros they wish to define any function prototypes they may want (substituting `T` for whichever types they wish to operate on). To be able to use the functions they created prototypes for, they could create a `.c` file in which they include `vec_definitions.h`, using whichever all of the definition macros that correspond to the prototypes they defined earlier.

## An example

Let's assume that I wanted to perform operations on a vector of integers. To best do this, I would make a note of the operations that I want to be able to perform on this vector.