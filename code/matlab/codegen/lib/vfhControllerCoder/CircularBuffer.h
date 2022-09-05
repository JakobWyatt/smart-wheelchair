//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// CircularBuffer.h
//
// Code generation for function 'CircularBuffer'
//

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace matlabshared {
namespace autonomous {
namespace internal {
class CircularBufferIndex;

}
} // namespace autonomous
} // namespace matlabshared
} // namespace coder

// Type Definitions
namespace coder {
namespace matlabshared {
namespace autonomous {
namespace internal {
class CircularBuffer {
public:
  CircularBufferIndex *Index;
  array<boolean_T, 2U> Buffer;
};

} // namespace internal
} // namespace autonomous
} // namespace matlabshared
} // namespace coder

#endif
// End of code generation (CircularBuffer.h)
