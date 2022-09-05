//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// VectorFieldHistogramBase.cpp
//
// Code generation for function 'VectorFieldHistogramBase'
//

// Include files
#include "VectorFieldHistogramBase.h"
#include "controllerVFH.h"
#include "lidarScan.h"
#include "rt_nonfinite.h"
#include "vfhControllerCoder_internal_types.h"
#include <algorithm>

// Function Definitions
void b_binary_expand_op(double in1_data[], int *in1_size,
                        const coder::lidarScan *in2)
{
  double in2_data[258];
  int in2_size;
  int stride_0_0;
  int stride_1_0;
  if (*in1_size == 1) {
    in2_size = in2->InternalRanges.size[0];
  } else {
    in2_size = *in1_size;
  }
  stride_0_0 = (in2->InternalRanges.size[0] != 1);
  stride_1_0 = (*in1_size != 1);
  if (*in1_size == 1) {
    *in1_size = in2->InternalRanges.size[0];
  }
  for (int i{0}; i < *in1_size; i++) {
    in2_data[i] =
        in2->InternalRanges.data[i * stride_0_0] * in1_data[i * stride_1_0];
  }
  *in1_size = in2_size;
  if (in2_size - 1 >= 0) {
    std::copy(&in2_data[0], &in2_data[in2_size], &in1_data[0]);
  }
}

void binary_expand_op(double in1_data[], int *in1_size,
                      const coder::lidarScan *in2)
{
  double tmp_data[258];
  int stride_0_0;
  int stride_1_0;
  int tmp_size;
  if (*in1_size == 1) {
    tmp_size = in2->InternalRanges.size[0];
  } else {
    tmp_size = *in1_size;
  }
  stride_0_0 = (in2->InternalRanges.size[0] != 1);
  stride_1_0 = (*in1_size != 1);
  if (*in1_size == 1) {
    *in1_size = in2->InternalRanges.size[0];
  }
  for (int i{0}; i < *in1_size; i++) {
    tmp_data[i] = 0.0 - in2->InternalRanges.data[i * stride_0_0] *
                            in1_data[i * stride_1_0];
  }
  *in1_size = tmp_size;
  if (tmp_size - 1 >= 0) {
    std::copy(&tmp_data[0], &tmp_data[tmp_size], &in1_data[0]);
  }
}

void binary_expand_op(double in1_data[], int *in1_size,
                      const coder::lidarScan *in2, const double in3_data[],
                      const int *in3_size)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (*in3_size == 1) {
    *in1_size = in2->InternalAngles.size[0];
  } else {
    *in1_size = *in3_size;
  }
  stride_0_0 = (in2->InternalAngles.size[0] != 1);
  stride_1_0 = (*in3_size != 1);
  if (*in3_size == 1) {
    loop_ub = in2->InternalAngles.size[0];
  } else {
    loop_ub = *in3_size;
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[i] =
        in2->InternalAngles.data[i * stride_0_0] + in3_data[i * stride_1_0];
  }
}

void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                      const int *in2_size, const double in3_data[],
                      const int *in3_size)
{
  double b_in1_data[258];
  int b_in1_size;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  if (*in3_size == 1) {
    if (*in2_size == 1) {
      b_in1_size = *in1_size;
    } else {
      b_in1_size = *in2_size;
    }
  } else {
    b_in1_size = *in3_size;
  }
  stride_0_0 = (*in1_size != 1);
  stride_1_0 = (*in2_size != 1);
  stride_2_0 = (*in3_size != 1);
  if (*in3_size == 1) {
    if (*in2_size != 1) {
      *in1_size = *in2_size;
    }
  } else {
    *in1_size = *in3_size;
  }
  for (int i{0}; i < *in1_size; i++) {
    b_in1_data[i] = (in1_data[i * stride_0_0] + in2_data[i * stride_1_0]) +
                    in3_data[i * stride_2_0];
  }
  *in1_size = b_in1_size;
  if (b_in1_size - 1 >= 0) {
    std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
  }
}

void binary_expand_op(unsigned char in1_data[], const unsigned char in3_data[],
                      const signed char in4[2], int in5)
{
  int stride_0_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in4[1];
  stride_0_1 = (in5 + 1 != 1);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in5 + 1;
  }
  for (int i{0}; i < unnamed_idx_1; i++) {
    in1_data[2 * i + 1] =
        static_cast<unsigned char>(in3_data[2 * (i * stride_0_1) + 1] - 1U);
  }
}

