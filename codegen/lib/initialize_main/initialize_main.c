/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * initialize_main.c
 *
 * Code generation for function 'initialize_main'
 *
 */

/* Include files */
#include "initialize_main.h"
#include "fftn.h"
#include "fftshift.h"
#include "initialize_main_data.h"
#include "initialize_main_emxutil.h"
#include "initialize_main_initialize.h"
#include "initialize_main_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void initialize_main(double N, emxArray_real_T *realVolume,
                     emxArray_real_T *imagVolume)
{
  emxArray_creal_T *spectrum;
  emxArray_real_T *r;
  creal_T *spectrum_data;
  double center;
  double cube_size;
  double d;
  double d1;
  double eye_radius;
  double eye_x1;
  double *imagVolume_data;
  double *r_data;
  int b_loop_ub_tmp;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int loop_ub;
  int loop_ub_tmp;
  int unnamed_idx_0;
  int unnamed_idx_1;
  if (!isInitialized_initialize_main) {
    initialize_main_initialize();
  }
  /*  Generate a 3D cube directly */
  emxInit_real_T(&r, 3);
  loop_ub_tmp = (int)N;
  i = r->size[0] * r->size[1] * r->size[2];
  r->size[0] = (int)N;
  r->size[1] = (int)N;
  r->size[2] = (int)N;
  emxEnsureCapacity_real_T(r, i);
  r_data = r->data;
  b_loop_ub_tmp = (int)N * (int)N * (int)N;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    r_data[i] = 0.0;
  }
  center = N / 2.0;
  cube_size = N / 4.0;
  /*  Create solid cube */
  d = center - cube_size;
  d1 = center + cube_size;
  if (d > d1) {
    i = 0;
    i1 = 0;
    b_loop_ub_tmp = 0;
    i2 = 0;
    i3 = 0;
    i4 = 0;
  } else {
    i = (int)d - 1;
    i1 = (int)d1;
    b_loop_ub_tmp = (int)d - 1;
    i2 = (int)d1;
    i3 = (int)d - 1;
    i4 = (int)d1;
  }
  unnamed_idx_0 = i1 - i;
  unnamed_idx_1 = i2 - b_loop_ub_tmp;
  loop_ub = i4 - i3;
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (i2 = 0; i2 < unnamed_idx_1; i2++) {
      for (i4 = 0; i4 < unnamed_idx_0; i4++) {
        r_data[((i + i4) + r->size[0] * (b_loop_ub_tmp + i2)) +
               r->size[0] * r->size[1] * (i3 + i1)] = 255.0;
      }
    }
  }
  /*  Eye hole parameters */
  eye_radius = N / 16.0;
  cube_size = N / 8.0;
  eye_x1 = center - cube_size;
  cube_size += center;
  /*  Carve two eye holes (cylindrical, full depth in Z) */
  d = eye_x1 - eye_radius;
  d1 = eye_x1 + eye_radius;
  if (d > d1) {
    i = 0;
    i1 = 0;
  } else {
    i = (int)d - 1;
    i1 = (int)d1;
  }
  d = center - eye_radius;
  d1 = center + eye_radius;
  if (d > d1) {
    b_loop_ub_tmp = 0;
    i2 = 0;
  } else {
    b_loop_ub_tmp = (int)d - 1;
    i2 = (int)d1;
  }
  unnamed_idx_0 = i1 - i;
  unnamed_idx_1 = i2 - b_loop_ub_tmp;
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    for (i2 = 0; i2 < unnamed_idx_1; i2++) {
      for (i3 = 0; i3 < unnamed_idx_0; i3++) {
        r_data[((i + i3) + r->size[0] * (b_loop_ub_tmp + i2)) +
               r->size[0] * r->size[1] * i1] = 0.0;
      }
    }
  }
  eye_x1 = cube_size - eye_radius;
  cube_size += eye_radius;
  if (eye_x1 > cube_size) {
    i = 0;
    i1 = 0;
  } else {
    i = (int)eye_x1 - 1;
    i1 = (int)cube_size;
  }
  if (d > d1) {
    b_loop_ub_tmp = 0;
    i2 = 0;
  } else {
    b_loop_ub_tmp = (int)d - 1;
    i2 = (int)d1;
  }
  unnamed_idx_0 = i1 - i;
  unnamed_idx_1 = i2 - b_loop_ub_tmp;
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    for (i2 = 0; i2 < unnamed_idx_1; i2++) {
      for (i3 = 0; i3 < unnamed_idx_0; i3++) {
        r_data[((i + i3) + r->size[0] * (b_loop_ub_tmp + i2)) +
               r->size[0] * r->size[1] * i1] = 0.0;
      }
    }
  }
  /*  3D FFT-shift for the spatial volume */
  /*  Compute the 3D Spectrum  */
  fftshift(r);
  emxInit_creal_T(&spectrum, 3);
  fftn(r, spectrum);
  emxFree_real_T(&r);
  /*  Use fftn for 3D FFT */
  /*  Do a fft shift  */
  b_fftshift(spectrum);
  spectrum_data = spectrum->data;
  /*  Split the volume into real and imaginary components */
  /*  Allocation  */
  /*  Splitting  */
  i = realVolume->size[0] * realVolume->size[1] * realVolume->size[2];
  realVolume->size[0] = (int)N;
  realVolume->size[1] = (int)N;
  realVolume->size[2] = (int)N;
  emxEnsureCapacity_real_T(realVolume, i);
  r_data = realVolume->data;
  i = imagVolume->size[0] * imagVolume->size[1] * imagVolume->size[2];
  imagVolume->size[0] = (int)N;
  imagVolume->size[1] = (int)N;
  imagVolume->size[2] = (int)N;
  emxEnsureCapacity_real_T(imagVolume, i);
  imagVolume_data = imagVolume->data;
  for (b_loop_ub_tmp = 0; b_loop_ub_tmp < loop_ub_tmp; b_loop_ub_tmp++) {
    for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub_tmp; unnamed_idx_0++) {
      for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub_tmp; unnamed_idx_1++) {
        r_data[(b_loop_ub_tmp + realVolume->size[0] * unnamed_idx_0) +
               realVolume->size[0] * realVolume->size[1] * unnamed_idx_1] =
            spectrum_data[(b_loop_ub_tmp + spectrum->size[0] * unnamed_idx_0) +
                          spectrum->size[0] * spectrum->size[1] * unnamed_idx_1]
                .re;
        imagVolume_data[(b_loop_ub_tmp + imagVolume->size[0] * unnamed_idx_0) +
                        imagVolume->size[0] * imagVolume->size[1] *
                            unnamed_idx_1] =
            spectrum_data[(b_loop_ub_tmp + spectrum->size[0] * unnamed_idx_0) +
                          spectrum->size[0] * spectrum->size[1] * unnamed_idx_1]
                .im;
      }
    }
  }
  emxFree_creal_T(&spectrum);
}

/* End of code generation (initialize_main.c) */
