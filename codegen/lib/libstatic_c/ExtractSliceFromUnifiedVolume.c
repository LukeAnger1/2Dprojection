/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ExtractSliceFromUnifiedVolume.c
 *
 * Code generation for function 'ExtractSliceFromUnifiedVolume'
 *
 */

/* Include files */
#include "ExtractSliceFromUnifiedVolume.h"
#include "colon.h"
#include "libstatic_c_emxutil.h"
#include "libstatic_c_types.h"
#include "meshgrid.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void ExtractSliceFromUnifiedVolume(const emxArray_real_T *volume, double N,
                                   double rotationVector[3], double angle,
                                   emxArray_real_T *sliceData)
{
  emxArray_real_T *meshN;
  emxArray_real_T *xGrid;
  emxArray_real_T *xRot;
  emxArray_real_T *yGrid;
  emxArray_real_T *yRot;
  emxArray_real_T *zRot;
  const double *volume_data;
  double angleRad;
  double b_y0;
  double cosTheta;
  double dotProduct;
  double vx;
  double vy;
  double vz;
  double x0;
  double *meshN_data;
  double *xGrid_data;
  double *xRot_data;
  double *yRot_data;
  double *zRot_data;
  int b_i;
  int i;
  int j;
  int loop_ub;
  int loop_ub_tmp;
  int zGrid_size_idx_1_tmp;
  volume_data = volume->data;
  /*  Create meshgrid for the volume */
  dotProduct = -(N / 2.0);
  angleRad = N / 2.0 - 1.0;
  emxInit_real_T(&meshN, 2);
  if (rtIsNaN(dotProduct) || rtIsNaN(angleRad)) {
    i = meshN->size[0] * meshN->size[1];
    meshN->size[0] = 1;
    meshN->size[1] = 1;
    emxEnsureCapacity_real_T(meshN, i);
    meshN_data = meshN->data;
    meshN_data[0] = rtNaN;
  } else if (angleRad < dotProduct) {
    meshN->size[0] = 1;
    meshN->size[1] = 0;
  } else if ((rtIsInf(dotProduct) || rtIsInf(angleRad)) &&
             (dotProduct == angleRad)) {
    i = meshN->size[0] * meshN->size[1];
    meshN->size[0] = 1;
    meshN->size[1] = 1;
    emxEnsureCapacity_real_T(meshN, i);
    meshN_data = meshN->data;
    meshN_data[0] = rtNaN;
  } else if (floor(dotProduct) == dotProduct) {
    i = meshN->size[0] * meshN->size[1];
    meshN->size[0] = 1;
    loop_ub = (int)(angleRad - dotProduct);
    meshN->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(meshN, i);
    meshN_data = meshN->data;
    for (i = 0; i <= loop_ub; i++) {
      meshN_data[i] = dotProduct + (double)i;
    }
  } else {
    eml_float_colon(dotProduct, angleRad, meshN);
  }
  /*  Create a grid for the slice (initially in xy-plane, z=0) */
  emxInit_real_T(&xGrid, 2);
  emxInit_real_T(&yGrid, 2);
  meshgrid(meshN, meshN, xGrid, yGrid);
  meshN_data = yGrid->data;
  xGrid_data = xGrid->data;
  emxFree_real_T(&meshN);
  loop_ub = xGrid->size[0];
  zGrid_size_idx_1_tmp = xGrid->size[1];
  /*  Convert angle to radians */
  angleRad = angle * 3.1415926535897931 / 180.0;
  /*  Normalize the rotation vector */
  dotProduct = b_norm(rotationVector);
  rotationVector[0] /= dotProduct;
  rotationVector[1] /= dotProduct;
  rotationVector[2] /= dotProduct;
  vx = rotationVector[0];
  vy = rotationVector[1];
  vz = rotationVector[2];
  /*  Initialize rotated slice coordinates */
  emxInit_real_T(&xRot, 2);
  i = xRot->size[0] * xRot->size[1];
  xRot->size[0] = xGrid->size[0];
  xRot->size[1] = xGrid->size[1];
  emxEnsureCapacity_real_T(xRot, i);
  xRot_data = xRot->data;
  loop_ub_tmp = xGrid->size[0] * xGrid->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    xRot_data[i] = 0.0;
  }
  emxInit_real_T(&yRot, 2);
  i = yRot->size[0] * yRot->size[1];
  yRot->size[0] = yGrid->size[0];
  yRot->size[1] = yGrid->size[1];
  emxEnsureCapacity_real_T(yRot, i);
  yRot_data = yRot->data;
  loop_ub_tmp = yGrid->size[0] * yGrid->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    yRot_data[i] = 0.0;
  }
  emxInit_real_T(&zRot, 2);
  i = zRot->size[0] * zRot->size[1];
  zRot->size[0] = xGrid->size[0];
  zRot->size[1] = xGrid->size[1];
  emxEnsureCapacity_real_T(zRot, i);
  zRot_data = zRot->data;
  loop_ub_tmp = xGrid->size[0] * xGrid->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    zRot_data[i] = 0.0;
  }
  /*  Rodrigues' rotation formula implementation */
  cosTheta = cos(angleRad);
  angleRad = sin(angleRad);
  /*  Apply rotation to each point in the slice */
  i = xGrid->size[0];
  for (b_i = 0; b_i < i; b_i++) {
    int i1;
    i1 = xGrid->size[1];
    for (j = 0; j < i1; j++) {
      /*  Original point */
      x0 = xGrid_data[b_i + xGrid->size[0] * j];
      b_y0 = meshN_data[b_i + yGrid->size[0] * j];
      /*  Dot product with rotation axis */
      dotProduct = (vx * x0 + vy * b_y0) + vz * 0.0;
      /*  Cross product with rotation axis */
      /*  Apply Rodrigues' rotation formula */
      xRot_data[b_i + xRot->size[0] * j] =
          (x0 * cosTheta + (vy * 0.0 - vz * b_y0) * angleRad) +
          vx * dotProduct * (1.0 - cosTheta);
      yRot_data[b_i + yRot->size[0] * j] =
          (b_y0 * cosTheta + (vz * x0 - vx * 0.0) * angleRad) +
          vy * dotProduct * (1.0 - cosTheta);
      zRot_data[b_i + zRot->size[0] * j] =
          (0.0 * cosTheta + (vx * b_y0 - vy * x0) * angleRad) +
          vz * dotProduct * (1.0 - cosTheta);
    }
  }
  emxFree_real_T(&yGrid);
  /*  Initialize the slice data */
  i = sliceData->size[0] * sliceData->size[1];
  sliceData->size[0] = xGrid->size[0];
  sliceData->size[1] = xGrid->size[1];
  emxFree_real_T(&xGrid);
  emxEnsureCapacity_real_T(sliceData, i);
  meshN_data = sliceData->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    meshN_data[i] = 0.0;
  }
  /*  Perform trilinear interpolation to extract the slice data */
  for (b_i = 0; b_i < loop_ub; b_i++) {
    for (j = 0; j < zGrid_size_idx_1_tmp; j++) {
      /*  Get the coordinates in the volume space */
      dotProduct = xRot_data[b_i + xRot->size[0] * j] + N / 2.0;
      angleRad = yRot_data[b_i + yRot->size[0] * j] + N / 2.0;
      vx = zRot_data[b_i + zRot->size[0] * j] + N / 2.0;
      /*  Ensure coordinates are within bounds */
      if (dotProduct < 1.0) {
        dotProduct = 1.0;
      }
      if (angleRad < 1.0) {
        angleRad = 1.0;
      }
      if (vx < 1.0) {
        vx = 1.0;
      }
      if (dotProduct > N) {
        dotProduct = N;
      }
      if (angleRad > N) {
        angleRad = N;
      }
      if (vx > N) {
        vx = N;
      }
      /*  Get integer indices and fractional parts */
      x0 = floor(dotProduct);
      b_y0 = floor(angleRad);
      vz = floor(vx);
      /*  Handle edge case */
      if (x0 == N) {
        x0 = N - 1.0;
      }
      if (b_y0 == N) {
        b_y0 = N - 1.0;
      }
      if (vz == N) {
        vz = N - 1.0;
      }
      vy = dotProduct - x0;
      dotProduct = angleRad - b_y0;
      angleRad = vx - vz;
      /*  Get the eight corner values */
      /*  Perform trilinear interpolation */
      meshN_data[b_i + sliceData->size[0] * j] =
          ((volume_data[(((int)b_y0 + volume->size[0] * ((int)x0 - 1)) +
                         volume->size[0] * volume->size[1] * ((int)vz - 1)) -
                        1] *
                (1.0 - vy) +
            volume_data[(((int)b_y0 + volume->size[0] * (int)x0) +
                         volume->size[0] * volume->size[1] * ((int)vz - 1)) -
                        1] *
                vy) *
               (1.0 - dotProduct) +
           (volume_data[((int)b_y0 + volume->size[0] * ((int)x0 - 1)) +
                        volume->size[0] * volume->size[1] * ((int)vz - 1)] *
                (1.0 - vy) +
            volume_data[((int)b_y0 + volume->size[0] * (int)x0) +
                        volume->size[0] * volume->size[1] * ((int)vz - 1)] *
                vy) *
               dotProduct) *
              (1.0 - angleRad) +
          ((volume_data[(((int)b_y0 + volume->size[0] * ((int)x0 - 1)) +
                         volume->size[0] * volume->size[1] * (int)vz) -
                        1] *
                (1.0 - vy) +
            volume_data[(((int)b_y0 + volume->size[0] * (int)x0) +
                         volume->size[0] * volume->size[1] * (int)vz) -
                        1] *
                vy) *
               (1.0 - dotProduct) +
           (volume_data[((int)b_y0 + volume->size[0] * ((int)x0 - 1)) +
                        volume->size[0] * volume->size[1] * (int)vz] *
                (1.0 - vy) +
            volume_data[((int)b_y0 + volume->size[0] * (int)x0) +
                        volume->size[0] * volume->size[1] * (int)vz] *
                vy) *
               dotProduct) *
              angleRad;
    }
  }
  emxFree_real_T(&zRot);
  emxFree_real_T(&yRot);
  emxFree_real_T(&xRot);
  /*  Remove NaN values (replace with 0) */
  for (b_i = 0; b_i < loop_ub_tmp; b_i++) {
    if (rtIsNaN(meshN_data[b_i])) {
      meshN_data[b_i] = 0.0;
    }
  }
}

/* End of code generation (ExtractSliceFromUnifiedVolume.c) */
