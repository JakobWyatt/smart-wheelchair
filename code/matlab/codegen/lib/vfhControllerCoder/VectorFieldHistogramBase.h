//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// VectorFieldHistogramBase.h
//
// Code generation for function 'VectorFieldHistogramBase'
//

#ifndef VECTORFIELDHISTOGRAMBASE_H
#define VECTORFIELDHISTOGRAMBASE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class controllerVFH;

class lidarScan;

} // namespace coder

// Function Declarations
void b_binary_expand_op(double in1_data[], int *in1_size,
                        const coder::lidarScan *in2);

void binary_expand_op(double in1_data[], int *in1_size,
                      const coder::lidarScan *in2);

void binary_expand_op(double in1_data[], int *in1_size,
                      const coder::lidarScan *in2, const double in3_data[],
                      const int *in3_size);

void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                      const int *in2_size, const double in3_data[],
                      const int *in3_size);

void binary_expand_op(unsigned char in1_data[], const unsigned char in3_data[],
                      const signed char in4[2], int in5);

void binary_expand_op(double in1_data[], int in1_size[2],
                      const double in2_data[], const signed char in4_data[],
                      const int in4_size[2], const signed char in5[2],
                      double in6, const signed char in7[2], double in8);

void c_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const coder::controllerVFH *in3,
                        const coder::lidarScan *in4);

void d_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const coder::controllerVFH *in3,
                        const coder::lidarScan *in4);

void e_binary_expand_op(double in1_data[], int *in1_size,
                        const coder::lidarScan *in2);

void plus(double in1_data[], int *in1_size, const double in2_data[],
          const int *in2_size);

#endif
// End of code generation (VectorFieldHistogramBase.h)
