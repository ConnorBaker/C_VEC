# How to use `C_VEC`

In general, to use the library, one would create a header file in which they include `vec_prototypes.h` and use whichever macros they wish to define any function prototypes they may want (substituting `T` for whichever types they wish to operate on). To be able to use the functions they created prototypes for, they could create a `.c` file in which they include `vec_definitions.h`, using whichever all of the definition macros that correspond to the prototypes they defined earlier.

## An example

The sources of this example are all located in the examples folder at the root of the directory. This particular exercise is under the BinaryToDecimal folder.

Let's assume that I wanted to perform operations on a vector of integers. To best do this, I would make a note of the operations that I want to be able to perform on this vector.

Let's assume that we're given some binary number and we want to convert it to a decimal number. To do this, we'll use the following functions:

+ `NEW_VEC` to create our vector
+ `DEL_VEC` to free the memory associated with our vector
+ `FOLDL` to easily convert to decimal
+ `PRINT` to see the contents of our vector

Knowing the functions that we want to use, we can throw the corresponding `define`s into a header file (I'll call mine [proj_functions.h](../examples/BinaryToDecimal/proj_functions.h)):

~~~c
//
// Created by Connor Baker on 2019-05-18.
//

#ifndef BINARYTODECIMAL_PROJ_FUNCTIONS_H
#define BINARYTODECIMAL_PROJ_FUNCTIONS_H

#include "../../src/vec_prototypes.h"

DEFINE_VEC(int)

DEFINE_PROTO_NEW_VEC(int)

DEFINE_PROTO_DEL_VEC(int)

DEFINE_PROTO_FOLDL(int)

DEFINE_PROTO_PRINT(int)

#endif //BINARYTODECIMAL_PROJ_FUNCTIONS_H
~~~

and in a `.c` file we put the function definition macros (I named mine [proj_functions.c](../examples/BinaryToDecimal/proj_functions.c)):

~~~c
//
// Created by Connor Baker on 2019-05-18.
//

#include "proj_functions.h"

#include "../../src/vec_definitions.h"

DEFINE_NEW_VEC(int)

DEFINE_DEL_VEC(int)

DEFINE_FOLDL(int)

DEFINE_PRINT(int)
~~~

Then the rest of the program could look like the following (I named the driver [main.c](../examples/BinaryToDecimal/main.c) because... it has the `main` function in it, I guess):

~~~c
#include <stdio.h>

#include "proj_functions.h"

void mult2(int *value, int *accumulator) {
  *accumulator = *accumulator * 2 + *value;
}

int main() {
  VEC(int) *v = NEW_VEC(int)(10);

  // Create the vector 1010110101
  v->dat[0] = 1;
  v->dat[1] = 0;
  v->dat[2] = 1;
  v->dat[3] = 0;
  v->dat[4] = 1;
  v->dat[5] = 1;
  v->dat[6] = 0;
  v->dat[7] = 1;
  v->dat[8] = 0;
  v->dat[9] = 1;

  printf("The vector 1010110101:\n");
  PRINT(int)(v);

  printf("Let's convert it to binary!\n");

  int result = FOLDL(int)(v, mult2, 0);
  printf("Result is %d.\n", result);

  DEL_VEC(int)(v);

  return 0;
}
~~~

The function `mult2` doubles the size of the accumulated value, and then adds the contents of the current cell of the vector being processed to the result. Doing this process from the greatest index of the vector towards the lowest index allows us to convert from binary to decimal.

An example run would produce the output:

~~~console
The vector 1010110101:
1 0 1 0 1 1 0 1 0 1
Let's convert it to binary!
Result is 693.
~~~