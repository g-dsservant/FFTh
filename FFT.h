#ifndef FFTh
#define FFTh


typedef struct Complex {
	double real;
	double imag;
}complex;

#define PI 3.14159265358979

double*  MagnitudeVec(complex* input, size_t n);                                    	//Computes Magnitudes of components of a complex Array/Vcetor
complex* ArrToComplex(double arr[], size_t n, size_t stride, size_t* new_size);		//Converts a Real valued array to Complex datatype array where the size of Complex array is stored in 'new_size' 
size_t   ZeroPad(complex** input, size_t n);						//Resizes the Complex array to the lowest power of 2 that is also greater than it's current size
void     FFT(complex* input, size_t n);							//Computes DFT using FFT algorithm (in place) on inputs of size's of 2^N	
void     IFFT(complex* input, size_t n);						//Computes IDFT using IFFT algorithm (in place) on inputs of size's of 2^N

#endif //FFTh




#ifdef FFTh_IMPLEMENTATION
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>


double* MagnitudeVec(complex* input, size_t n) {

	double* new = (double*)malloc(sizeof(double)*n);
	for (int i = 0; i < n; ++i) {
		new[i] = sqrt( (input[i].real * input[i].real) + (input[i].imag * input[i].imag) );
	}
	return new;
}



complex* ArrToComplex(double arr[], size_t n, size_t stride, size_t* new_size) {

	size_t NewSize = (n + stride - 1)/stride;

	*new_size = NewSize;

	complex *new = (complex*)malloc(sizeof(complex) * NewSize);
	
	for (int i = 0; i < NewSize; ++i) {
		new[i].real = arr[i*stride];
		new[i].imag = 0.0f;
	}

	return new;
}


size_t ZeroPad(complex** input, size_t n) {

	if ( (n > 0) && (n & (n - 1)) == 0 ) {
		return n;
	}
    
    size_t n_new = n;
    uint8_t pos = 0;

    while (n_new > 1) {
    	n_new >>= 1;
    	++pos; 
    }

    n_new = 1;
    n_new <<= (pos+1);

    complex *new = (complex*)realloc(*input, sizeof(complex)*n_new);
    if (new) {

    	*input = new;

    	for (size_t i = n; i < n_new; ++i) {
    		(*input)[i].real = (*input)[i].imag = 0.0f;
    	}

    	return n_new;
    }

    else {
    	return 0;
    }
}


void FFT(complex *input, size_t n) {

	if (n == 0) return;
	
	if (!( (n > 0) && (n & (n - 1)) == 0 ) ) { //if it is not a power of 2
		return;
	}
	
	if (n == 1) {
		return;
	}

	complex *even = (complex*)malloc(sizeof(complex)*(n/2));
	complex *odd = (complex*)malloc(sizeof(complex)*(n/2));

	for (int i = 0; i < n/2; ++i) {
		even[i] = input[2*i];
		odd[i]  = input[2*i + 1];
	}

	FFT(even, n/2);
	FFT(odd , n/2);



	for (int i = 0; i < n/2; ++i) {
		input[i].real = even[i].real + (cos((-2*PI*i)/n) * odd[i].real) - (sin((-2*PI*i)/n) * odd[i].imag);
		input[i].imag = even[i].imag + (cos((-2*PI*i)/n) * odd[i].imag) + (sin((-2*PI*i)/n) * odd[i].real);

		input[i + n/2].real = even[i].real - (cos((-2*PI*i)/n) * odd[i].real) + (sin((-2*PI*i)/n) * odd[i].imag);
		input[i + n/2].imag = even[i].imag - (cos((-2*PI*i)/n) * odd[i].imag) - (sin((-2*PI*i)/n) * odd[i].real);
	}

	free(even);
	free(odd);

} 


void IFFT(complex *input, size_t n) {

	if (n == 0) return;
	
	if (!( (n > 0) && (n & (n - 1)) == 0 ) ) { //if it is not a power of 2
		return;
	}
	
	if (n == 1) {
		return;
	}

	complex *even = (complex*)malloc(sizeof(complex)*(n/2));
	complex *odd = (complex*)malloc(sizeof(complex)*(n/2));

	for (int i = 0; i < n/2; ++i) {
		even[i] = input[2*i];
		odd[i]  = input[2*i + 1];
	}

	IFFT(even, n/2);
	IFFT(odd , n/2);


	double inv = 1.0/n;
	double inv_2 = n/2.0;
	for (int i = 0; i < n/2; ++i) {
		input[i].real = inv * (inv_2 * even[i].real + (cos((2*PI*i)/n) * inv_2 * odd[i].real) - (sin((2*PI*i)/n) * inv_2 * odd[i].imag));
		input[i].imag = inv * (inv_2 * even[i].imag + (cos((2*PI*i)/n) * inv_2 * odd[i].imag) + (sin((2*PI*i)/n) * inv_2 * odd[i].real));

		input[i + n/2].real = inv * (inv_2 * even[i].real - (cos((2*PI*i)/n) * inv_2 * odd[i].real) + (sin((2*PI*i)/n) * inv_2 * odd[i].imag));
		input[i + n/2].imag = inv * (inv_2 * even[i].imag - (cos((2*PI*i)/n) * inv_2 * odd[i].imag) - (sin((2*PI*i)/n) * inv_2 * odd[i].real));

	}

	free(even);
	free(odd);

}

#endif //FFTh_IMPLEMENTATION 
