/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fftn.c
 *
 * Code generation for function 'fftn'
 *
 */

/* Include files */
#include "fftn.h"
#include "FFTImplementationCallback.h"
#include "libstatic_c_emxutil.h"
#include "libstatic_c_types.h"
#include "permute.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void fftn(const emxArray_real_T *x, emxArray_creal_T *y)
{
  static const int iv[3] = {2, 1, 3};
  static const int iv1[3] = {3, 1, 2};
  static const int iv2[3] = {2, 3, 1};
  emxArray_creal_T *acc;
  emxArray_creal_T *xPerm;
  emxArray_creal_T *yPerm;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *acc_data;
  creal_T *xPerm_data;
  creal_T *yPerm_data;
  int lens[3];
  int b_k;
  int c_k;
  int i;
  int k;
  int nRows;
  int subsa_idx_1;
  int subsa_idx_2;
  bool guard1;
  lens[0] = x->size[0];
  lens[1] = x->size[1];
  lens[2] = x->size[2];
  emxInit_creal_T(&acc, 3);
  emxInit_creal_T(&xPerm, 3);
  emxInit_creal_T(&yPerm, 3);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if ((x->size[0] == 0) || (x->size[1] == 0) || (x->size[2] == 0)) {
    guard1 = true;
  } else {
    bool exitg1;
    bool useRadix2;
    useRadix2 = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 3)) {
      if (lens[k] == 0) {
        useRadix2 = true;
        exitg1 = true;
      } else {
        k++;
      }
    }
    if (useRadix2) {
      guard1 = true;
    } else {
      int i1;
      useRadix2 =
          ((x->size[0] > 0) && ((int)((unsigned int)x->size[0] &
                                      (unsigned int)(x->size[0] - 1)) == 0));
      k = c_FFTImplementationCallback_get(x->size[0], useRadix2, &nRows);
      c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                      sintabinv);
      if (useRadix2) {
        c_FFTImplementationCallback_r2b(x, x->size[0], costab, sintab, acc);
        acc_data = acc->data;
      } else {
        c_FFTImplementationCallback_dob(x, k, x->size[0], costab, sintab,
                                        sintabinv, acc);
        acc_data = acc->data;
      }
      if (nomovement(iv, acc)) {
        i = xPerm->size[0] * xPerm->size[1] * xPerm->size[2];
        xPerm->size[0] = acc->size[1];
        xPerm->size[1] = acc->size[0];
        xPerm->size[2] = acc->size[2];
        emxEnsureCapacity_creal_T(xPerm, i);
        xPerm_data = xPerm->data;
        k = acc->size[0] * acc->size[1] * acc->size[2];
        for (i = 0; i < k; i++) {
          xPerm_data[i] = acc_data[i];
        }
      } else {
        i = acc->size[1];
        k = xPerm->size[0] * xPerm->size[1] * xPerm->size[2];
        xPerm->size[0] = acc->size[1];
        nRows = acc->size[0];
        xPerm->size[1] = acc->size[0];
        i1 = acc->size[2];
        xPerm->size[2] = acc->size[2];
        emxEnsureCapacity_creal_T(xPerm, k);
        xPerm_data = xPerm->data;
        for (k = 0; k < i1; k++) {
          for (b_k = 0; b_k < i; b_k++) {
            if (acc->size[0] - 1 >= 0) {
              subsa_idx_1 = b_k + 1;
              subsa_idx_2 = k + 1;
            }
            for (c_k = 0; c_k < nRows; c_k++) {
              xPerm_data[((subsa_idx_1 + xPerm->size[0] * c_k) +
                          xPerm->size[0] * xPerm->size[1] * (subsa_idx_2 - 1)) -
                         1] =
                  acc_data[(c_k + acc->size[0] * (subsa_idx_1 - 1)) +
                           acc->size[0] * acc->size[1] * (subsa_idx_2 - 1)];
            }
          }
        }
      }
      useRadix2 =
          ((x->size[1] > 0) && ((int)((unsigned int)x->size[1] &
                                      (unsigned int)(x->size[1] - 1)) == 0));
      k = c_FFTImplementationCallback_get(x->size[1], useRadix2, &nRows);
      c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                      sintabinv);
      if (useRadix2) {
        e_FFTImplementationCallback_r2b(xPerm, x->size[1], costab, sintab,
                                        yPerm);
        yPerm_data = yPerm->data;
      } else {
        d_FFTImplementationCallback_dob(xPerm, k, x->size[1], costab, sintab,
                                        sintabinv, yPerm);
        yPerm_data = yPerm->data;
      }
      if (nomovement(iv, yPerm)) {
        i = acc->size[0] * acc->size[1] * acc->size[2];
        acc->size[0] = yPerm->size[1];
        acc->size[1] = yPerm->size[0];
        acc->size[2] = yPerm->size[2];
        emxEnsureCapacity_creal_T(acc, i);
        acc_data = acc->data;
        k = yPerm->size[0] * yPerm->size[1] * yPerm->size[2];
        for (i = 0; i < k; i++) {
          acc_data[i] = yPerm_data[i];
        }
      } else {
        i = yPerm->size[1];
        k = acc->size[0] * acc->size[1] * acc->size[2];
        acc->size[0] = yPerm->size[1];
        nRows = yPerm->size[0];
        acc->size[1] = yPerm->size[0];
        i1 = yPerm->size[2];
        acc->size[2] = yPerm->size[2];
        emxEnsureCapacity_creal_T(acc, k);
        acc_data = acc->data;
        for (k = 0; k < i1; k++) {
          for (b_k = 0; b_k < i; b_k++) {
            if (yPerm->size[0] - 1 >= 0) {
              subsa_idx_1 = b_k + 1;
              subsa_idx_2 = k + 1;
            }
            for (c_k = 0; c_k < nRows; c_k++) {
              acc_data[((subsa_idx_1 + acc->size[0] * c_k) +
                        acc->size[0] * acc->size[1] * (subsa_idx_2 - 1)) -
                       1] =
                  yPerm_data[(c_k + yPerm->size[0] * (subsa_idx_1 - 1)) +
                             yPerm->size[0] * yPerm->size[1] *
                                 (subsa_idx_2 - 1)];
            }
          }
        }
      }
      if (nomovement(iv1, acc)) {
        i = xPerm->size[0] * xPerm->size[1] * xPerm->size[2];
        xPerm->size[0] = acc->size[2];
        xPerm->size[1] = acc->size[0];
        xPerm->size[2] = acc->size[1];
        emxEnsureCapacity_creal_T(xPerm, i);
        xPerm_data = xPerm->data;
        k = acc->size[0] * acc->size[2] * acc->size[1];
        for (i = 0; i < k; i++) {
          xPerm_data[i] = acc_data[i];
        }
      } else {
        i = acc->size[2];
        k = xPerm->size[0] * xPerm->size[1] * xPerm->size[2];
        xPerm->size[0] = acc->size[2];
        nRows = acc->size[0];
        xPerm->size[1] = acc->size[0];
        i1 = acc->size[1];
        xPerm->size[2] = acc->size[1];
        emxEnsureCapacity_creal_T(xPerm, k);
        xPerm_data = xPerm->data;
        for (k = 0; k < i; k++) {
          for (b_k = 0; b_k < i1; b_k++) {
            if (acc->size[0] - 1 >= 0) {
              subsa_idx_1 = b_k + 1;
              subsa_idx_2 = k + 1;
            }
            for (c_k = 0; c_k < nRows; c_k++) {
              xPerm_data[((subsa_idx_2 + xPerm->size[0] * c_k) +
                          xPerm->size[0] * xPerm->size[1] * (subsa_idx_1 - 1)) -
                         1] =
                  acc_data[(c_k + acc->size[0] * (subsa_idx_1 - 1)) +
                           acc->size[0] * acc->size[1] * (subsa_idx_2 - 1)];
            }
          }
        }
      }
      useRadix2 =
          ((x->size[2] > 0) && ((int)((unsigned int)x->size[2] &
                                      (unsigned int)(x->size[2] - 1)) == 0));
      k = c_FFTImplementationCallback_get(x->size[2], useRadix2, &nRows);
      c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                      sintabinv);
      if (useRadix2) {
        e_FFTImplementationCallback_r2b(xPerm, x->size[2], costab, sintab,
                                        yPerm);
        yPerm_data = yPerm->data;
      } else {
        d_FFTImplementationCallback_dob(xPerm, k, x->size[2], costab, sintab,
                                        sintabinv, yPerm);
        yPerm_data = yPerm->data;
      }
      if (nomovement(iv2, yPerm)) {
        i = y->size[0] * y->size[1] * y->size[2];
        y->size[0] = yPerm->size[1];
        y->size[1] = yPerm->size[2];
        y->size[2] = yPerm->size[0];
        emxEnsureCapacity_creal_T(y, i);
        xPerm_data = y->data;
        k = yPerm->size[1] * yPerm->size[2] * yPerm->size[0];
        for (i = 0; i < k; i++) {
          xPerm_data[i] = yPerm_data[i];
        }
      } else {
        i = yPerm->size[1];
        k = y->size[0] * y->size[1] * y->size[2];
        y->size[0] = yPerm->size[1];
        nRows = yPerm->size[2];
        y->size[1] = yPerm->size[2];
        i1 = yPerm->size[0];
        y->size[2] = yPerm->size[0];
        emxEnsureCapacity_creal_T(y, k);
        xPerm_data = y->data;
        for (k = 0; k < nRows; k++) {
          for (b_k = 0; b_k < i; b_k++) {
            if (yPerm->size[0] - 1 >= 0) {
              subsa_idx_1 = b_k + 1;
              subsa_idx_2 = k + 1;
            }
            for (c_k = 0; c_k < i1; c_k++) {
              xPerm_data[((subsa_idx_1 + y->size[0] * (subsa_idx_2 - 1)) +
                          y->size[0] * y->size[1] * c_k) -
                         1] =
                  yPerm_data[(c_k + yPerm->size[0] * (subsa_idx_1 - 1)) +
                             yPerm->size[0] * yPerm->size[1] *
                                 (subsa_idx_2 - 1)];
            }
          }
        }
      }
    }
  }
  if (guard1) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    xPerm_data = y->data;
    k = x->size[0] * x->size[1] * x->size[2];
    for (i = 0; i < k; i++) {
      xPerm_data[i].re = 0.0;
      xPerm_data[i].im = 0.0;
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  emxFree_creal_T(&yPerm);
  emxFree_creal_T(&xPerm);
  emxFree_creal_T(&acc);
}

/* End of code generation (fftn.c) */
