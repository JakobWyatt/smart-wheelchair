//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// cross.cpp
//
// Code generation for function 'cross'
//

// Include files
#include "cross.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder {
void cross(const double a_data[], const int a_size[2], const double b_data[],
           double c_data[], int c_size[2])
{
  c_size[0] = a_size[0];
  c_size[1] = 3;
  if (a_size[0] != 0) {
    int dim;
    int iNext;
    int nHigh;
    int stride;
    int stridem1;
    boolean_T exitg1;
    dim = 0;
    nHigh = 0;
    exitg1 = false;
    while ((!exitg1) && (nHigh < 2)) {
      if (a_size[nHigh] == 3) {
        dim = nHigh + 1;
        exitg1 = true;
      } else {
        nHigh++;
      }
    }
    if (dim >= 2) {
      stride = a_size[0];
      stridem1 = a_size[0] - 1;
    } else {
      stride = 1;
      stridem1 = 0;
    }
    iNext = stride * 3;
    if (dim >= 2) {
      nHigh = 1;
    } else {
      nHigh = (iNext << 1) + 1;
    }
    for (int iStart{1}; iNext < 0 ? iStart >= nHigh : iStart <= nHigh;
         iStart += iNext) {
      dim = iStart + stridem1;
      for (int i1{iStart}; i1 <= dim; i1++) {
        double b_c_data_tmp;
        double c_data_tmp;
        int i2;
        int i3;
        i2 = (i1 + stride) - 1;
        i3 = i2 + stride;
        c_data[i1 - 1] = a_data[i2] * b_data[i3] - a_data[i3] * b_data[i2];
        c_data_tmp = a_data[i1 - 1];
        b_c_data_tmp = b_data[i1 - 1];
        c_data[i2] = a_data[i3] * b_c_data_tmp - c_data_tmp * b_data[i3];
        c_data[i3] = c_data_tmp * b_data[i2] - a_data[i2] * b_c_data_tmp;
      }
    }
  }
}

} // namespace coder

// End of code generation (cross.cpp)
