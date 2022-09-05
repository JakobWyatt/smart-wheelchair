//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// RangeSensorBase.h
//
// Code generation for function 'RangeSensorBase'
//

#ifndef RANGESENSORBASE_H
#define RANGESENSORBASE_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class binaryOccupancyMap;

}

// Type Definitions
namespace coder {
namespace nav {
namespace internal {
class RangeSensorBase {
public:
  static void stepImpl_anonFcn1(const double angles[258],
                                const ::coder::array<boolean_T, 2U> &grid,
                                const binaryOccupancyMap *map,
                                const double pose[3], double varargout_1[258]);
};

} // namespace internal
} // namespace nav
} // namespace coder

#endif
// End of code generation (RangeSensorBase.h)
