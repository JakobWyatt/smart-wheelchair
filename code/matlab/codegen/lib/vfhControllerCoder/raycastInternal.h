//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// raycastInternal.h
//
// Code generation for function 'raycastInternal'
//

#ifndef RAYCASTINTERNAL_H
#define RAYCASTINTERNAL_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace nav {
namespace algs {
namespace internal {
namespace impl {
void getTruncatedIncrements(const double gridSize[2], double x0, double x1,
                            double b_y0, double b_y1, boolean_T *endClipped,
                            double *n, double *xInc, double *yInc, double *dtx,
                            double *dty, double *txNext, double *tyNext);

void parseMapInputs(const ::coder::array<boolean_T, 2U> &varargin_1,
                    double gridSize[2], double *resolution);

} // namespace impl
} // namespace internal
} // namespace algs
} // namespace nav
} // namespace coder

#endif
// End of code generation (raycastInternal.h)
