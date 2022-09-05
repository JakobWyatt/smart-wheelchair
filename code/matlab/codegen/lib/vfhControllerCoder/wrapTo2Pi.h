//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// wrapTo2Pi.h
//
// Code generation for function 'wrapTo2Pi'
//

#ifndef WRAPTO2PI_H
#define WRAPTO2PI_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void f_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const double in3_data[], const int *in3_size);

void g_binary_expand_op(boolean_T in1_data[], int in1_size[2],
                        const double in2_data[], const int in2_size[2],
                        const double in3_data[], const int in3_size[2]);

#endif
// End of code generation (wrapTo2Pi.h)
