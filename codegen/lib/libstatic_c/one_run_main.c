/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * one_run_main.c
 *
 * Code generation for function 'one_run_main'
 *
 */

/* Include files */
#include "one_run_main.h"
#include "ExtractSliceFromUnifiedVolume.h"
#include "abs.h"
#include "fftshift.h"
#include "ifft2.h"
#include "libstatic_c_data.h"
#include "libstatic_c_emxutil.h"
#include "libstatic_c_initialize.h"
#include "libstatic_c_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void one_run_main(const emxArray_real_T *realVolume,
                  const emxArray_real_T *imagVolume, double N,
                  const double pivot[3], double angle,
                  emxArray_real_T *projection)
{
  emxArray_creal_T *projectionSlice;
  emxArray_creal_T *r;
  emxArray_real_T *imagData;
  emxArray_real_T *realData;
  creal_T *projectionSlice_data;
  double b_pivot[3];
  double *imagData_data;
  double *realData_data;
  int i;
  int jj;
  int loop_ub_tmp;
  if (!isInitialized_libstatic_c) {
    libstatic_c_initialize();
  }
  /*  Extract the projection slice  */
  emxInit_real_T(&realData, 2);
  b_pivot[0] = pivot[0];
  b_pivot[1] = pivot[1];
  b_pivot[2] = pivot[2];
  ExtractSliceFromUnifiedVolume(realVolume, N, b_pivot, angle, realData);
  realData_data = realData->data;
  emxInit_real_T(&imagData, 2);
  b_pivot[0] = pivot[0];
  b_pivot[1] = pivot[1];
  b_pivot[2] = pivot[2];
  ExtractSliceFromUnifiedVolume(imagVolume, N, b_pivot, angle, imagData);
  imagData_data = imagData->data;
  /*  Build the complex slice */
  emxInit_creal_T(&projectionSlice, 2);
  i = (int)N;
  jj = projectionSlice->size[0] * projectionSlice->size[1];
  projectionSlice->size[0] = (int)N;
  projectionSlice->size[1] = (int)N;
  emxEnsureCapacity_creal_T(projectionSlice, jj);
  projectionSlice_data = projectionSlice->data;
  loop_ub_tmp = (int)N * (int)N;
  for (jj = 0; jj < loop_ub_tmp; jj++) {
    projectionSlice_data[jj].re = 0.0;
    projectionSlice_data[jj].im = 0.0;
  }
  for (loop_ub_tmp = 0; loop_ub_tmp < i; loop_ub_tmp++) {
    for (jj = 0; jj < i; jj++) {
      projectionSlice_data[loop_ub_tmp + projectionSlice->size[0] * jj].re =
          realData_data[loop_ub_tmp + realData->size[0] * jj];
      projectionSlice_data[loop_ub_tmp + projectionSlice->size[0] * jj].im =
          imagData_data[loop_ub_tmp + imagData->size[0] * jj];
    }
  }
  emxFree_real_T(&imagData);
  emxFree_real_T(&realData);
  /*  Backtransform the slice to spatial domain and apply 2D FFT shift */
  emxInit_creal_T(&r, 2);
  ifft2(projectionSlice, r);
  emxFree_creal_T(&projectionSlice);
  b_abs(r, projection);
  emxFree_creal_T(&r);
  c_fftshift(projection);
  realData_data = projection->data;
  /*  stupid scaling */
  loop_ub_tmp = projection->size[0] * projection->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    realData_data[i] *= 0.001;
  }
}

/* End of code generation (one_run_main.c) */
