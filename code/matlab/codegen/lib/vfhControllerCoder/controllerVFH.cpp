//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// controllerVFH.cpp
//
// Code generation for function 'controllerVFH'
//

// Include files
#include "controllerVFH.h"
#include "VectorFieldHistogramBase.h"
#include "angdiff.h"
#include "cross.h"
#include "eml_mtimes_helper.h"
#include "lidarScan.h"
#include "minOrMax.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include "vfhControllerCoder_internal_types.h"
#include "wrapToPi.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static void b_binary_expand_op(double in1_data[], int in1_size[2],
                               const double in2_data[], const int in2_size[2],
                               const double in3_data[], const int in3_size[2]);

// Function Definitions
namespace coder {
void controllerVFH::buildPolarObstacleDensity(const lidarScan *scan)
{
  lidarScan validScan;
  double higherVec_data[774];
  double kh_data[774];
  double lh_data[774];
  double lk_data[774];
  double lowerVec_data[774];
  double higherAng_data[258];
  double sinOfEnlargement_data[258];
  double varargin_1_data[258];
  double varargin_2_data[258];
  double weightedRanges_data[258];
  double obj[2];
  double constA;
  int kalphaVec_size[2];
  int kh_size[2];
  int lowerVec_size[2];
  int high_i;
  int ibmat;
  int lk_size;
  int mid_i;
  int ntilerows;
  obj[0] = DistanceLimits[0];
  obj[1] = DistanceLimits[1];
  scan->removeInvalidData(obj, &validScan);
  constA = DistanceLimits[1];
  mid_i = validScan.InternalRanges.size[0];
  for (lk_size = 0; lk_size < mid_i; lk_size++) {
    weightedRanges_data[lk_size] =
        constA - validScan.InternalRanges.data[lk_size];
  }
  constA = RobotRadius + SafetyDistance;
  if (constA == 0.0) {
    ntilerows = validScan.InternalAngles.size[0];
    mid_i = validScan.InternalAngles.size[0];
    if (mid_i - 1 >= 0) {
      std::memset(&sinOfEnlargement_data[0], 0, mid_i * sizeof(double));
    }
    lk_size = validScan.InternalAngles.size[0];
    for (int k{0}; k < lk_size; k++) {
      ibmat = 0;
      constA = validScan.InternalAngles.data[k];
      if (!std::isnan(constA)) {
        if ((constA >= AngularSectorMidPoints[0]) &&
            (constA < AngularSectorMidPoints[179])) {
          int low_ip1;
          ibmat = 1;
          low_ip1 = 2;
          high_i = 180;
          while (high_i > low_ip1) {
            mid_i = (ibmat + high_i) >> 1;
            if (validScan.InternalAngles.data[k] >=
                AngularSectorMidPoints[mid_i - 1]) {
              ibmat = mid_i;
              low_ip1 = mid_i + 1;
            } else {
              high_i = mid_i;
            }
          }
        }
        if (validScan.InternalAngles.data[k] == AngularSectorMidPoints[179]) {
          ibmat = 180;
        }
      }
      sinOfEnlargement_data[k] = ibmat;
    }
    std::memset(&PolarObstacleDensity[0], 0, 180U * sizeof(double));
    for (int i{0}; i < ntilerows; i++) {
      lk_size = static_cast<int>(sinOfEnlargement_data[i]) - 1;
      PolarObstacleDensity[lk_size] += weightedRanges_data[i];
    }
  } else {
    double kalpha[540];
    double validWeights[180];
    int lh_size[2];
    boolean_T validWeights_data[46440];
    ntilerows = validScan.InternalRanges.size[0];
    mid_i = validScan.InternalRanges.size[0];
    for (lk_size = 0; lk_size < mid_i; lk_size++) {
      sinOfEnlargement_data[lk_size] =
          constA / validScan.InternalRanges.data[lk_size];
    }
    for (int i{0}; i < ntilerows; i++) {
      if (sinOfEnlargement_data[i] >= 1.0) {
        sinOfEnlargement_data[i] = 0.99999999999999978;
      }
    }
    for (int k{0}; k < ntilerows; k++) {
      sinOfEnlargement_data[k] = std::asin(sinOfEnlargement_data[k]);
    }
    if (validScan.InternalAngles.size[0] == validScan.InternalRanges.size[0]) {
      ibmat = validScan.InternalAngles.size[0];
      mid_i = validScan.InternalAngles.size[0];
      for (lk_size = 0; lk_size < mid_i; lk_size++) {
        higherAng_data[lk_size] = validScan.InternalAngles.data[lk_size] +
                                  sinOfEnlargement_data[lk_size];
      }
    } else {
      binary_expand_op(higherAng_data, &ibmat, &validScan,
                       sinOfEnlargement_data,
                       &validScan.InternalRanges.size[0]);
    }
    if (validScan.InternalAngles.size[0] == validScan.InternalRanges.size[0]) {
      ntilerows = validScan.InternalAngles.size[0];
      mid_i = validScan.InternalAngles.size[0];
      for (lk_size = 0; lk_size < mid_i; lk_size++) {
        sinOfEnlargement_data[lk_size] =
            validScan.InternalAngles.data[lk_size] -
            sinOfEnlargement_data[lk_size];
      }
    } else {
      e_binary_expand_op(sinOfEnlargement_data, &ntilerows, &validScan);
    }
    if (ntilerows - 1 >= 0) {
      std::copy(&sinOfEnlargement_data[0], &sinOfEnlargement_data[ntilerows],
                &varargin_1_data[0]);
    }
    for (int k{0}; k < ntilerows; k++) {
      varargin_1_data[k] = std::cos(varargin_1_data[k]);
    }
    if (ntilerows - 1 >= 0) {
      std::copy(&sinOfEnlargement_data[0], &sinOfEnlargement_data[ntilerows],
                &varargin_2_data[0]);
    }
    for (int k{0}; k < ntilerows; k++) {
      varargin_2_data[k] = std::sin(varargin_2_data[k]);
    }
    lowerVec_size[0] = ntilerows;
    lowerVec_size[1] = 3;
    if (ntilerows - 1 >= 0) {
      std::copy(&varargin_1_data[0], &varargin_1_data[ntilerows],
                &lowerVec_data[0]);
    }
    for (lk_size = 0; lk_size < ntilerows; lk_size++) {
      lowerVec_data[lk_size + ntilerows] = varargin_2_data[lk_size];
    }
    if (ntilerows - 1 >= 0) {
      std::memset(&lowerVec_data[ntilerows * 2], 0,
                  ((ntilerows + ntilerows * 2) - ntilerows * 2) *
                      sizeof(double));
    }
    if (ibmat - 1 >= 0) {
      std::copy(&higherAng_data[0], &higherAng_data[ibmat],
                &varargin_1_data[0]);
    }
    for (int k{0}; k < ibmat; k++) {
      varargin_1_data[k] = std::cos(varargin_1_data[k]);
    }
    if (ibmat - 1 >= 0) {
      std::copy(&higherAng_data[0], &higherAng_data[ibmat],
                &varargin_2_data[0]);
    }
    for (int k{0}; k < ibmat; k++) {
      varargin_2_data[k] = std::sin(varargin_2_data[k]);
    }
    if (ibmat - 1 >= 0) {
      std::copy(&varargin_1_data[0], &varargin_1_data[ibmat],
                &higherVec_data[0]);
    }
    for (lk_size = 0; lk_size < ibmat; lk_size++) {
      higherVec_data[lk_size + ibmat] = varargin_2_data[lk_size];
    }
    if (ibmat - 1 >= 0) {
      std::memset(&higherVec_data[ibmat * 2], 0,
                  ((ibmat + ibmat * 2) - ibmat * 2) * sizeof(double));
    }
    mid_i = 180 * ntilerows;
    for (lk_size = 0; lk_size < mid_i; lk_size++) {
      validWeights_data[lk_size] = true;
    }
    cross(lowerVec_data, lowerVec_size, higherVec_data, lh_data, lh_size);
    for (int k{0}; k < 180; k++) {
      PolarObstacleDensity[k] = AngularSectorMidPoints[k];
      PolarObstacleDensity[k] = std::cos(PolarObstacleDensity[k]);
      kalpha[k] = PolarObstacleDensity[k];
      kalpha[k + 180] = std::sin(AngularSectorMidPoints[k]);
      kalpha[k + 360] = 0.0;
    }
    mid_i = lh_size[0];
    kalphaVec_size[0] = ntilerows;
    kalphaVec_size[1] = 3;
    for (int i{0}; i < 180; i++) {
      double kalphaVec_data[774];
      int b_lk_size[2];
      int low_ip1;
      for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
        ibmat = low_ip1 * ntilerows;
        for (high_i = 0; high_i < ntilerows; high_i++) {
          kalphaVec_data[ibmat + high_i] = kalpha[i + 180 * low_ip1];
        }
      }
      cross(lowerVec_data, lowerVec_size, kalphaVec_data, lk_data, b_lk_size);
      cross(kalphaVec_data, kalphaVec_size, higherVec_data, kh_data, kh_size);
      low_ip1 = b_lk_size[0];
      high_i = b_lk_size[0];
      for (int k{0}; k < low_ip1; k++) {
        constA = lk_data[k + b_lk_size[0] * 2];
        if (!std::isnan(constA)) {
          if (constA < 0.0) {
            constA = -1.0;
          } else {
            constA = (constA > 0.0);
          }
        }
        varargin_1_data[k] = constA;
      }
      ibmat = kh_size[0];
      for (int k{0}; k < ibmat; k++) {
        constA = kh_data[k + kh_size[0] * 2];
        if (!std::isnan(constA)) {
          if (constA < 0.0) {
            constA = -1.0;
          } else {
            constA = (constA > 0.0);
          }
        }
        sinOfEnlargement_data[k] = constA;
      }
      for (int k{0}; k < mid_i; k++) {
        constA = lh_data[k + lh_size[0] * 2];
        if (!std::isnan(constA)) {
          if (constA < 0.0) {
            constA = -1.0;
          } else {
            constA = (constA > 0.0);
          }
        }
        higherAng_data[k] = constA;
      }
      if (b_lk_size[0] == 1) {
        lk_size = kh_size[0];
      } else {
        lk_size = b_lk_size[0];
      }
      if ((b_lk_size[0] == kh_size[0]) && (lk_size == mid_i)) {
        for (lk_size = 0; lk_size < low_ip1; lk_size++) {
          varargin_1_data[lk_size] =
              (varargin_1_data[lk_size] + sinOfEnlargement_data[lk_size]) +
              higherAng_data[lk_size];
        }
      } else {
        binary_expand_op(varargin_1_data, &high_i, sinOfEnlargement_data,
                         &kh_size[0], higherAng_data, &mid_i);
      }
      for (int k{0}; k < high_i; k++) {
        sinOfEnlargement_data[k] = std::abs(varargin_1_data[k]);
      }
      for (lk_size = 0; lk_size < ntilerows; lk_size++) {
        validWeights_data[i + 180 * lk_size] =
            (sinOfEnlargement_data[lk_size] > 1.0);
      }
    }
    for (lk_size = 0; lk_size < 180; lk_size++) {
      validWeights[lk_size] = 0.0;
      for (ibmat = 0; ibmat < ntilerows; ibmat++) {
        validWeights[lk_size] +=
            static_cast<double>(validWeights_data[lk_size + 180 * ibmat]) *
            weightedRanges_data[ibmat];
      }
      PolarObstacleDensity[lk_size] = validWeights[lk_size];
    }
  }
}

