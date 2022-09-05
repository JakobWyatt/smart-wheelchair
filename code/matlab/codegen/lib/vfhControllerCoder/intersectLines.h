//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// intersectLines.h
//
// Code generation for function 'intersectLines'
//

#ifndef INTERSECTLINES_H
#define INTERSECTLINES_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace nav {
namespace algs {
namespace internal {
namespace impl {
void intersectLines(const double line1[4], const double line2[8],
                    double point[4]);

}
} // namespace internal
} // namespace algs
} // namespace nav
} // namespace coder

#endif
// End of code generation (intersectLines.h)
