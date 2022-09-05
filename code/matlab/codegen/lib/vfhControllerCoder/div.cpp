//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// div.cpp
//
// Code generation for function 'div'
//

// Include files
#include "div.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                      const int in2_size[2], const int *in3_size,
                      const double in4[4], const double in5_data[],
                      const int *in5_size, const double in6_data[],
                      const int *in6_size)
{
  double b_in2_data[2];
  double b_in4;
  double c_in4;
  double d_in4;
  int b_in2_size;
  int i;
  int i1;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  b_in4 = in4[2];
  c_in4 = in4[2];
  d_in4 = in4[0] * in4[3];
  i = *in3_size;
  if (*in6_size == 1) {
    if (*in5_size == 1) {
      if (i == 1) {
        i1 = *in1_size;
      } else {
        i1 = i;
      }
      if (i1 == 1) {
        b_in2_size = i;
      } else if (i == 1) {
        b_in2_size = *in1_size;
      } else {
        b_in2_size = i;
      }
    } else {
      b_in2_size = *in5_size;
    }
  } else {
    b_in2_size = *in6_size;
  }
  stride_0_0 = (i != 1);
  stride_1_0 = (i != 1);
  stride_2_0 = (*in1_size != 1);
  stride_3_0 = (i != 1);
  stride_4_0 = (*in5_size != 1);
  stride_5_0 = (*in6_size != 1);
  if (*in6_size == 1) {
    if (*in5_size == 1) {
      if (i == 1) {
        i1 = *in1_size;
      } else {
        i1 = i;
      }
      if (i1 == 1) {
        *in1_size = i;
      } else if (i != 1) {
        *in1_size = i;
      }
    } else {
      *in1_size = *in5_size;
    }
  } else {
    *in1_size = *in6_size;
  }
  for (i = 0; i < *in1_size; i++) {
    b_in2_data[i] = ((in2_data[i * stride_0_0] *
                          in2_data[i * stride_1_0 + in2_size[0] * 3] * b_in4 -
                      in1_data[i * stride_2_0] * c_in4 *
                          in2_data[i * stride_3_0 + in2_size[0] * 2]) -
                     d_in4 * in5_data[i * stride_4_0]) /
                    in6_data[i * stride_5_0];
  }
  *in1_size = b_in2_size;
  if (b_in2_size - 1 >= 0) {
    std::copy(&b_in2_data[0], &b_in2_data[b_in2_size], &in1_data[0]);
  }
}

void binary_expand_op(double in1_data[], int *in1_size, const double in2[4],
                      const double in3_data[], const int in3_size[2],
                      const int *in4_size, const double in5_data[],
                      const int *in5_size, const double in6_data[],
                      const int *in6_size)
{
  double b_in1_data[2];
  double b_in2;
  double c_in2;
  double d_in2;
  int b_in1_size;
  int b_in5_size;
  int i;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  b_in2 = in2[3];
  c_in2 = in2[1] * in2[2];
  d_in2 = in2[3];
  i = *in4_size;
  if (*in6_size == 1) {
    if (*in5_size == 1) {
      b_in5_size = i;
    } else {
      b_in5_size = *in5_size;
    }
    if (b_in5_size == 1) {
      if (i == 1) {
        b_in1_size = *in1_size;
      } else {
        b_in1_size = i;
      }
    } else if (*in5_size == 1) {
      b_in1_size = i;
    } else {
      b_in1_size = *in5_size;
    }
  } else {
    b_in1_size = *in6_size;
  }
  stride_0_0 = (*in1_size != 1);
  stride_1_0 = (i != 1);
  stride_2_0 = (i != 1);
  stride_3_0 = (i != 1);
  stride_4_0 = (*in5_size != 1);
  stride_5_0 = (*in6_size != 1);
  if (*in6_size == 1) {
    if (*in5_size == 1) {
      b_in5_size = i;
    } else {
      b_in5_size = *in5_size;
    }
    if (b_in5_size == 1) {
      if (i != 1) {
        *in1_size = i;
      }
    } else if (*in5_size == 1) {
      *in1_size = i;
    } else {
      *in1_size = *in5_size;
    }
  } else {
    *in1_size = *in6_size;
  }
  for (i = 0; i < *in1_size; i++) {
    b_in1_data[i] = ((in1_data[i * stride_0_0] * b_in2 *
                          in3_data[i * stride_1_0 + in3_size[0] * 3] +
                      c_in2 * in3_data[i * stride_2_0 + in3_size[0] * 3]) -
                     in3_data[i * stride_3_0 + in3_size[0]] *
                         in5_data[i * stride_4_0] * d_in2) /
                    in6_data[i * stride_5_0];
  }
  *in1_size = b_in1_size;
  if (b_in1_size - 1 >= 0) {
    std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
  }
}

// End of code generation (div.cpp)
