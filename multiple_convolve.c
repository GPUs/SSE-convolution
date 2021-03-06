/* Copyright (C) 2013 Henry Gomersall <heng@cantab.net> 
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the organization nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY  THE AUTHOR ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

/* A macro that outputs a wrapper for each of the convolution routines.
 * The macro passed a name conv_func will output a function called
 * conv_func_multiple and it will have signature:
 * conv_func_multiple(float* in, float* out, int length,
 *                    float* kernel, int kernel_length, int N)
 * 
 * The additional N defines how many times to run the convolution function
 * conv_func(float* in, float* out, int length,
 *                    float* kernel, int kernel_length)
 * */

#include "convolve.h"

#ifndef MULTIPLE_CONVOLVE
#define MULTIPLE_CONVOLVE(FUNCTION_NAME) \
int FUNCTION_NAME ## _multiple(float* in, float* out, int length, \
        float* kernel, int kernel_length, int N) \
{ \
    for(int i=0; i<N; i++){ \
        FUNCTION_NAME(in, out, length, kernel, kernel_length); \
    } \
 \
    return 0; \
}
#endif

MULTIPLE_CONVOLVE(convolve_naive);
MULTIPLE_CONVOLVE(convolve_reversed_naive);

#ifdef SSE3
MULTIPLE_CONVOLVE(convolve_sse_simple);
MULTIPLE_CONVOLVE(convolve_sse_partial_unroll);
MULTIPLE_CONVOLVE(convolve_sse_in_aligned);
MULTIPLE_CONVOLVE(convolve_sse_in_aligned_fixed_kernel);
MULTIPLE_CONVOLVE(convolve_sse_unrolled_avx_vector);
MULTIPLE_CONVOLVE(convolve_sse_unrolled_vector);

#endif

#ifdef AVX
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_unaligned);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_unaligned_fma);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_m128_load);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_partial_aligned);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_aligned);
MULTIPLE_CONVOLVE(convolve_avx_unrolled_vector_local_output);

#endif