void controllerVFH::computeCost(const double c_data[], const int c_size[2],
                                double prevDir, double cost_data[],
                                int cost_size[2]) const
{
  double b_b_data[273];
  double b_data[273];
  double delta_data[273];
  double b;
  double cdWeight;
  double pdWeight;
  double tdWeight;
  int b_b_size[2];
  int b_size[2];
  int delta_size[2];
  int nx;
  tdWeight = TargetDirectionWeight;
  cdWeight = CurrentDirectionWeight;
  pdWeight = PreviousDirectionWeight;
  b = (tdWeight + cdWeight) + pdWeight;
  delta_size[0] = 1;
  delta_size[1] = c_size[1];
  nx = c_size[1];
  for (int k{0}; k < nx; k++) {
    delta_data[k] = -1.5707963267948966 - c_data[k];
  }
  robotics::internal::b_wrapToPi(delta_data, delta_size);
  nx = delta_size[1];
  cost_size[0] = 1;
  cost_size[1] = delta_size[1];
  for (int k{0}; k < nx; k++) {
    cost_data[k] = std::abs(delta_data[k]);
  }
  delta_size[0] = 1;
  delta_size[1] = c_size[1];
  nx = c_size[1];
  for (int k{0}; k < nx; k++) {
    delta_data[k] = 0.0 - c_data[k];
  }
  robotics::internal::b_wrapToPi(delta_data, delta_size);
  nx = delta_size[1];
  b_size[0] = 1;
  b_size[1] = delta_size[1];
  for (int k{0}; k < nx; k++) {
    b_data[k] = std::abs(delta_data[k]);
  }
  delta_size[0] = 1;
  delta_size[1] = c_size[1];
  nx = c_size[1];
  for (int k{0}; k < nx; k++) {
    delta_data[k] = prevDir - c_data[k];
  }
  robotics::internal::b_wrapToPi(delta_data, delta_size);
  nx = delta_size[1];
  b_b_size[0] = 1;
  b_b_size[1] = delta_size[1];
  for (int k{0}; k < nx; k++) {
    b_b_data[k] = std::abs(delta_data[k]);
  }
  if (cost_size[1] == 1) {
    nx = b_size[1];
  } else {
    nx = cost_size[1];
  }
  if ((cost_size[1] == b_size[1]) && (nx == delta_size[1])) {
    nx = cost_size[1] - 1;
    cost_size[0] = 1;
    for (int k{0}; k <= nx; k++) {
      cost_data[k] = ((tdWeight * cost_data[k] + cdWeight * b_data[k]) +
                      pdWeight * b_b_data[k]) /
                     3.0 * b;
    }
  } else {
    binary_expand_op(cost_data, cost_size, tdWeight, cdWeight, b_data, b_size,
                     pdWeight, b_b_data, b_b_size, b);
  }
}

