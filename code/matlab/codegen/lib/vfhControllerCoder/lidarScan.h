//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// lidarScan.h
//
// Code generation for function 'lidarScan'
//

#ifndef LIDARSCAN_H
#define LIDARSCAN_H

// Include files
#include "rtwtypes.h"
#include "vfhControllerCoder_internal_types.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class lidarScan {
public:
  void removeInvalidData(const double varargin_2[2], lidarScan *objOut) const;
  emxArray_real_T_258 InternalRanges;
  emxArray_real_T_258 InternalAngles;
  boolean_T ContainsOnlyFiniteData;
};

} // namespace coder

#endif
// End of code generation (lidarScan.h)
