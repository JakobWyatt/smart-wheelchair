//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// vfhControllerCoder.cpp
//
// Code generation for function 'vfhControllerCoder'
//

// Include files
#include "vfhControllerCoder.h"
#include "CircularBuffer.h"
#include "CircularBufferIndex.h"
#include "RangeSensorBase.h"
#include "SharedMapProperties.h"
#include "binaryOccupancyMap.h"
#include "controllerVFH.h"
#include "lidarScan.h"
#include "randn.h"
#include "rangeSensor.h"
#include "rt_nonfinite.h"
#include "vfhControllerCoder_data.h"
#include "vfhControllerCoder_initialize.h"
#include "vfhControllerCoder_internal_types.h"
#include "wrapToPi.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>

// Function Declarations
static int div_s32(int numerator, int denominator);

// Function Definitions
static int div_s32(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int b_denominator;
    unsigned int b_numerator;
    if (numerator < 0) {
      b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      b_numerator = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      b_denominator = static_cast<unsigned int>(denominator);
    }
    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int>(b_numerator);
    } else {
      quotient = static_cast<int>(b_numerator);
    }
  }
  return quotient;
}

double vfhControllerCoder(const double pose[3],
                          const coder::array<boolean_T, 2U> &map)
{
  static const double sweep[258]{
      -3.1415926535897931,   -3.1171926535897931,   -3.0927926535897932,
      -3.0683926535897932,   -3.0439926535897932,   -3.0195926535897932,
      -2.9951926535897933,   -2.9707926535897933,   -2.9463926535897933,
      -2.9219926535897933,   -2.8975926535897929,   -2.8731926535897929,
      -2.8487926535897929,   -2.824392653589793,    -2.799992653589793,
      -2.775592653589793,    -2.751192653589793,    -2.7267926535897931,
      -2.7023926535897931,   -2.6779926535897931,   -2.6535926535897931,
      -2.6291926535897931,   -2.6047926535897932,   -2.5803926535897932,
      -2.5559926535897932,   -2.5315926535897932,   -2.5071926535897928,
      -2.4827926535897928,   -2.4583926535897929,   -2.4339926535897929,
      -2.4095926535897929,   -2.3851926535897929,   -2.360792653589793,
      -2.336392653589793,    -2.311992653589793,    -2.287592653589793,
      -2.263192653589793,    -2.2387926535897931,   -2.2143926535897931,
      -2.1899926535897931,   -2.1655926535897931,   -2.1411926535897932,
      -2.1167926535897932,   -2.0923926535897932,   -2.0679926535897932,
      -2.0435926535897933,   -2.0191926535897933,   -1.9947926535897931,
      -1.9703926535897931,   -1.9459926535897931,   -1.9215926535897931,
      -1.8971926535897929,   -1.872792653589793,    -1.848392653589793,
      -1.823992653589793,    -1.799592653589793,    -1.7751926535897931,
      -1.7507926535897931,   -1.7263926535897931,   -1.7019926535897931,
      -1.6775926535897929,   -1.6531926535897929,   -1.628792653589793,
      -1.604392653589793,    -1.579992653589793,    -1.555592653589793,
      -1.5311926535897931,   -1.5067926535897931,   -1.4823926535897931,
      -1.4579926535897929,   -1.4335926535897929,   -1.409192653589793,
      -1.384792653589793,    -1.360392653589793,    -1.335992653589793,
      -1.311592653589793,    -1.2871926535897931,   -1.2627926535897931,
      -1.2383926535897929,   -1.2139926535897929,   -1.1895926535897929,
      -1.165192653589793,    -1.1407926535897932,   -1.1163926535897928,
      -1.0919926535897928,   -1.0675926535897928,   -1.0431926535897929,
      -1.0187926535897929,   -0.9943926535897929,   -0.96999265358979292,
      -0.94559265358979294,  -0.921192653589793,    -0.896792653589793,
      -0.872392653589793,    -0.847992653589793,    -0.82359265358979306,
      -0.79919265358979308,  -0.7747926535897931,   -0.75039265358979312,
      -0.72599265358979315,  -0.70159265358979317,  -0.67719265358979275,
      -0.65279265358979277,  -0.62839265358979279,  -0.60399265358979282,
      -0.57959265358979284,  -0.55519265358979286,  -0.53079265358979288,
      -0.50639265358979291,  -0.48199265358979293,  -0.45759265358979295,
      -0.433192653589793,    -0.408792653589793,    -0.384392653589793,
      -0.35999265358979304,  -0.33559265358979307,  -0.31119265358979309,
      -0.28679265358979311,  -0.26239265358979313,  -0.23799265358979271,
      -0.21359265358979274,  -0.18919265358979276,  -0.16479265358979278,
      -0.1403926535897928,   -0.11599265358979283,  -0.09159265358979285,
      -0.067192653589792872, -0.042792653589792895, -0.018392653589792918,
      0.0060073464102070595, 0.030407346410207037,  0.054807346410207014,
      0.079207346410206991,  0.10360734641020697,   0.12800734641020695,
      0.15240734641020692,   0.1768073464102069,    0.20120734641020688,
      0.22560734641020685,   0.25000734641020728,   0.27440734641020725,
      0.29880734641020723,   0.32320734641020721,   0.34760734641020719,
      0.37200734641020716,   0.39640734641020714,   0.42080734641020712,
      0.44520734641020709,   0.46960734641020707,   0.49400734641020705,
      0.518407346410207,     0.542807346410207,     0.567207346410207,
      0.591607346410207,     0.61600734641020694,   0.64040734641020691,
      0.66480734641020689,   0.68920734641020731,   0.71360734641020729,
      0.73800734641020727,   0.76240734641020724,   0.78680734641020722,
      0.8112073464102072,    0.83560734641020717,   0.86000734641020715,
      0.88440734641020713,   0.90880734641020711,   0.93320734641020708,
      0.95760734641020706,   0.982007346410207,     1.006407346410207,
      1.030807346410207,     1.055207346410207,     1.0796073464102069,
      1.1040073464102069,    1.1284073464102073,    1.1528073464102071,
      1.1772073464102071,    1.2016073464102071,    1.226007346410207,
      1.2504073464102072,    1.2748073464102072,    1.2992073464102072,
      1.3236073464102072,    1.3480073464102071,    1.3724073464102071,
      1.3968073464102071,    1.4212073464102071,    1.4456073464102071,
      1.4700073464102072,    1.4944073464102072,    1.5188073464102072,
      1.5432073464102072,    1.5676073464102072,    1.5920073464102071,
      1.6164073464102071,    1.6408073464102071,    1.6652073464102071,
      1.6896073464102073,    1.7140073464102072,    1.7384073464102072,
      1.7628073464102072,    1.7872073464102072,    1.8116073464102072,
      1.8360073464102071,    1.8604073464102071,    1.8848073464102071,
      1.9092073464102073,    1.9336073464102073,    1.9580073464102072,
      1.9824073464102072,    2.0068073464102074,    2.0312073464102074,
      2.0556073464102074,    2.0800073464102073,    2.1044073464102073,
      2.1288073464102073,    2.1532073464102073,    2.1776073464102073,
      2.2020073464102072,    2.2264073464102072,    2.2508073464102072,
      2.2752073464102072,    2.2996073464102071,    2.3240073464102071,
      2.3484073464102071,    2.3728073464102071,    2.3972073464102071,
      2.421607346410207,     2.446007346410207,     2.470407346410207,
      2.494807346410207,     2.5192073464102074,    2.5436073464102074,
      2.5680073464102073,    2.5924073464102073,    2.6168073464102073,
      2.6412073464102073,    2.6656073464102072,    2.6900073464102072,
      2.7144073464102072,    2.7388073464102072,    2.7632073464102072,
      2.7876073464102071,    2.8120073464102071,    2.8364073464102071,
      2.8608073464102071,    2.885207346410207,     2.9096073464102075,
      2.9340073464102074,    2.9584073464102074,    2.9828073464102074,
      3.0072073464102074,    3.0316073464102073,    3.0560073464102073,
      3.0804073464102073,    3.1048073464102073,    3.1292073464102073};
  coder::binaryOccupancyMap binmap;
  coder::controllerVFH vfh;
  coder::lidarScan scan;
  coder::matlabshared::autonomous::internal::CircularBuffer *obj;
  coder::rangeSensor lidar;
  coder::array<boolean_T, 2U> buffer;
  coder::array<boolean_T, 2U> grid;
  double measRanges[258];
  double r[258];
  double matSz_idx_0;
  double matSz_idx_1;
  int npages[2];
  int outsize[2];
  int binmap_idx_1;
  int i;
  int k;
  int stride;
  boolean_T x[2];
  boolean_T a;
  boolean_T exitg1;
  if (!isInitialized_vfhControllerCoder) {
    vfhControllerCoder_initialize();
  }
  //  MATLAB Example Code
  binmap.HasParent = false;
  binmap.SharedProperties.GridSize[0] = map.size(0);
  binmap.SharedProperties.GridSize[1] = map.size(1);
  binmap.SharedProperties.GridOriginInLocal[0] = 0.0;
  binmap.SharedProperties.GridOriginInLocal[1] = 0.0;
  binmap.SharedProperties.LocalOriginInWorld[0] = 0.0;
  binmap.SharedProperties.LocalOriginInWorld[1] = 0.0;
  binmap.DataSize[0] = map.size(0);
  binmap.DataSize[1] = map.size(1);
  matSz_idx_0 = binmap.SharedProperties.GridSize[0];
  matSz_idx_1 = binmap.SharedProperties.GridSize[1];
  binmap.Index.Head[0] = 1.0;
  binmap.Index.Head[1] = 1.0;
  binmap.Index.Size[0] = matSz_idx_0;
  binmap.Index.Size[1] = matSz_idx_1;
  binmap.DefaultValueInternal = false;
  obj = &binmap.Buffer;
  a = binmap.DefaultValueInternal;
  matSz_idx_0 = binmap.Index.Size[0];
  matSz_idx_1 = binmap.Index.Size[1];
  obj->Index = &binmap.Index;
  obj->Buffer.set_size(static_cast<int>(matSz_idx_0),
                       static_cast<int>(matSz_idx_1));
  stride = static_cast<int>(matSz_idx_0) * static_cast<int>(matSz_idx_1);
  for (i = 0; i < stride; i++) {
    obj->Buffer[i] = a;
  }
  stride = binmap.Buffer.Buffer.size(0);
  binmap_idx_1 = binmap.Buffer.Buffer.size(1);
  binmap.Buffer.Buffer.set_size(stride, binmap_idx_1);
  stride *= binmap_idx_1;
  for (i = 0; i < stride; i++) {
    binmap.Buffer.Buffer[i] = map[i];
  }
  binmap.Index.Head[0] = 1.0;
  binmap.Index.Head[1] = 1.0;
  std::copy(&sweep[0], &sweep[258], &lidar.pAngleSweep[0]);
  x[0] = (binmap.Index.Head[0] == 1.0);
  x[1] = (binmap.Index.Head[1] == 1.0);
  a = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (!x[k]) {
      a = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (a) {
    grid.set_size(binmap.Buffer.Buffer.size(0), binmap.Buffer.Buffer.size(1));
    stride = binmap.Buffer.Buffer.size(0) * binmap.Buffer.Buffer.size(1);
    for (i = 0; i < stride; i++) {
      grid[i] = binmap.Buffer.Buffer[i];
    }
  } else {
    grid.set_size(binmap.Buffer.Buffer.size(0), binmap.Buffer.Buffer.size(1));
    stride = binmap.Buffer.Buffer.size(0) * binmap.Buffer.Buffer.size(1);
    for (i = 0; i < stride; i++) {
      grid[i] = binmap.Buffer.Buffer[i];
    }
    matSz_idx_0 = -(binmap.Index.Head[0] - 1.0);
    matSz_idx_1 = -(binmap.Index.Head[1] - 1.0);
    if ((grid.size(0) != 0) && (grid.size(1) != 0) &&
        ((grid.size(0) != 1) || (grid.size(1) != 1))) {
      if (matSz_idx_0 < 0.0) {
        stride = static_cast<int>(-matSz_idx_0);
        a = false;
      } else {
        stride = static_cast<int>(matSz_idx_0);
        a = true;
      }
      if (stride > grid.size(0)) {
        stride -= div_s32(stride, grid.size(0)) * grid.size(0);
      }
      if (stride > (grid.size(0) >> 1)) {
        stride = grid.size(0) - stride;
        a = !a;
      }
      outsize[0] = stride;
      x[0] = a;
      if (matSz_idx_1 < 0.0) {
        stride = static_cast<int>(-matSz_idx_1);
        a = false;
      } else {
        stride = static_cast<int>(matSz_idx_1);
        a = true;
      }
      if (stride > grid.size(1)) {
        stride -= div_s32(stride, grid.size(1)) * grid.size(1);
      }
      if (stride > (grid.size(1) >> 1)) {
        stride = grid.size(1) - stride;
        a = !a;
      }
      outsize[1] = stride;
      x[1] = a;
      stride = grid.size(0);
      binmap_idx_1 = grid.size(1);
      if (stride >= binmap_idx_1) {
        binmap_idx_1 = stride;
      }
      buffer.set_size(1, static_cast<int>(std::floor(
                             static_cast<double>(binmap_idx_1) / 2.0)));
      stride = 1;
      npages[1] = 1;
      npages[0] = grid.size(1);
      for (int dim{0}; dim < 2; dim++) {
        int b_npages;
        int ns;
        int pagesize;
        i = grid.size(dim);
        binmap_idx_1 = outsize[dim];
        ns = binmap_idx_1 - 1;
        pagesize = stride * grid.size(dim);
        b_npages = npages[dim];
        if ((grid.size(dim) > 1) && (binmap_idx_1 > 0)) {
          for (int b_i{0}; b_i < b_npages; b_i++) {
            int pageroot;
            pageroot = b_i * pagesize;
            for (int j{0}; j < stride; j++) {
              int i1;
              i1 = pageroot + j;
              if (x[dim]) {
                int b_i1;
                for (k = 0; k <= ns; k++) {
                  buffer[k] = grid[i1 + ((k + i) - binmap_idx_1) * stride];
                }
                b_i1 = binmap_idx_1 + 1;
                for (k = i; k >= b_i1; k--) {
                  grid[i1 + (k - 1) * stride] =
                      grid[i1 + ((k - binmap_idx_1) - 1) * stride];
                }
                for (k = 0; k <= ns; k++) {
                  grid[i1 + k * stride] = buffer[k];
                }
              } else {
                int b_i1;
                for (k = 0; k <= ns; k++) {
                  buffer[k] = grid[i1 + k * stride];
                }
                b_i1 = i - binmap_idx_1;
                for (k = 0; k < b_i1; k++) {
                  grid[i1 + k * stride] =
                      grid[i1 + (k + binmap_idx_1) * stride];
                }
                for (k = 0; k <= ns; k++) {
                  grid[i1 + ((k + i) - binmap_idx_1) * stride] = buffer[k];
                }
              }
            }
          }
        }
        stride = pagesize;
      }
    }
    if (!binmap.HasParent) {
      binmap.Buffer.Buffer.set_size(grid.size(0), grid.size(1));
      stride = grid.size(0) * grid.size(1);
      for (i = 0; i < stride; i++) {
        binmap.Buffer.Buffer[i] = grid[i];
      }
      binmap.Index.Head[0] = 1.0;
      binmap.Index.Head[1] = 1.0;
    }
  }
  matSz_idx_0 = binmap.DataSize[0];
  matSz_idx_1 = binmap.DataSize[1];
  stride = static_cast<int>(matSz_idx_0);
  binmap_idx_1 = static_cast<int>(matSz_idx_1);
  buffer = grid.reshape(stride, binmap_idx_1);
  coder::nav::internal::RangeSensorBase::stepImpl_anonFcn1(
      lidar.pAngleSweep, buffer, &binmap, pose, measRanges);
  for (int b_i{0}; b_i < 258; b_i++) {
    if (measRanges[b_i] < 0.0) {
      measRanges[b_i] = rtNaN;
    }
  }
  coder::randn(r);
  for (int b_i{0}; b_i < 258; b_i++) {
    matSz_idx_0 = measRanges[b_i] + r[b_i] * 0.0;
    measRanges[b_i] = matSz_idx_0;
    if ((matSz_idx_0 < 0.0) && (!std::isnan(matSz_idx_0))) {
      measRanges[b_i] = 0.0;
    }
  }
  coder::randn(r);
  scan.ContainsOnlyFiniteData = false;
  scan.InternalRanges.size[0] = 258;
  scan.InternalAngles.size[0] = 258;
  for (i = 0; i < 258; i++) {
    scan.InternalRanges.data[i] = measRanges[i];
    scan.InternalAngles.data[i] = lidar.pAngleSweep[i] + r[i] * 0.0;
  }
  coder::robotics::internal::wrapToPi(scan.InternalAngles.data,
                                      &scan.InternalAngles.size[0]);
  vfh.NarrowOpeningThreshold = 0.8;
  vfh.RobotRadius = 0.1;
  vfh.CurrentDirectionWeight = 2.0;
  vfh.PreviousDirectionWeight = 2.0;
  vfh.AngularLimits[0] = -3.1415926535897931;
  vfh.AngularLimits[1] = 3.1415926535897931;
  vfh.isInitialized = 0;
  vfh.SafetyDistance = 1.0;
  vfh.DistanceLimits[0] = 0.0;
  vfh.DistanceLimits[1] = 15.0;
  vfh.HistogramThresholds[0] = 100.0;
  vfh.HistogramThresholds[1] = 200.0;
  vfh.MinTurningRadius = 1.0;
  vfh.TargetDirectionWeight = 5.0;
  return vfh.step(&scan);
}

// End of code generation (vfhControllerCoder.cpp)