double controllerVFH::selectHeadingDirection()
{
  array<double, 2U> c;
  array<double, 2U> candToSectDiff;
  double b_data[273];
  double candidateDirections_data[273];
  double candidateDirs_data[273];
  double angles_data[180];
  double nonNarrowDirs_data[180];
  double sectorSizes_data[90];
  double theta2_data[90];
  double thetaSteer;
  int candidateDirections_size[2];
  int candidateDirs_size[2];
  int nonNarrowDirs_size[2];
  int sectorSizes_size[2];
  int theta2_size[2];
  int tmp_size[2];
  int i;
  int m;
  int tmp2;
  int work;
  short d_tmp_data[273];
  signed char x[182];
  signed char changes[181];
  unsigned char foundSectors_data[181];
  unsigned char c_tmp_data[180];
  unsigned char sectors_data[180];
  signed char b_tmp_data[90];
  signed char tmp_data[90];
  boolean_T exitg1;
  boolean_T y;
  x[0] = 0;
  for (i = 0; i < 180; i++) {
    x[i + 1] = static_cast<signed char>(!MaskedHistogram[i]);
  }
  x[181] = 0;
  work = x[0];
  for (m = 0; m < 181; m++) {
    tmp2 = work;
    work = x[m + 1];
    changes[m] = static_cast<signed char>(work - tmp2);
  }
  y = false;
  tmp2 = 0;
  exitg1 = false;
  while ((!exitg1) && (tmp2 < 181)) {
    if (changes[tmp2] != 0) {
      y = true;
      exitg1 = true;
    } else {
      tmp2++;
    }
  }
  if (!y) {
    thetaSteer = rtNaN;
    PreviousDirection = rtNaN;
  } else {
    double cVal;
    int loop_ub;
    int trueCount;
    signed char iv[2];
    signed char sz[2];
    boolean_T nearIdx_data[49140];
    boolean_T freeDirs_data[273];
    boolean_T narrowIdx_data[90];
    work = 0;
    tmp2 = 0;
    exitg1 = false;
    while ((!exitg1) && (tmp2 < 181)) {
      if (changes[tmp2] != 0) {
        work++;
        foundSectors_data[work - 1] = static_cast<unsigned char>(tmp2 + 1);
        if (work >= 181) {
          exitg1 = true;
        } else {
          tmp2++;
        }
      } else {
        tmp2++;
      }
    }
    if (work < 1) {
      work = 0;
    }
    sz[1] = static_cast<signed char>(work / 2);
    m = sz[1];
    tmp2 = sz[1] << 1;
    if (tmp2 - 1 >= 0) {
      std::copy(&foundSectors_data[0], &foundSectors_data[tmp2],
                &sectors_data[0]);
    }
    if (sz[1] < 1) {
      loop_ub = 0;
    } else {
      loop_ub = sz[1];
    }
    if (loop_ub == sz[1]) {
      for (i = 0; i < loop_ub; i++) {
        work = 2 * i + 1;
        sectors_data[work] =
            static_cast<unsigned char>(foundSectors_data[work] - 1U);
      }
    } else {
      binary_expand_op(sectors_data, foundSectors_data, sz, loop_ub - 1);
    }
    if (tmp2 - 1 >= 0) {
      std::memset(&angles_data[0], 0, tmp2 * sizeof(double));
    }
    if (sz[1] < 1) {
      loop_ub = 0;
    } else {
      loop_ub = sz[1];
    }
    for (i = 0; i < loop_ub; i++) {
      angles_data[2 * i] = AngularSectorMidPoints[sectors_data[2 * i] - 1];
    }
    if (sz[1] < 1) {
      loop_ub = 0;
    } else {
      loop_ub = sz[1];
    }
    for (i = 0; i < loop_ub; i++) {
      work = 2 * i + 1;
      angles_data[work] = AngularSectorMidPoints[sectors_data[work] - 1];
    }
    if (m != 0) {
      for (tmp2 = 0; tmp2 < m; tmp2++) {
        work = tmp2 << 1;
        sectorSizes_data[tmp2] = sectors_data[work + 1] - sectors_data[work];
      }
    }
    loop_ub = m - 1;
    for (i = 0; i <= loop_ub; i++) {
      sectorSizes_data[i] *= AngularDifference;
    }
    cVal = NarrowOpeningThreshold;
    for (i = 0; i < m; i++) {
      narrowIdx_data[i] = (sectorSizes_data[i] < cVal);
    }
    m--;
    trueCount = 0;
    loop_ub = 0;
    for (i = 0; i <= m; i++) {
      if (narrowIdx_data[i]) {
        trueCount++;
        tmp_data[loop_ub] = static_cast<signed char>(i + 1);
        loop_ub++;
      }
    }
    for (i = 0; i < trueCount; i++) {
      sectorSizes_data[i] = angles_data[2 * (tmp_data[i] - 1)];
    }
    for (i = 0; i < trueCount; i++) {
      theta2_data[i] = angles_data[2 * (tmp_data[i] - 1) + 1];
    }
    candidateDirs_size[0] = 1;
    candidateDirs_size[1] = trueCount;
    if (trueCount - 1 >= 0) {
      std::copy(&sectorSizes_data[0], &sectorSizes_data[trueCount],
                &candidateDirs_data[0]);
    }
    robotics::internal::b_wrapToPi(candidateDirs_data, candidateDirs_size);
    sectorSizes_size[0] = 1;
    sectorSizes_size[1] = candidateDirs_size[1];
    loop_ub = candidateDirs_size[1];
    if (loop_ub - 1 >= 0) {
      std::copy(&candidateDirs_data[0], &candidateDirs_data[loop_ub],
                &sectorSizes_data[0]);
    }
    candidateDirs_size[0] = 1;
    candidateDirs_size[1] = trueCount;
    if (trueCount - 1 >= 0) {
      std::copy(&theta2_data[0], &theta2_data[trueCount],
                &candidateDirs_data[0]);
    }
    robotics::internal::b_wrapToPi(candidateDirs_data, candidateDirs_size);
    theta2_size[0] = 1;
    theta2_size[1] = candidateDirs_size[1];
    loop_ub = candidateDirs_size[1];
    if (loop_ub - 1 >= 0) {
      std::copy(&candidateDirs_data[0], &candidateDirs_data[loop_ub],
                &theta2_data[0]);
    }
    if (sectorSizes_size[1] == 1) {
      loop_ub = candidateDirs_size[1];
    } else {
      loop_ub = sectorSizes_size[1];
    }
    if ((sectorSizes_size[1] == candidateDirs_size[1]) &&
        (sectorSizes_size[1] == loop_ub)) {
      candidateDirs_size[0] = 1;
      candidateDirs_size[1] = sectorSizes_size[1];
      loop_ub = sectorSizes_size[1];
      for (i = 0; i < loop_ub; i++) {
        double d;
        d = sectorSizes_data[i];
        candidateDirs_data[i] = d - (d - theta2_data[i]) / 2.0;
      }
    } else {
      b_binary_expand_op(candidateDirs_data, candidateDirs_size,
                         sectorSizes_data, sectorSizes_size, theta2_data,
                         theta2_size);
    }
    robotics::internal::b_wrapToPi(candidateDirs_data, candidateDirs_size);
    loop_ub = candidateDirs_size[1];
    if (loop_ub - 1 >= 0) {
      std::copy(&candidateDirs_data[0], &candidateDirs_data[loop_ub],
                &sectorSizes_data[0]);
    }
    trueCount = 0;
    for (i = 0; i <= m; i++) {
      if (!narrowIdx_data[i]) {
        trueCount++;
      }
    }
    sz[0] = 1;
    sz[1] = static_cast<signed char>(trueCount);
    work = 0;
    for (i = 0; i <= m; i++) {
      if (!narrowIdx_data[i]) {
        work++;
      }
    }
    iv[0] = 1;
    iv[1] = static_cast<signed char>(work);
    tmp2 = 0;
    tmp_size[0] = 1;
    loop_ub = 0;
    for (i = 0; i <= m; i++) {
      if (!narrowIdx_data[i]) {
        tmp2++;
        b_tmp_data[loop_ub] = static_cast<signed char>(i + 1);
        loop_ub++;
      }
    }
    tmp_size[1] = tmp2;
    if ((tmp2 == static_cast<signed char>(trueCount)) &&
        (tmp2 == static_cast<signed char>(work))) {
      nonNarrowDirs_size[1] = tmp2 + tmp2;
      for (i = 0; i < tmp2; i++) {
        nonNarrowDirs_data[i] =
            angles_data[2 * (b_tmp_data[i] - 1)] + cVal / 2.0;
      }
      for (i = 0; i < tmp2; i++) {
        nonNarrowDirs_data[i + tmp2] =
            angles_data[2 * (b_tmp_data[i] - 1) + 1] - cVal / 2.0;
      }
    } else {
      binary_expand_op(nonNarrowDirs_data, nonNarrowDirs_size, angles_data,
                       b_tmp_data, tmp_size, sz, cVal, iv, cVal);
    }
    if (std::isnan(PreviousDirection)) {
      PreviousDirection = 0.0;
    }
    loop_ub = nonNarrowDirs_size[1];
    work = candidateDirs_size[1];
    tmp2 = nonNarrowDirs_size[1] + candidateDirs_size[1];
    candidateDirs_size[1] = tmp2 + 3;
    if (loop_ub - 1 >= 0) {
      std::copy(&nonNarrowDirs_data[0], &nonNarrowDirs_data[loop_ub],
                &candidateDirs_data[0]);
    }
    for (i = 0; i < work; i++) {
      candidateDirs_data[i + loop_ub] = sectorSizes_data[i];
    }
    candidateDirs_data[tmp2] = -1.5707963267948966;
    candidateDirs_data[tmp2 + 1] = 0.0;
    candidateDirs_data[tmp2 + 2] = PreviousDirection;
    loop_ub = tmp2 + 3;
    std::copy(&candidateDirs_data[0], &candidateDirs_data[loop_ub], &b_data[0]);
    c.set_size(candidateDirs_size[1], 180);
    for (tmp2 = 0; tmp2 < 180; tmp2++) {
      i = c.size(0) - 1;
      for (work = 0; work <= i; work++) {
        c[work + c.size(0) * tmp2] = robotics::internal::angdiff(
            AngularSectorMidPoints[tmp2], b_data[work]);
      }
    }
    work = c.size(0) * 180;
    candToSectDiff.set_size(c.size(0), 180);
    for (tmp2 = 0; tmp2 < work; tmp2++) {
      candToSectDiff[tmp2] = std::abs(c[tmp2]);
    }
    internal::minimum(candToSectDiff, b_data, &work);
    if (candToSectDiff.size(0) == work) {
      loop_ub = static_cast<short>(candToSectDiff.size(0));
    } else if (work < candToSectDiff.size(0)) {
      loop_ub = static_cast<short>(work);
    } else {
      loop_ub = static_cast<short>(candToSectDiff.size(0));
    }
    c.set_size(loop_ub, 180);
    for (tmp2 = 0; tmp2 < 180; tmp2++) {
      i = c.size(0) - 1;
      for (work = 0; work <= i; work++) {
        c[work + c.size(0) * tmp2] =
            candToSectDiff[work + candToSectDiff.size(0) * tmp2] - b_data[work];
      }
    }
    tmp2 = c.size(0);
    loop_ub = c.size(0) * 180;
    for (i = 0; i < loop_ub; i++) {
      nearIdx_data[i] = (c[i] < 1.4901161193847656E-8);
    }
    for (i = 0; i < tmp2; i++) {
      freeDirs_data[i] = true;
    }
    for (i = 0; i < tmp2; i++) {
      trueCount = 0;
      loop_ub = 0;
      for (work = 0; work < 180; work++) {
        if (nearIdx_data[i + tmp2 * work]) {
          trueCount++;
          c_tmp_data[loop_ub] = static_cast<unsigned char>(work + 1);
          loop_ub++;
        }
      }
      y = false;
      work = 1;
      exitg1 = false;
      while ((!exitg1) && (work <= trueCount)) {
        if (MaskedHistogram[c_tmp_data[work - 1] - 1]) {
          y = true;
          exitg1 = true;
        } else {
          work++;
        }
      }
      freeDirs_data[i] = !y;
    }
    work = tmp2 - 1;
    trueCount = 0;
    candidateDirections_size[0] = 1;
    loop_ub = 0;
    for (i = 0; i <= work; i++) {
      if (freeDirs_data[i]) {
        trueCount++;
        candidateDirections_data[loop_ub] = candidateDirs_data[i];
        loop_ub++;
      }
    }
    candidateDirections_size[1] = trueCount;
    computeCost(candidateDirections_data, candidateDirections_size,
                PreviousDirection, candidateDirs_data, candidateDirs_size);
    cVal = internal::minimum(candidateDirs_data, candidateDirs_size);
    tmp2 = candidateDirs_size[1] - 1;
    for (i = 0; i <= tmp2; i++) {
      candidateDirs_data[i] -= cVal;
    }
    trueCount = 0;
    loop_ub = 0;
    for (i = 0; i <= tmp2; i++) {
      if (candidateDirs_data[i] < 1.4901161193847656E-8) {
        trueCount++;
        d_tmp_data[loop_ub] = static_cast<short>(i + 1);
        loop_ub++;
      }
    }
    candidateDirs_size[0] = 1;
    candidateDirs_size[1] = trueCount;
    for (i = 0; i < trueCount; i++) {
      candidateDirs_data[i] = candidateDirections_data[d_tmp_data[i] - 1];
    }
    thetaSteer = internal::minimum(candidateDirs_data, candidateDirs_size);
    PreviousDirection = thetaSteer;
  }
  return thetaSteer;
}

} // namespace coder
static void b_binary_expand_op(double in1_data[], int in1_size[2],
                               const double in2_data[], const int in2_size[2],
                               const double in3_data[], const int in3_size[2])
{
  int b_in3_size;
  int stride_0_1;
  int stride_1_1;
  int stride_2_1;
  in1_size[0] = 1;
  if (in3_size[1] == 1) {
    b_in3_size = in2_size[1];
  } else {
    b_in3_size = in3_size[1];
  }
  if (b_in3_size == 1) {
    in1_size[1] = in2_size[1];
  } else if (in3_size[1] == 1) {
    in1_size[1] = in2_size[1];
  } else {
    in1_size[1] = in3_size[1];
  }
  stride_0_1 = (in2_size[1] != 1);
  stride_1_1 = (in2_size[1] != 1);
  stride_2_1 = (in3_size[1] != 1);
  if (in3_size[1] == 1) {
    b_in3_size = in2_size[1];
  } else {
    b_in3_size = in3_size[1];
  }
  if (b_in3_size == 1) {
    b_in3_size = in2_size[1];
  } else if (in3_size[1] == 1) {
    b_in3_size = in2_size[1];
  } else {
    b_in3_size = in3_size[1];
  }
  for (int i{0}; i < b_in3_size; i++) {
    in1_data[i] = in2_data[i * stride_0_1] -
                  (in2_data[i * stride_1_1] - in3_data[i * stride_2_1]) / 2.0;
  }
}

