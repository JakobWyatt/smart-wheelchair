//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// vfhControllerCoder_initialize.cpp
//
// Code generation for function 'vfhControllerCoder_initialize'
//

// Include files
#include "vfhControllerCoder_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"
#include "vfhControllerCoder_data.h"

// Function Definitions
void vfhControllerCoder_initialize()
{
  eml_rand_mt19937ar_stateful_init();
  isInitialized_vfhControllerCoder = true;
}

// End of code generation (vfhControllerCoder_initialize.cpp)
