//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_vfhControllerCoder_mex.cpp
//
// Code generation for function 'vfhControllerCoder'
//

// Include files
#include "_coder_vfhControllerCoder_mex.h"
#include "_coder_vfhControllerCoder_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&vfhControllerCoder_atexit);
  // Module initialization.
  vfhControllerCoder_initialize();
  // Dispatch the entry-point.
  unsafe_vfhControllerCoder_mexFunction(nlhs, plhs, nrhs, prhs);
  // Module termination.
  vfhControllerCoder_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, (const char_T *)"windows-1252", true);
  return emlrtRootTLSGlobal;
}

void unsafe_vfhControllerCoder_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                           int32_T nrhs, const mxArray *prhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        18, "vfhControllerCoder");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "vfhControllerCoder");
  }
  // Call the function.
  vfhControllerCoder_api(prhs, &outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

// End of code generation (_coder_vfhControllerCoder_mex.cpp)