namespace coder {
double controllerVFH::step(const lidarScan *varargin_1)
{
  lidarScan validScan;
  double DYj_data[258];
  double a_tmp_data[258];
  double c_tmp_data[258];
  double x_data[258];
  double d2scaled;
  double delta1;
  double delta2;
  int DYj_size;
  int idx;
  int k;
  int nx;
  int trueCount;
  short ii_data;
  unsigned char b_tmp_data[180];
  unsigned char tmp_data[180];
  boolean_T blockedL_data[258];
  boolean_T blockedR_data[258];
  boolean_T b;
  boolean_T exitg1;
  if (isInitialized != 1) {
    isInitialized = 1;
    PreviousDirection = 0.0;
    d2scaled = AngularLimits[0] + 0.017453292519943295;
    AngularSectorMidPoints[179] = AngularLimits[1] - 0.017453292519943295;
    AngularSectorMidPoints[0] = AngularLimits[0] + 0.017453292519943295;
    if (AngularLimits[0] + 0.017453292519943295 ==
        -(AngularLimits[1] - 0.017453292519943295)) {
      d2scaled = (AngularLimits[1] - 0.017453292519943295) / 179.0;
      for (k = 0; k < 178; k++) {
        AngularSectorMidPoints[k + 1] =
            (2.0 * (static_cast<double>(k) + 2.0) - 181.0) * d2scaled;
      }
    } else if (((AngularLimits[0] + 0.017453292519943295 < 0.0) !=
                (AngularLimits[1] - 0.017453292519943295 < 0.0)) &&
               ((std::abs(AngularLimits[0] + 0.017453292519943295) >
                 8.9884656743115785E+307) ||
                (std::abs(AngularLimits[1] - 0.017453292519943295) >
                 8.9884656743115785E+307))) {
      delta1 = (AngularLimits[0] + 0.017453292519943295) / 179.0;
      delta2 = (AngularLimits[1] - 0.017453292519943295) / 179.0;
      for (k = 0; k < 178; k++) {
        AngularSectorMidPoints[k + 1] =
            (d2scaled + delta2 * (static_cast<double>(k) + 1.0)) -
            delta1 * (static_cast<double>(k) + 1.0);
      }
    } else {
      delta1 = ((AngularLimits[1] - 0.017453292519943295) -
                (AngularLimits[0] + 0.017453292519943295)) /
               179.0;
      for (k = 0; k < 178; k++) {
        AngularSectorMidPoints[k + 1] =
            d2scaled + (static_cast<double>(k) + 1.0) * delta1;
      }
    }
    d2scaled = AngularSectorMidPoints[1] - AngularSectorMidPoints[0];
    if (std::abs(d2scaled) > 3.1415926535897931) {
      delta1 = internal::scalar::b_mod(d2scaled + 3.1415926535897931);
      if ((delta1 == 0.0) && (d2scaled + 3.1415926535897931 > 0.0)) {
        delta1 = 6.2831853071795862;
      }
      d2scaled = delta1 - 3.1415926535897931;
    }
    AngularDifference = std::abs(d2scaled);
    d2scaled = AngularDifference / 2.0;
    for (int i{0}; i < 180; i++) {
      AngularSectorStartPoints[i] = AngularSectorMidPoints[i] - d2scaled;
      BinaryHistogram[i] = false;
      BinaryHistogram[i] = false;
    }
    PreviousDirection *= 0.0;
  }
  buildPolarObstacleDensity(varargin_1);
  d2scaled = HistogramThresholds[1];
  trueCount = 0;
  nx = 0;
  for (idx = 0; idx < 180; idx++) {
    b = (PolarObstacleDensity[idx] > d2scaled);
    if (b) {
      trueCount++;
      tmp_data[nx] = static_cast<unsigned char>(idx + 1);
      nx++;
    }
  }
  for (int i{0}; i < trueCount; i++) {
    BinaryHistogram[tmp_data[i] - 1] = true;
  }
  d2scaled = HistogramThresholds[0];
  trueCount = 0;
  nx = 0;
  for (idx = 0; idx < 180; idx++) {
    b = (PolarObstacleDensity[idx] < d2scaled);
    if (b) {
      trueCount++;
      b_tmp_data[nx] = static_cast<unsigned char>(idx + 1);
      nx++;
    }
  }
  for (int i{0}; i < trueCount; i++) {
    BinaryHistogram[b_tmp_data[i] - 1] = false;
  }
  double obj[2];
  d2scaled = -MinTurningRadius;
  delta2 = MinTurningRadius;
  obj[0] = DistanceLimits[0];
  obj[1] = DistanceLimits[1];
  varargin_1->removeInvalidData(obj, &validScan);
  idx = validScan.InternalAngles.size[0];
  nx = validScan.InternalAngles.size[0];
  if (nx - 1 >= 0) {
    std::copy(&validScan.InternalAngles.data[0],
              &validScan.InternalAngles.data[nx], &a_tmp_data[0]);
  }
  nx = validScan.InternalAngles.size[0];
  for (k = 0; k < nx; k++) {
    a_tmp_data[k] = std::cos(a_tmp_data[k]);
  }
  DYj_size = validScan.InternalAngles.size[0];
  nx = validScan.InternalAngles.size[0];
  if (nx - 1 >= 0) {
    std::copy(&validScan.InternalAngles.data[0],
              &validScan.InternalAngles.data[nx], &DYj_data[0]);
  }
  nx = validScan.InternalAngles.size[0];
  for (k = 0; k < nx; k++) {
    DYj_data[k] = std::sin(DYj_data[k]);
  }
  if (validScan.InternalRanges.size[0] == validScan.InternalAngles.size[0]) {
    DYj_size = validScan.InternalRanges.size[0];
    nx = validScan.InternalRanges.size[0];
    for (int i{0}; i < nx; i++) {
      DYj_data[i] *= validScan.InternalRanges.data[i];
    }
  } else {
    b_binary_expand_op(DYj_data, &DYj_size, &validScan);
  }
  if (validScan.InternalRanges.size[0] == validScan.InternalAngles.size[0]) {
    idx = validScan.InternalRanges.size[0];
    nx = validScan.InternalRanges.size[0];
    for (int i{0}; i < nx; i++) {
      a_tmp_data[i] = 0.0 - validScan.InternalRanges.data[i] * a_tmp_data[i];
    }
  } else {
    binary_expand_op(a_tmp_data, &idx, &validScan);
  }
  trueCount = idx;
  for (int i{0}; i < idx; i++) {
    delta1 = a_tmp_data[i];
    x_data[i] = delta1 * delta1;
  }
  for (int i{0}; i < DYj_size; i++) {
    delta1 = d2scaled - DYj_data[i];
    c_tmp_data[i] = delta1 * delta1;
  }
  if (idx == DYj_size) {
    for (int i{0}; i < idx; i++) {
      x_data[i] += c_tmp_data[i];
    }
  } else {
    plus(x_data, &trueCount, c_tmp_data, &DYj_size);
  }
  for (k = 0; k < trueCount; k++) {
    x_data[k] = std::sqrt(x_data[k]);
  }
  if (trueCount == validScan.InternalAngles.size[0]) {
    d2scaled = (MinTurningRadius + RobotRadius) + SafetyDistance;
    nx = trueCount;
    for (int i{0}; i < trueCount; i++) {
      blockedR_data[i] =
          ((x_data[i] < d2scaled) && (validScan.InternalAngles.data[i] <= 0.0));
    }
  } else {
    d_binary_expand_op(blockedR_data, &nx, x_data, &trueCount, this,
                       &validScan);
  }
  trueCount = idx;
  for (int i{0}; i < idx; i++) {
    delta1 = a_tmp_data[i];
    x_data[i] = delta1 * delta1;
  }
  for (int i{0}; i < DYj_size; i++) {
    delta1 = delta2 - DYj_data[i];
    c_tmp_data[i] = delta1 * delta1;
  }
  if (idx == DYj_size) {
    for (int i{0}; i < idx; i++) {
      x_data[i] += c_tmp_data[i];
    }
  } else {
    plus(x_data, &trueCount, c_tmp_data, &DYj_size);
  }
  for (k = 0; k < trueCount; k++) {
    x_data[k] = std::sqrt(x_data[k]);
  }
  if (trueCount == validScan.InternalAngles.size[0]) {
    d2scaled = (MinTurningRadius + RobotRadius) + SafetyDistance;
    DYj_size = trueCount;
    for (int i{0}; i < trueCount; i++) {
      blockedL_data[i] =
          ((x_data[i] < d2scaled) && (validScan.InternalAngles.data[i] >= 0.0));
    }
  } else {
    c_binary_expand_op(blockedL_data, &DYj_size, x_data, &trueCount, this,
                       &validScan);
  }
  k = (nx >= 1);
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (nx > 0)) {
    if (blockedR_data[nx - 1]) {
      idx = 1;
      ii_data = static_cast<short>(nx);
      exitg1 = true;
    } else {
      nx--;
    }
  }
  if (k == 1) {
    if (idx == 0) {
      k = 0;
    }
  } else {
    k = (idx >= 1);
  }
  for (int i{0}; i < k; i++) {
    d2scaled = validScan.InternalAngles.data[ii_data - 1];
  }
  nx = (DYj_size >= 1);
  idx = 0;
  trueCount = 0;
  exitg1 = false;
  while ((!exitg1) && (trueCount <= DYj_size - 1)) {
    if (blockedL_data[trueCount]) {
      idx = 1;
      ii_data = static_cast<short>(trueCount + 1);
      exitg1 = true;
    } else {
      trueCount++;
    }
  }
  if (nx == 1) {
    if (idx == 0) {
      nx = 0;
    }
  } else {
    nx = (idx >= 1);
  }
  for (int i{0}; i < nx; i++) {
    delta1 = validScan.InternalAngles.data[ii_data - 1];
  }
  if (k == 0) {
    d2scaled = AngularSectorMidPoints[0];
  } else if (d2scaled <= AngularSectorMidPoints[0]) {
    d2scaled = AngularSectorMidPoints[1];
  }
  if (nx == 0) {
    delta1 = AngularSectorMidPoints[179];
  } else if (delta1 >= AngularSectorMidPoints[179]) {
    delta1 = AngularSectorMidPoints[178];
  }
  for (int i{0}; i < 180; i++) {
    MaskedHistogram[i] =
        (BinaryHistogram[i] || ((AngularSectorMidPoints[i] < d2scaled) ||
                                (AngularSectorMidPoints[i] > delta1)));
  }
  return selectHeadingDirection();
}

} // namespace coder

// End of code generation (controllerVFH.cpp)
