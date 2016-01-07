# predicates

This library provides code for performing robust geometric computations using adaptive-precision floating-point arithmetic.
It is based on code by Jonathan Richard Shewchuk; the original source is available [here](http://www.cs.cmu.edu/afs/cs/project/quake/public/code/predicates.c).
The theory behind adaptive-precision arithmetic used in the original source was described in [a paper](http://www.cs.cmu.edu/afs/cs/project/quake/public/papers/robust-arithmetic.ps) also by Shewchuk.
These geometric predicates were used to write the mesh generation program [Triangle](http://www.cs.cmu.edu/~quake/triangle.html), which received the 2003 Wilkinson Prize for Numerical Software.

Things that have changed since the original source code was written in 1996:
* The C99 standard was ratified and implemented in free, open-source compilers (GCC, clang).
This introduces many syntactic niceties not available in K&R C, the language used in the original code.
* Compilers have gotten a whole lot smarter about optimizations like loop unrolling and function inlining.
* The most common CPU was the Intel Pentium series, which used 80-bit extended precision floating-point registers.
These were intended to give greater numerical accuracy, but instead made FP computations notoriously unpredictable; x87 floating-point arithmetic has since been deprecated in favor of SSE instructions.
* The C standard library and headers have grown substantially, obviating the need for some of the routines in the original source code.
For example, one no longer needs to calculate the machine epsilon; this is now in the standard library header `float.h`, although one has to take care which definition of epsilon is meant.
* The C math library now includes the routines `nextafter` and `nextafterf`, which return the next representable floating-point number after an input number; these procedures make it much easier to write stress tests for geometric predicates.

This repository is intended to contain an updated version of Shewchuk's original source code accounting for these developments.
The original source is one 4.5k-line C file, although full of many helpful comments.
This is somewhat hard to digest, so I'm breaking it up into several smaller files.
Additionally, I'm adding unit tests, which will demonstrate both robustness of geometric predicates implemented with adaptive-precision arithmetic and the non-robustness of naive implementations.
There will be no substantive modifications to the main routines.

Unit tests are in the directory `test/`; demonstrations of the failure of geometric predicates in floating-point arithmetic are in the directory `demos`.


## Installation

The code is built using [CMake](http://www.cmake.org) as follows:

    mkdir build
    cd build
    cmake ..
    make

To run the unit tests:

    make test
    
Demo programs are optionally built if you have `zlib` and `libpng`.
