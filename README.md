# FFT Header-only Library (Basic)
This is a very basic library that uses an array of complex numbers in the implementation of Fast Fourier Transform (FFT).
The algorithm used is the basic 2-radix algorithm that only supports inputs of sizes that match powers of two (i.e size = 2^N).

## Functionalities 
  1) ArrToComplex -> Converts double arrays to an array of complex numbers and returns the pointer.
  2) ZeroPad -> Resizes the input complex array to the least power of 2 greater than it's current size.
  3) MagnitudeVec -> Calculates the magnitude of each element in the complex array and returns a double pointer.
  4) FFT -> 2-radix FFT algorithm based on recursion.
  5) IFFT -> 2-radix IFFT algorithm based on recursion.

## How to use
  To use it in your own .c file,

  First download the "FFT.h" file to a folder.

  In your code, use this on top:  
  '''c
  #define FFTh_IMPLEMENTATION
  #include "FFT.h"

  And then, while compiling, use:
  'gcc -g -I<path/to/FFT.h> -o <output> <yourfile>.c'
  and ofcourse whatever addition flags you want to use.

  
