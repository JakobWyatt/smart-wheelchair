//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// rangeSensor.h
//
// Code generation for function 'rangeSensor'
//

#ifndef RANGESENSOR_H
#define RANGESENSOR_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_3 {
  unsigned int f1[8];
};

namespace coder {
class rangeSensor {
public:
  boolean_T tunablePropertyChanged[3];
  double Range[2];
  double RangeNoise;
  double HorizontalAngleNoise;
  double pAngleSweep[258];

private:
  int isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[2];
  double pInputPrototype;
  double pR[2];
  double pRNoise;
  double pHANoise;
};

} // namespace coder

#endif
// End of code generation (rangeSensor.h)