void binary_expand_op(double in1_data[], int in1_size[2],
                      const double in2_data[], const signed char in4_data[],
                      const int in4_size[2], const signed char in5[2],
                      double in6, const signed char in7[2], double in8)
{
  double b_in2_data[90];
  double c_in2_data[90];
  int b_in2_size_idx_1;
  int b_unnamed_idx_1;
  int in2_size_idx_1;
  int stride_0_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in5[1];
  b_unnamed_idx_1 = in7[1];
  if (unnamed_idx_1 == 1) {
    in2_size_idx_1 = in4_size[1];
  } else {
    in2_size_idx_1 = unnamed_idx_1;
  }
  stride_0_1 = (in4_size[1] != 1);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in4_size[1];
  }
  for (int i{0}; i < unnamed_idx_1; i++) {
    b_in2_data[i] = in2_data[2 * (in4_data[i * stride_0_1] - 1)] + in6 / 2.0;
  }
  if (b_unnamed_idx_1 == 1) {
    b_in2_size_idx_1 = in4_size[1];
  } else {
    b_in2_size_idx_1 = b_unnamed_idx_1;
  }
  stride_0_1 = (in4_size[1] != 1);
  if (b_unnamed_idx_1 == 1) {
    unnamed_idx_1 = in4_size[1];
  } else {
    unnamed_idx_1 = b_unnamed_idx_1;
  }
  for (int i{0}; i < unnamed_idx_1; i++) {
    c_in2_data[i] =
        in2_data[2 * (in4_data[i * stride_0_1] - 1) + 1] - in8 / 2.0;
  }
  in1_size[0] = 1;
  in1_size[1] = in2_size_idx_1 + b_in2_size_idx_1;
  if (in2_size_idx_1 - 1 >= 0) {
    std::copy(&b_in2_data[0], &b_in2_data[in2_size_idx_1], &in1_data[0]);
  }
  for (int i{0}; i < b_in2_size_idx_1; i++) {
    in1_data[i + in2_size_idx_1] = c_in2_data[i];
  }
}

void c_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const coder::controllerVFH *in3,
                        const coder::lidarScan *in4)
{
  double b_in3;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  b_in3 = (in3->MinTurningRadius + in3->RobotRadius) + in3->SafetyDistance;
  if (in4->InternalAngles.size[0] == 1) {
    *in1_size = *in2_size;
  } else {
    *in1_size = in4->InternalAngles.size[0];
  }
  stride_0_0 = (*in2_size != 1);
  stride_1_0 = (in4->InternalAngles.size[0] != 1);
  if (in4->InternalAngles.size[0] == 1) {
    loop_ub = *in2_size;
  } else {
    loop_ub = in4->InternalAngles.size[0];
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[i] = ((in2_data[i * stride_0_0] < b_in3) &&
                   (in4->InternalAngles.data[i * stride_1_0] >= 0.0));
  }
}

void d_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const coder::controllerVFH *in3,
                        const coder::lidarScan *in4)
{
  double b_in3;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  b_in3 = (in3->MinTurningRadius + in3->RobotRadius) + in3->SafetyDistance;
  if (in4->InternalAngles.size[0] == 1) {
    *in1_size = *in2_size;
  } else {
    *in1_size = in4->InternalAngles.size[0];
  }
  stride_0_0 = (*in2_size != 1);
  stride_1_0 = (in4->InternalAngles.size[0] != 1);
  if (in4->InternalAngles.size[0] == 1) {
    loop_ub = *in2_size;
  } else {
    loop_ub = in4->InternalAngles.size[0];
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[i] = ((in2_data[i * stride_0_0] < b_in3) &&
                   (in4->InternalAngles.data[i * stride_1_0] <= 0.0));
  }
}

void e_binary_expand_op(double in1_data[], int *in1_size,
                        const coder::lidarScan *in2)
{
  double in2_data[258];
  int in2_size;
  int stride_0_0;
  int stride_1_0;
  if (*in1_size == 1) {
    in2_size = in2->InternalAngles.size[0];
  } else {
    in2_size = *in1_size;
  }
  stride_0_0 = (in2->InternalAngles.size[0] != 1);
  stride_1_0 = (*in1_size != 1);
  if (*in1_size == 1) {
    *in1_size = in2->InternalAngles.size[0];
  }
  for (int i{0}; i < *in1_size; i++) {
    in2_data[i] =
        in2->InternalAngles.data[i * stride_0_0] - in1_data[i * stride_1_0];
  }
  *in1_size = in2_size;
  if (in2_size - 1 >= 0) {
    std::copy(&in2_data[0], &in2_data[in2_size], &in1_data[0]);
  }
}

void plus(double in1_data[], int *in1_size, const double in2_data[],
          const int *in2_size)
{
  double b_in1_data[258];
  int b_in1_size;
  int stride_0_0;
  int stride_1_0;
  if (*in2_size == 1) {
    b_in1_size = *in1_size;
  } else {
    b_in1_size = *in2_size;
  }
  stride_0_0 = (*in1_size != 1);
  stride_1_0 = (*in2_size != 1);
  if (*in2_size != 1) {
    *in1_size = *in2_size;
  }
  for (int i{0}; i < *in1_size; i++) {
    b_in1_data[i] = in1_data[i * stride_0_0] + in2_data[i * stride_1_0];
  }
  *in1_size = b_in1_size;
  if (b_in1_size - 1 >= 0) {
    std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
  }
}

// End of code generation (VectorFieldHistogramBase.cpp)
