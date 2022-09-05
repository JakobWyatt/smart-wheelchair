//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// RangeSensorBase.cpp
//
// Code generation for function 'RangeSensorBase'
//

// Include files
#include "RangeSensorBase.h"
#include "SharedMapProperties.h"
#include "binaryOccupancyMap.h"
#include "bsxfun.h"
#include "intersectLines.h"
#include "linePosition.h"
#include "raycast.h"
#include "rt_nonfinite.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
namespace nav {
namespace internal {
void RangeSensorBase::stepImpl_anonFcn1(
    const double angles[258], const ::coder::array<boolean_T, 2U> &grid,
    const binaryOccupancyMap *map, const double pose[3],
    double varargout_1[258])
{
  static const double dv[8]{
      0.0, 0.0, 0.0, 0.0, 1.0000000000000044, 0.0, 0.0, 1.0000000000000044};
  double collisionLoc[516];
  double x_data[258];
  double supportLines[8];
  double line[4];
  double a_data[2];
  double location[2];
  double pos[2];
  int ints_size[2];
  int point_size[2];
  int idx;
  int x_size;
  boolean_T isObstacleFree;
  location[0] = map->SharedProperties.LocalOriginInWorld[0] +
                map->SharedProperties.GridOriginInLocal[0];
  location[1] = map->SharedProperties.LocalOriginInWorld[1] +
                map->SharedProperties.GridOriginInLocal[1];
  std::copy(&dv[0], &dv[8], &supportLines[0]);
  for (int i{0}; i < 258; i++) {
    varargout_1[i] = rtNaN;
  }
  for (int i{0}; i < 258; i++) {
    double ji[2];
    double absxk;
    double scale;
    scale = angles[i] + pose[2];
    pos[0] = 15.0 * std::cos(scale);
    pos[1] = 15.0 * std::sin(scale);
    absxk = pose[0] + pos[0];
    pos[0] = absxk;
    collisionLoc[i] = absxk;
    absxk = pose[1] + pos[1];
    pos[1] = absxk;
    collisionLoc[i + 258] = absxk;
    algs::internal::raycast(*(double(*)[2]) & pose[0], pos, grid, location,
                            &isObstacleFree, ji);
    if (!isObstacleFree) {
      double line_data[8];
      double ints[4];
      double ints_data[4];
      double b_line_data[2];
      double point_data[2];
      double supportLines_tmp_tmp;
      int b_i;
      int bcoef;
      int ii_size;
      signed char ii_data[2];
      boolean_T invalidLine_data[2];
      boolean_T tmp_data[2];
      boolean_T exitg1;
      line[0] = pose[0];
      line[1] = pose[1];
      line[2] = pos[0] - pose[0];
      line[3] = absxk - pose[1];
      supportLines_tmp_tmp = ji[1] - (0.5 - location[0]);
      absxk = supportLines_tmp_tmp;
      collisionLoc[i] = supportLines_tmp_tmp;
      pos[0] = supportLines_tmp_tmp - pose[0];
      supportLines_tmp_tmp =
          ((map->SharedProperties.GridSize[0] + 1.0) - ji[0]) -
          (0.5 - location[1]);
      collisionLoc[i + 258] = supportLines_tmp_tmp;
      pos[1] = supportLines_tmp_tmp - pose[1];
      supportLines[0] = absxk - 0.50000000000000222;
      supportLines[3] = supportLines_tmp_tmp - 0.50000000000000222;
      if (pos[0] > 0.50000000000000222) {
        supportLines[1] = absxk - 0.50000000000000222;
      } else if (pos[0] > -0.50000000000000222) {
        scale = line[2];
        if (!std::isnan(line[2])) {
          if (line[2] < 0.0) {
            scale = -1.0;
          } else {
            scale = (line[2] > 0.0);
          }
        }
        if (scale < 0.0) {
          supportLines[1] = absxk - 0.50000000000000222;
        } else {
          supportLines[1] = absxk + 0.50000000000000222;
        }
      } else {
        supportLines[1] = absxk + 0.50000000000000222;
      }
      if (pos[1] > 0.50000000000000222) {
        supportLines[2] = supportLines_tmp_tmp - 0.50000000000000222;
      } else if (pos[1] > -0.50000000000000222) {
        scale = line[3];
        if (!std::isnan(line[3])) {
          if (line[3] < 0.0) {
            scale = -1.0;
          } else {
            scale = (line[3] > 0.0);
          }
        }
        if (scale < 0.0) {
          supportLines[2] = supportLines_tmp_tmp - 0.50000000000000222;
        } else {
          supportLines[2] = supportLines_tmp_tmp + 0.50000000000000222;
        }
      } else {
        supportLines[2] = supportLines_tmp_tmp + 0.50000000000000222;
      }
      algs::internal::impl::intersectLines(line, supportLines, ints);
      invalidLine_data[0] = !std::isinf(ints[0]);
      tmp_data[0] = !std::isnan(ints[0]);
      invalidLine_data[1] = !std::isinf(ints[1]);
      tmp_data[1] = !std::isnan(ints[1]);
      idx = 0;
      bcoef = 0;
      exitg1 = false;
      while ((!exitg1) && (bcoef < 2)) {
        if (invalidLine_data[bcoef] && tmp_data[bcoef]) {
          idx++;
          ii_data[idx - 1] = static_cast<signed char>(bcoef + 1);
          if (idx >= 2) {
            exitg1 = true;
          } else {
            bcoef++;
          }
        } else {
          bcoef++;
        }
      }
      if (idx < 1) {
        ii_size = 0;
      } else {
        ii_size = idx;
      }
      for (b_i = 0; b_i < 2; b_i++) {
        for (idx = 0; idx < ii_size; idx++) {
          line[idx + ii_size * b_i] = ints[(ii_data[idx] + (b_i << 1)) - 1];
        }
      }
      for (b_i = 0; b_i < 4; b_i++) {
        for (idx = 0; idx < ii_size; idx++) {
          line_data[idx + ii_size * b_i] =
              supportLines[(ii_data[idx] + (b_i << 1)) - 1];
        }
      }
      for (b_i = 0; b_i < ii_size; b_i++) {
        absxk = line_data[b_i + ii_size * 2];
        scale = line_data[b_i + ii_size * 3];
        ji[b_i] = absxk * absxk + scale * scale;
      }
      for (b_i = 0; b_i < ii_size; b_i++) {
        invalidLine_data[b_i] = (ji[b_i] < 2.2204460492503131E-16);
      }
      for (int c_i{0}; c_i < ii_size; c_i++) {
        if (ji[c_i] < 2.2204460492503131E-16) {
          ji[c_i] = 1.0;
        }
      }
      for (b_i = 0; b_i < ii_size; b_i++) {
        point_data[b_i] = line[b_i] - line_data[b_i];
      }
      for (b_i = 0; b_i < ii_size; b_i++) {
        b_line_data[b_i] = line_data[b_i + ii_size * 2];
      }
      bsxfun(point_data, ii_size, b_line_data, ii_size, a_data, &idx);
      for (b_i = 0; b_i < ii_size; b_i++) {
        point_data[b_i] = line[b_i + ii_size] - line_data[b_i + ii_size];
      }
      for (b_i = 0; b_i < ii_size; b_i++) {
        b_line_data[b_i] = line_data[b_i + ii_size * 3];
      }
      bsxfun(point_data, ii_size, b_line_data, ii_size, x_data, &x_size);
      if (idx == x_size) {
        for (b_i = 0; b_i < idx; b_i++) {
          a_data[b_i] += x_data[b_i];
        }
      } else {
        b_binary_expand_op(a_data, &idx, x_data, &x_size);
      }
      if (ii_size == 1) {
        x_size = static_cast<signed char>(idx);
      } else if (idx == 1) {
        x_size = static_cast<signed char>(ii_size);
      } else if (idx == ii_size) {
        x_size = static_cast<signed char>(idx);
      } else if (ii_size < idx) {
        x_size = static_cast<signed char>(ii_size);
      } else {
        x_size = static_cast<signed char>(idx);
      }
      if (x_size != 0) {
        idx = (idx != 1);
        bcoef = (ii_size != 1);
        b_i = x_size - 1;
        for (int c_i{0}; c_i <= b_i; c_i++) {
          x_data[c_i] = a_data[idx * c_i] / ji[bcoef * c_i];
        }
      }
      bcoef = ii_size - 1;
      ii_size = 0;
      for (int c_i{0}; c_i <= bcoef; c_i++) {
        if (invalidLine_data[c_i]) {
          ii_size++;
        }
      }
      if ((ii_size - 1 >= 0) && (x_size - 1 >= 0)) {
        std::memset(&x_data[0], 0, x_size * sizeof(double));
      }
      for (b_i = 0; b_i < x_size; b_i++) {
        absxk = x_data[b_i];
        invalidLine_data[b_i] = (absxk > -1.0E-14);
        tmp_data[b_i] = (absxk < 1.00000000000001);
      }
      bcoef = x_size - 1;
      ii_size = 0;
      for (int c_i{0}; c_i <= bcoef; c_i++) {
        if (invalidLine_data[c_i] && tmp_data[c_i]) {
          ii_size++;
        }
      }
      idx = 0;
      for (int c_i{0}; c_i <= bcoef; c_i++) {
        if (invalidLine_data[c_i] && tmp_data[c_i]) {
          ii_data[idx] = ii_data[c_i];
          idx++;
        }
      }
      ints_size[0] = ii_size;
      ints_size[1] = 2;
      point_size[0] = static_cast<signed char>(ii_size);
      point_size[1] = 2;
      for (int c_i{0}; c_i < 2; c_i++) {
        for (b_i = 0; b_i < ii_size; b_i++) {
          ints_data[b_i + ii_size * c_i] =
              ints[(ii_data[b_i] + (c_i << 1)) - 1];
        }
        idx = c_i * ii_size;
        for (bcoef = 0; bcoef < ii_size; bcoef++) {
          line[idx + bcoef] = pose[c_i];
        }
      }
      if (ii_size == static_cast<signed char>(ii_size)) {
        idx = ii_size * 2;
        point_size[0] = ii_size;
        for (b_i = 0; b_i < idx; b_i++) {
          scale = ints_data[b_i] - line[b_i];
          line[b_i] = scale * scale;
        }
      } else {
        binary_expand_op(line, point_size, ints_data, ints_size);
      }
      b_i = point_size[0];
      if (point_size[0] == 0) {
        x_size = 0;
      } else {
        x_size = point_size[0];
        std::copy(&line[0], &line[b_i], &x_data[0]);
        for (idx = 0; idx < b_i; idx++) {
          x_data[idx] += line[b_i + idx];
        }
      }
      for (int c_i{0}; c_i < x_size; c_i++) {
        x_data[c_i] = std::sqrt(x_data[c_i]);
      }
      if (x_size == 1) {
        varargout_1[i] = x_data[0];
        collisionLoc[i] = ints_data[0];
        collisionLoc[i + 258] = ints_data[ii_size];
      } else if (x_size > 1) {
        if ((x_data[0] > x_data[1]) ||
            (std::isnan(x_data[0]) && (!std::isnan(x_data[1])))) {
          idx = 1;
        } else {
          idx = 0;
        }
        varargout_1[i] = x_data[idx];
        collisionLoc[i] = ints_data[idx];
        collisionLoc[i + 258] = ints_data[idx + ii_size];
      } else {
        double t;
        double y;
        scale = 3.3121686421112381E-170;
        absxk = std::abs(collisionLoc[i] - pose[0]);
        if (absxk > 3.3121686421112381E-170) {
          y = 1.0;
          scale = absxk;
        } else {
          t = absxk / 3.3121686421112381E-170;
          y = t * t;
        }
        absxk = std::abs(supportLines_tmp_tmp - pose[1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        varargout_1[i] = scale * std::sqrt(y);
      }
    }
  }
}

} // namespace internal
} // namespace nav
} // namespace coder

// End of code generation (RangeSensorBase.cpp)
