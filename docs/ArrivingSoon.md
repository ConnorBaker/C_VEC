# Arriving Soon

The following is a wish-list of sorts of Haskell functions on lists that I'd like to implement:

+ `:` (cons)
+ `last` (returns the last element of a list)
+ `init` (returns all but the last element of a list)
+ `tail` (returns all but the first element of a list)
+ `reverse` (reverses the list, possibly in place)
+ `drop` (returns a new list with some number of elements from the front gone)
  + `dropWhile` (returns a new list with elements dropped from the front while a condition holds)
+ `take` (returns a new list made of some number of elements from the front)
  + `takeWhile` (returns a new list made of elements front while a condition holds)
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