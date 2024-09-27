# Assignment 1

## Introduction

This file contains instructions on how I proceeded to resolve the exercices of the assignments.

## Implementing objective functions

### Quadratic function

#### Point 2D

TODO: Write explanations

#### Point ND

TODO: Write explanations

### A non-convex function

TODO: Write explanations

## Grid Search

### Grid Search 2D

I have modified the grid_search_2d function in the GridSearch.hh file and my solution lies between lines 31 and 67. It performs a double loop that will iterate over all the defined points in the grid between the lower and the upper bound.

After compilation, I ran the following command to test my implementation:

```bash
$ ./Build/bin/GridSearch 1 -5 5 10
```

Which gives me a minimal value of -12.5 at the point x = (0, 5).

### Grid Search 3D

I have modified the grid_search_nd function in the GridSearch.hh file and my solution lies between lines 80 and 104. I also implemented a helper function that allows us to recursively iterate over the n dimension of the N-dimensional grid and compute f(x) between the lower and the upper bound.

After compilation, I ran the following command to test my implementation:

```bash
$ ./Build/bin/GridSearch 2 -2 2 4 3
```

Which gives me a minimal value of -12.0438 for x = (0, 0, -2).

The implementation is very inefficient and time consuming, since running the following example:

```bash
$ ./Build/bin/GridSearch 2 -100 100 200 4
```

Took me 135.313 seconds to complete and find the optimal solution of -77146.5.
