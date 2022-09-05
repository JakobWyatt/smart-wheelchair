//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// raycastInternal.cpp
//
// Code generation for function 'raycastInternal'
//

// Include files
#include "raycastInternal.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <math.h>

// Function Definitions
namespace coder {
namespace nav {
namespace algs {
namespace internal {
namespace impl {
void getTruncatedIncrements(const double gridSize[2], double x0, double x1,
                            double b_y0, double b_y1, boolean_T *endClipped,
                            double *n, double *xInc, double *yInc, double *dtx,
                            double *dty, double *txNext, double *tyNext)
{
  double absx;
  double dtx_tmp;
  double dx;
  double nx;
  double ny;
  double x0Floor;
  double x0Trunc;
  double x1Floor;
  double x1Trunc;
  double y0Floor;
  double y1Floor;
  int b_exponent;
  int exponent;
  int xIncSign;
  boolean_T xClipped;
  boolean_T yClipped;
  nx = 0.0;
  dx = x1 - x0;
  xIncSign = -1;
  x0Floor = std::floor(x0);
  x1Floor = std::floor(x1);
  if (std::round(x0) - x0Floor > 0.0) {
    xIncSign = 1;
  }
  dtx_tmp = std::abs(dx);
  *dtx = 1.0 / dtx_tmp;
  absx = std::abs(x1);
  if ((!std::isinf(absx)) && (!std::isnan(absx))) {
    if (absx <= 2.2250738585072014E-308) {
      absx = 4.94065645841247E-324;
    } else {
      frexp(absx, &exponent);
      absx = std::ldexp(1.0, exponent - 53);
    }
  } else {
    absx = rtNaN;
  }
  if (dtx_tmp <= 2.0 * absx) {
    *xInc = xIncSign;
    *txNext = *dtx;
  } else if (dx > 0.0) {
    *xInc = 1.0;
    *txNext = ((x0Floor + 1.0) - x0) * *dtx;
    nx = x1Floor - x0Floor;
  } else {
    *xInc = -1.0;
    *txNext = (x0 - x0Floor) * *dtx;
    nx = x0Floor - x1Floor;
  }
  x0Trunc = std::fmin(std::fmax(0.0, x0Floor), gridSize[0]);
  x1Trunc = std::fmin(std::fmax(0.0, x1Floor), gridSize[0]);
  ny = 0.0;
  dx = b_y1 - b_y0;
  xIncSign = -1;
  y0Floor = std::floor(b_y0);
  y1Floor = std::floor(b_y1);
  if (std::round(b_y0) - y0Floor > 0.0) {
    xIncSign = 1;
  }
  dtx_tmp = std::abs(dx);
  *dty = 1.0 / dtx_tmp;
  absx = std::abs(b_y1);
  if ((!std::isinf(absx)) && (!std::isnan(absx))) {
    if (absx <= 2.2250738585072014E-308) {
      absx = 4.94065645841247E-324;
    } else {
      frexp(absx, &b_exponent);
      absx = std::ldexp(1.0, b_exponent - 53);
    }
  } else {
    absx = rtNaN;
  }
  if (dtx_tmp <= 2.0 * absx) {
    *yInc = xIncSign;
    *tyNext = *dty;
  } else if (dx > 0.0) {
    *yInc = 1.0;
    *tyNext = ((y0Floor + 1.0) - b_y0) * *dty;
    ny = y1Floor - y0Floor;
  } else {
    *yInc = -1.0;
    *tyNext = (b_y0 - y0Floor) * *dty;
    ny = y0Floor - y1Floor;
  }
  absx = std::fmin(std::fmax(0.0, y0Floor), gridSize[1]);
  dx = std::fmin(std::fmax(0.0, y1Floor), gridSize[1]);
  if ((x0Floor != x0Trunc) || (x1Floor != x1Trunc)) {
    xClipped = true;
  } else {
    xClipped = false;
  }
  if ((y0Floor != absx) || (y1Floor != dx)) {
    yClipped = true;
  } else {
    yClipped = false;
  }
  if ((x1Floor != x1Trunc) || (y1Floor != dx)) {
    *endClipped = true;
  } else {
    *endClipped = false;
  }
  if (xClipped || yClipped) {
    if (xClipped && yClipped) {
      y0Floor = std::abs(y0Floor - absx) + std::abs(y1Floor - dx);
      absx = std::abs(x0Floor - x0Trunc) + std::abs(x1Floor - x1Trunc);
      dx = y0Floor / ny;
      dtx_tmp = absx / nx;
      if (std::abs(dtx_tmp) >= std::abs(dx)) {
        ny = std::ceil(ny * (1.0 - dtx_tmp));
        nx -= absx;
      } else {
        nx = std::ceil(nx * (1.0 - dx));
        ny -= y0Floor;
      }
    } else if (xClipped && (!yClipped)) {
      absx = std::abs(x0Floor - x0Trunc) + std::abs(x1Floor - x1Trunc);
      ny = std::ceil(ny * (1.0 - absx / nx));
      nx -= absx;
    } else {
      absx = std::abs(y0Floor - absx) + std::abs(y1Floor - dx);
      nx = std::ceil(nx * (1.0 - absx / ny));
      ny -= absx;
    }
  }
  *n = nx + ny;
}

void parseMapInputs(const ::coder::array<boolean_T, 2U> &varargin_1,
                    double gridSize[2], double *resolution)
{
  gridSize[0] = varargin_1.size(1);
  gridSize[1] = varargin_1.size(0);
  *resolution = 1.0;
}

} // namespace impl
} // namespace internal
} // namespace algs
} // namespace nav
} // namespace coder

// End of code generation (raycastInternal.cpp)
