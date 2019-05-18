# `C_VEC`

Fancy "Generic" C arrays with some nice built-in operations.

The goal is to eventually get parity, through macros, with most of the functions that Haskell provides for operations on lists.

## Table of Contents

[Implementation Details](./Implementation.md)

[How to use `C_VEC`](./HowToUse.md)

[Supported Operations](./SupportedOperations.md)

[Arriving Soon](./ArrivingSoon.md)

## General notes on `C_VEC`

### On performance

These are *not* performance-oriented implementations -- this is an exercise in seeing what I can do with macros. My goal is to make things easier to do in `C` when compared to other, more feature-filled languages like `Haskell`.

### On bugs

Part of the reason that I started this project was to force myself to gain experience with unit-testing framework available for `C` language projects.

This project, uses Google's Googletest unit testing framework in an effort to have some amount of code coverage and to spot bugs before the changes that introduce them are committed.

However, it is unlikely that I alone will be able cover the entire use-space. `C_VEC` is meant to be flexible enough that it can be used in a wide variety of ways -- ways that I cannot imagine. Due to that, it is unlikely that I will be able to test all, or even many, of the ways in which this library could be used.

In addition to being able to cover the wide number of ways that the library can be used, debugging macros is a notoriously difficult task.

There *are almost certainly* bugs.

### Don't let the names fool you

Though some of the function names may look or sound cool or foreign to those unfamiliar with functional languages, make no mistake -- these are not the beautiful, shiny, and pure tools that functional languages have; these are only pale imitations of them meant to make things that I do in `C` more bearable. In fact, some of what I hope to achieve with this library goes against some of the core tenants of good `C` -- generic, have-it-if-you-need-it functions that aren't built to take advantage of the hardware that it runs on.
