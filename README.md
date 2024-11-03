# FFT Header-only Library (Basic)

This is a very basic library that uses an array of complex numbers in the implementation of Fast Fourier Transform (FFT).  
The algorithm used is the basic 2-radix algorithm that only supports inputs of sizes that match powers of two (i.e., size = 2^N).

## Functionalities
1. **ArrToComplex** -> Converts double arrays to an array of complex numbers and returns the pointer.
2. **ZeroPad** -> Resizes the input complex array to the least power of 2 greater than its current size.
3. **MagnitudeVec** -> Calculates the magnitude of each element in the complex array and returns a double pointer.
4. **FFT** -> 2-radix FFT algorithm based on recursion.
5. **IFFT** -> 2-radix IFFT algorithm based on recursion.

## How to Use
To use it in your own `.c` file:

1. First, download the `FFT.h` file to a folder.

2. In your code, use this on top:

   ```c
   #define FFTh_IMPLEMENTATION
   #include "FFT.h"

3. While compiling, use:

   `gcc -g -I<path/to/FFT.h> -o <output> <yourfile>.c`

   Replace <path/to/FFT.h> with the actual path where you saved the header file, and <yourfile>.c with your source file name, including any additional flags you want to use.

   
