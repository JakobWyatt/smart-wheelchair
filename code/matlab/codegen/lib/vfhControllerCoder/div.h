//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// div.h
//
// Code generation for function 'div'
//

#ifndef DIV_H
#define DIV_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                      const int in2_size[2], const int *in3_size,
                      const double in4[4], const double in5_data[],
                      const int *in5_size, const double in6_data[],
                      const int *in6_size);

void binary_expand_op(double in1_data[], int *in1_size, const double in2[4],
                      const double in3_data[], const int in3_size[2],
                      const int *in4_size, const double in5_data[],
                      const int *in5_size, const double in6_data[],
                      const int *in6_size);

#endif
// End of code generation (div.h)
