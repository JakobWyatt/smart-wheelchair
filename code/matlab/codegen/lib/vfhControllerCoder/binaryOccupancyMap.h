//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// binaryOccupancyMap.h
//
// Code generation for function 'binaryOccupancyMap'
//

#ifndef BINARYOCCUPANCYMAP_H
#define BINARYOCCUPANCYMAP_H

// Include files
#include "CircularBuffer.h"
#include "CircularBufferIndex.h"
#include "SharedMapProperties.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class binaryOccupancyMap {
public:
  matlabshared::autonomous::internal::SharedMapProperties SharedProperties;
  matlabshared::autonomous::internal::CircularBufferIndex Index;
  matlabshared::autonomous::internal::CircularBuffer Buffer;
  boolean_T DefaultValueInternal;
  boolean_T HasParent;
  double DataSize[2];
};

} // namespace coder

#endif
// End of code generation (binaryOccupancyMap.h)
