//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_vfhControllerCoder_api.h
//
// Code generation for function 'vfhControllerCoder'
//

#ifndef _CODER_VFHCONTROLLERCODER_API_H
#define _CODER_VFHCONTROLLERCODER_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
real_T vfhControllerCoder(real_T pose[3], coder::array<boolean_T, 2U> *map);

void vfhControllerCoder_api(const mxArray *const prhs[2], const mxArray **plhs);

void vfhControllerCoder_atexit();

void vfhControllerCoder_initialize();

void vfhControllerCoder_terminate();

void vfhControllerCoder_xil_shutdown();

void vfhControllerCoder_xil_terminate();

#endif
// End of code generation (_coder_vfhControllerCoder_api.h)
