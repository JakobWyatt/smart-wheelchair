//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// raycast.h
//
// Code generation for function 'raycast'
//

#ifndef RAYCAST_H
#define RAYCAST_H

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
void raycast(const double p1[2], const double p2[2],
             const ::coder::array<boolean_T, 2U> &map,
             const double gridLocation[2], boolean_T *p,
             double collisionGridPts[2]);

}
} // namespace algs
} // namespace nav
} // namespace coder

#endif
// End of code generation (raycast.h)
