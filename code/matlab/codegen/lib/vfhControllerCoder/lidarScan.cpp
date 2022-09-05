//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// lidarScan.cpp
//
// Code generation for function 'lidarScan'
//

// Include files
#include "lidarScan.h"
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "vfhControllerCoder_internal_types.h"
#include "wrapToPi.h"
#include "rtGetInf.h"
#include <algorithm>
#include <cmath>

// Function Definitions
namespace coder {
void lidarScan::removeInvalidData(const double varargin_2[2],
                                  lidarScan *objOut) const
{
  static double dv[2]{0.0, 0.0};
  int loop_ub;
  boolean_T b_tmp_data[258];
  boolean_T c_tmp_data[258];
  boolean_T tmp_data[258];
  boolean_T validIdx_data[258];
  boolean_T validRangeLimitIndices_data[258];
  boolean_T exitg1;
  boolean_T p;
  dv[1U] = rtGetInf();
  objOut->InternalRanges.size[0] = InternalRanges.size[0];
  loop_ub = InternalRanges.size[0];
  if (loop_ub - 1 >= 0) {
    std::copy(&InternalRanges.data[0], &InternalRanges.data[loop_ub],
              &objOut->InternalRanges.data[0]);
  }
  objOut->InternalAngles.size[0] = InternalAngles.size[0];
  loop_ub = InternalAngles.size[0];
  if (loop_ub - 1 >= 0) {
    std::copy(&InternalAngles.data[0], &InternalAngles.data[loop_ub],
              &objOut->InternalAngles.data[0]);
  }
  robotics::internal::wrapToPi(objOut->InternalAngles.data,
                               &objOut->InternalAngles.size[0]);
  objOut->ContainsOnlyFiniteData = true;
  for (int i{0}; i < 258; i++) {
    validRangeLimitIndices_data[i] = true;
  }
  p = true;
  loop_ub = 0;
  exitg1 = false;
  while ((!exitg1) && (loop_ub < 2)) {
    if (!(varargin_2[loop_ub] == dv[loop_ub])) {
      p = false;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  if (!p) {
    loop_ub = InternalRanges.size[0];
    for (int i{0}; i < loop_ub; i++) {
      double d;
      d = InternalRanges.data[i];
      validRangeLimitIndices_data[i] =
          ((d >= varargin_2[0]) && (d <= varargin_2[1]));
    }
  }
  loop_ub = InternalRanges.size[0];
  for (int i{0}; i < loop_ub; i++) {
    validIdx_data[i] = std::isinf(InternalRanges.data[i]);
  }
  loop_ub = InternalRanges.size[0];
  for (int i{0}; i < loop_ub; i++) {
    tmp_data[i] = std::isnan(InternalRanges.data[i]);
  }
  loop_ub = objOut->InternalAngles.size[0];
  for (int i{0}; i < loop_ub; i++) {
    b_tmp_data[i] = std::isinf(objOut->InternalAngles.data[i]);
  }
  loop_ub = objOut->InternalAngles.size[0];
  for (int i{0}; i < loop_ub; i++) {
    c_tmp_data[i] = std::isnan(objOut->InternalAngles.data[i]);
  }
  for (int i{0}; i < 258; i++) {
    validIdx_data[i] = ((!validIdx_data[i]) && (!tmp_data[i]) &&
                        ((!b_tmp_data[i]) && (!c_tmp_data[i])) &&
                        validRangeLimitIndices_data[i]);
  }
  p = true;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub < 259)) {
    if (!validIdx_data[loop_ub - 1]) {
      p = false;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  if (!p) {
    for (int i{0}; i < 258; i++) {
      validIdx_data[i] = !validIdx_data[i];
    }
    internal::nullAssignment(objOut->InternalAngles.data,
                             &objOut->InternalAngles.size[0], validIdx_data);
    objOut->InternalRanges.size[0] = InternalRanges.size[0];
    loop_ub = InternalRanges.size[0];
    if (loop_ub - 1 >= 0) {
      std::copy(&InternalRanges.data[0], &InternalRanges.data[loop_ub],
                &objOut->InternalRanges.data[0]);
    }
    internal::nullAssignment(objOut->InternalRanges.data,
                             &objOut->InternalRanges.size[0], validIdx_data);
    robotics::internal::wrapToPi(objOut->InternalAngles.data,
                                 &objOut->InternalAngles.size[0]);
    objOut->ContainsOnlyFiniteData = true;
  }
}

} // namespace coder

// End of code generation (lidarScan.cpp)
