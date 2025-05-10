/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_render_api.h
 *
 * Code generation for function 'initialize_main'
 *
 */

#ifndef _CODER_RENDER_API_H
#define _CODER_RENDER_API_H

/* Include files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void initialize_main(real_T N, emxArray_real_T *realVolume,
                     emxArray_real_T *imagVolume);

void initialize_main_api(const mxArray *prhs, int32_T nlhs,
                         const mxArray *plhs[2]);

void one_run_main(emxArray_real_T *realVolume, emxArray_real_T *imagVolume,
                  real_T N, real_T pivot[3], real_T angle,
                  emxArray_real_T *projection);

void one_run_main_api(const mxArray *const prhs[5], const mxArray **plhs);

void render_atexit(void);

void render_initialize(void);

void render_terminate(void);

void render_xil_shutdown(void);

void render_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_render_api.h) */
