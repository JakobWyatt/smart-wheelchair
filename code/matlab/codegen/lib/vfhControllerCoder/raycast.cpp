//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// raycast.cpp
//
// Code generation for function 'raycast'
//

// Include files
#include "raycast.h"
#include "eps.h"
#include "minOrMax.h"
#include "raycastInternal.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace nav {
namespace algs {
namespace internal {
void raycast(const double p1[2], const double p2[2],
             const ::coder::array<boolean_T, 2U> &map,
             const double gridLocation[2], boolean_T *p,
             double collisionGridPts[2])
{
  array<double, 1U> xp;
  array<double, 1U> yp;
  double endPtX_data[4];
  double endPtY_data[4];
  double gridSize[2];
  double b_x_tmp;
  double b_y0;
  double b_y1;
  double dtx;
  double dty;
  double i;
  double n;
  double txNext;
  double tyNext;
  double x;
  double x0;
  double x1;
  double xInc;
  double x_tmp;
  double y;
  double yInc;
  int b_p;
  int loop_ub_tmp;
  boolean_T endClipped;
  boolean_T exitg1;
  impl::parseMapInputs(map, gridSize, &y);
  collisionGridPts[0] = rtNaN;
  collisionGridPts[1] = rtNaN;
  *p = true;
  x0 = p1[0] - gridLocation[0];
  b_y0 = p1[1] - gridLocation[1];
  x_tmp = std::floor(x0);
  b_x_tmp = std::floor(b_y0);
  x = x_tmp + 1.0;
  y = b_x_tmp + 1.0;
  x1 = p2[0] - gridLocation[0];
  b_y1 = p2[1] - gridLocation[1];
  impl::getTruncatedIncrements(gridSize, x0, x1, b_y0, b_y1, &endClipped, &n,
                               &xInc, &yInc, &dtx, &dty, &txNext, &tyNext);
  if (n != 0.0) {
    double iter;
    loop_ub_tmp =
        static_cast<int>(3.0 * ::coder::internal::maximum(gridSize) + 4.0);
    xp.set_size(loop_ub_tmp);
    yp.set_size(loop_ub_tmp);
    for (b_p = 0; b_p < loop_ub_tmp; b_p++) {
      xp[b_p] = rtNaN;
      yp[b_p] = rtNaN;
    }
    xp[0] = x_tmp + 1.0;
    yp[0] = b_x_tmp + 1.0;
    i = 1.0;
    iter = 1.0;
    while (iter <= n) {
      if (std::abs(tyNext - txNext) < 1.0E-15) {
        x += xInc;
        txNext += dtx;
        y += yInc;
        tyNext += dty;
        xp[static_cast<int>(i + 1.0) - 1] = x;
        yp[static_cast<int>(i + 1.0) - 1] = y - yInc;
        xp[static_cast<int>(i + 2.0) - 1] = x - xInc;
        yp[static_cast<int>(i + 2.0) - 1] = y;
        xp[static_cast<int>(i + 3.0) - 1] = x;
        yp[static_cast<int>(i + 3.0) - 1] = y;
        i += 3.0;
        iter += 2.0;
      } else {
        if (tyNext < txNext) {
          y += yInc;
          tyNext += dty;
          xp[static_cast<int>(i + 1.0) - 1] = x;
          yp[static_cast<int>(i + 1.0) - 1] = y;
          i++;
          if ((txNext > 1.0E+10) &&
              (std::abs(std::round(x0) - x0) <= eps(x0))) {
            xp[static_cast<int>(i + 1.0) - 1] = x + xInc;
            yp[static_cast<int>(i + 1.0) - 1] = y;
            i++;
          }
        } else if (tyNext > txNext) {
          x += xInc;
          txNext += dtx;
          xp[static_cast<int>(i + 1.0) - 1] = x;
          yp[static_cast<int>(i + 1.0) - 1] = y;
          i++;
          if ((tyNext > 1.0E+10) &&
              (std::abs(std::round(b_y0) - b_y0) <= eps(b_y0))) {
            xp[static_cast<int>(i + 1.0) - 1] = x;
            yp[static_cast<int>(i + 1.0) - 1] = y + yInc;
            i++;
          }
        }
        iter++;
      }
    }
  } else {
    i = 1.0;
    xp.set_size(1);
    xp[0] = x_tmp + 1.0;
    yp.set_size(1);
    yp[0] = b_x_tmp + 1.0;
  }
  if (endClipped) {
    loop_ub_tmp = 0;
  } else {
    x = std::floor(x1);
    if (std::abs(x1 - x) <= 2.0 * eps(x1)) {
      y = std::floor(b_y1);
      if (std::abs(b_y1 - y) <= 2.0 * eps(b_y1)) {
        loop_ub_tmp = 4;
        endPtX_data[0] = x;
        endPtY_data[0] = y + 1.0;
        endPtX_data[1] = x + 1.0;
        endPtY_data[1] = y;
        endPtX_data[2] = x;
        endPtY_data[2] = y;
        endPtX_data[3] = x + 1.0;
        endPtY_data[3] = y + 1.0;
      } else {
        y = std::ceil(b_y1);
        if (std::abs(b_y1 - y) <= 2.0 * eps(b_y1)) {
          loop_ub_tmp = 4;
          endPtX_data[0] = x;
          endPtY_data[0] = y + 1.0;
          endPtX_data[1] = x + 1.0;
          endPtY_data[1] = y;
          endPtX_data[2] = x;
          endPtY_data[2] = y;
          endPtX_data[3] = x + 1.0;
          endPtY_data[3] = y + 1.0;
        } else {
          loop_ub_tmp = 1;
          endPtX_data[0] = x;
          endPtY_data[0] = std::floor(b_y1) + 1.0;
        }
      }
    } else {
      y = std::ceil(x1);
      if (std::abs(x1 - y) <= 2.0 * eps(x1)) {
        if (std::abs(b_y1 - std::floor(b_y1)) <= eps(b_y1)) {
          loop_ub_tmp = 4;
          x = std::floor(b_y1);
          endPtX_data[0] = y;
          endPtY_data[0] = x + 1.0;
          endPtX_data[1] = y + 1.0;
          endPtY_data[1] = x;
          endPtX_data[2] = y;
          endPtY_data[2] = x;
          endPtX_data[3] = y + 1.0;
          endPtY_data[3] = x + 1.0;
        } else {
          x = std::ceil(b_y1);
          if (std::abs(b_y1 - x) <= 2.0 * eps(b_y1)) {
            loop_ub_tmp = 4;
            endPtX_data[0] = y;
            endPtY_data[0] = x + 1.0;
            endPtX_data[1] = y + 1.0;
            endPtY_data[1] = x;
            endPtX_data[2] = y;
            endPtY_data[2] = x;
            endPtX_data[3] = y + 1.0;
            endPtY_data[3] = x + 1.0;
          } else {
            loop_ub_tmp = 1;
            endPtX_data[0] = y;
            endPtY_data[0] = std::floor(b_y1) + 1.0;
          }
        }
      } else if (std::abs(b_y1 - std::floor(b_y1)) <= 2.0 * eps(b_y1)) {
        loop_ub_tmp = 1;
        endPtX_data[0] = x + 1.0;
        endPtY_data[0] = std::floor(b_y1);
      } else {
        y = std::ceil(b_y1);
        if (std::abs(b_y1 - y) <= 2.0 * eps(b_y1)) {
          loop_ub_tmp = 1;
          endPtX_data[0] = std::floor(x1) + 1.0;
          endPtY_data[0] = y + 1.0;
        } else {
          loop_ub_tmp = 1;
          endPtX_data[0] = xp[static_cast<int>(i) - 1];
          endPtY_data[0] = yp[static_cast<int>(i) - 1];
        }
      }
    }
  }
  b_p = 0;
  exitg1 = false;
  while ((!exitg1) && (b_p <= static_cast<int>(i) - 1)) {
    if ((xp[b_p] >= 1.0) && (xp[b_p] <= gridSize[0]) && (yp[b_p] >= 1.0) &&
        (yp[b_p] <= gridSize[1])) {
      y = (gridSize[1] + 1.0) - yp[b_p];
      if (map[static_cast<int>(y + (xp[b_p] - 1.0) *
                                       static_cast<double>(map.size(0))) -
              1]) {
        *p = false;
        collisionGridPts[0] = y;
        collisionGridPts[1] = xp[b_p];
        exitg1 = true;
      } else {
        b_p++;
      }
    } else {
      b_p++;
    }
  }
  if (*p) {
    b_p = 0;
    exitg1 = false;
    while ((!exitg1) && (b_p <= loop_ub_tmp - 1)) {
      if ((endPtX_data[b_p] >= 1.0) && (endPtX_data[b_p] <= gridSize[0]) &&
          (endPtY_data[b_p] >= 1.0) && (endPtY_data[b_p] <= gridSize[1])) {
        y = (gridSize[1] + 1.0) - endPtY_data[b_p];
        if (map[static_cast<int>(y + (endPtX_data[b_p] - 1.0) *
                                         static_cast<double>(map.size(0))) -
                1]) {
          *p = false;
          collisionGridPts[0] = y;
          collisionGridPts[1] = endPtX_data[b_p];
          exitg1 = true;
        } else {
          b_p++;
        }
      } else {
        b_p++;
      }
    }
  }
  if (*p) {
    if (std::abs(x0 - x_tmp) <= 2.0 * eps(x0)) {
      if (std::abs(b_y0 - b_x_tmp) <= 2.0 * eps(b_y0)) {
        loop_ub_tmp = 4;
        endPtX_data[0] = x_tmp;
        endPtY_data[0] = b_x_tmp + 1.0;
        endPtX_data[1] = x_tmp + 1.0;
        endPtY_data[1] = b_x_tmp;
        endPtX_data[2] = x_tmp;
        endPtY_data[2] = b_x_tmp;
        endPtX_data[3] = x_tmp + 1.0;
        endPtY_data[3] = b_x_tmp + 1.0;
      } else {
        y = std::ceil(b_y0);
        if (std::abs(b_y0 - y) <= 2.0 * eps(b_y0)) {
          loop_ub_tmp = 4;
          endPtX_data[0] = x_tmp;
          endPtY_data[0] = y + 1.0;
          endPtX_data[1] = x_tmp + 1.0;
          endPtY_data[1] = y;
          endPtX_data[2] = x_tmp;
          endPtY_data[2] = y;
          endPtX_data[3] = x_tmp + 1.0;
          endPtY_data[3] = y + 1.0;
        } else {
          loop_ub_tmp = 1;
          endPtX_data[0] = x_tmp;
          endPtY_data[0] = std::floor(b_y0) + 1.0;
        }
      }
    } else {
      x = std::ceil(x0);
      if (std::abs(x0 - x) <= 2.0 * eps(x0)) {
        if (std::abs(b_y0 - std::floor(b_y0)) <= eps(b_y0)) {
          loop_ub_tmp = 4;
          endPtX_data[0] = x;
          endPtY_data[0] = b_x_tmp + 1.0;
          endPtX_data[1] = x + 1.0;
          endPtY_data[1] = b_x_tmp;
          endPtX_data[2] = x;
          endPtY_data[2] = b_x_tmp;
          endPtX_data[3] = x + 1.0;
          endPtY_data[3] = b_x_tmp + 1.0;
        } else if (std::abs(b_y0 - std::ceil(b_y0)) <= 2.0 * eps(b_y0)) {
          loop_ub_tmp = 4;
          y = std::ceil(b_y0);
          endPtX_data[0] = x;
          endPtY_data[0] = y + 1.0;
          endPtX_data[1] = x + 1.0;
          endPtY_data[1] = y;
          endPtX_data[2] = x;
          endPtY_data[2] = y;
          endPtX_data[3] = x + 1.0;
          endPtY_data[3] = y + 1.0;
        } else {
          loop_ub_tmp = 1;
          endPtX_data[0] = x;
          endPtY_data[0] = std::floor(b_y0) + 1.0;
        }
      } else if (std::abs(b_y0 - b_x_tmp) <= 2.0 * eps(b_y0)) {
        loop_ub_tmp = 1;
        endPtX_data[0] = std::floor(x0) + 1.0;
        endPtY_data[0] = b_x_tmp;
      } else {
        y = std::ceil(b_y0);
        if (std::abs(b_y0 - y) <= 2.0 * eps(b_y0)) {
          loop_ub_tmp = 1;
          endPtX_data[0] = std::floor(x0) + 1.0;
          endPtY_data[0] = y + 1.0;
        } else {
          loop_ub_tmp = 0;
        }
      }
    }
    b_p = 0;
    exitg1 = false;
    while ((!exitg1) && (b_p <= loop_ub_tmp - 1)) {
      if ((endPtX_data[b_p] >= 1.0) && (endPtX_data[b_p] <= gridSize[0]) &&
          (endPtY_data[b_p] >= 1.0) && (endPtY_data[b_p] <= gridSize[1])) {
        y = (gridSize[1] + 1.0) - endPtY_data[b_p];
        if (map[static_cast<int>(y + (endPtX_data[b_p] - 1.0) *
                                         static_cast<double>(map.size(0))) -
                1]) {
          *p = false;
          collisionGridPts[0] = y;
          collisionGridPts[1] = endPtX_data[b_p];
          exitg1 = true;
        } else {
          b_p++;
        }
      } else {
        b_p++;
      }
    }
  }
}

} // namespace internal
} // namespace algs
} // namespace nav
} // namespace coder

// End of code generation (raycast.cpp)
