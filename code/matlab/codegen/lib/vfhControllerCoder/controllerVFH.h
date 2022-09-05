//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// controllerVFH.h
//
// Code generation for function 'controllerVFH'
//

#ifndef CONTROLLERVFH_H
#define CONTROLLERVFH_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class lidarScan;

}

// Type Definitions
namespace coder {
class controllerVFH {
public:
  double step(const lidarScan *varargin_1);

protected:
  void buildPolarObstacleDensity(const lidarScan *scan);
  double selectHeadingDirection();
  void computeCost(const double c_data[], const int c_size[2], double prevDir,
                   double cost_data[], int cost_size[2]) const;

public:
  int isInitialized;
  double NarrowOpeningThreshold;
  double DistanceLimits[2];
  double RobotRadius;
  double SafetyDistance;
  double MinTurningRadius;
  double TargetDirectionWeight;
  double CurrentDirectionWeight;
  double PreviousDirectionWeight;
  double HistogramThresholds[2];
  double PolarObstacleDensity[180];
  boolean_T BinaryHistogram[180];
  boolean_T MaskedHistogram[180];
  double PreviousDirection;
  double AngularSectorMidPoints[180];
  double AngularDifference;
  double AngularSectorStartPoints[180];
  double AngularLimits[2];
};

} // namespace coder

#endif
// End of code generation (controllerVFH.h)
