/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ifft2.c
 *
 * Code generation for function 'ifft2'
 *
 */

/* Include files */
#include "ifft2.h"
#include "FFTImplementationCallback.h"
#include "render_emxutil.h"
#include "render_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ifft2(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *acc;
  emxArray_creal_T *xPerm;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *acc_data;
  creal_T *xPerm_data;
  int lens[2];
  int i;
  int i1;
  int k;
  int nRows;
  bool guard1;
  lens[0] = x->size[0];
  lens[1] = x->size[1];
  emxInit_creal_T(&acc, 2);
  emxInit_creal_T(&xPerm, 2);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    guard1 = true;
  } else {
    bool exitg1;
    bool useRadix2;
    useRadix2 = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
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
      useRadix2 =
          ((x->size[0] > 0) && ((int)((unsigned int)x->size[0] &
                                      (unsigned int)(x->size[0] - 1)) == 0));
      k = c_FFTImplementationCallback_get(x->size[0], useRadix2, &nRows);
      d_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                      sintabinv);
      if (useRadix2) {
        f_FFTImplementationCallback_r2b(x, x->size[0], costab, sintab, acc);
        acc_data = acc->data;
      } else {
        e_FFTImplementationCallback_dob(x, k, x->size[0], costab, sintab,
                                        sintabinv, acc);
        acc_data = acc->data;
      }
      k = acc->size[1];
      i = xPerm->size[0] * xPerm->size[1];
      xPerm->size[0] = acc->size[1];
      nRows = acc->size[0];
      xPerm->size[1] = acc->size[0];
      emxEnsureCapacity_creal_T(xPerm, i);
      xPerm_data = xPerm->data;
      for (i = 0; i < nRows; i++) {
        for (i1 = 0; i1 < k; i1++) {
          xPerm_data[i1 + xPerm->size[0] * i] = acc_data[i + acc->size[0] * i1];
        }
      }
      useRadix2 =
          ((x->size[1] > 0) && ((int)((unsigned int)x->size[1] &
                                      (unsigned int)(x->size[1] - 1)) == 0));
      k = c_FFTImplementationCallback_get(x->size[1], useRadix2, &nRows);
      d_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                      sintabinv);
      if (useRadix2) {
        f_FFTImplementationCallback_r2b(xPerm, x->size[1], costab, sintab, acc);
        acc_data = acc->data;
      } else {
        e_FFTImplementationCallback_dob(xPerm, k, x->size[1], costab, sintab,
                                        sintabinv, acc);
        acc_data = acc->data;
      }
      k = acc->size[1];
      i = y->size[0] * y->size[1];
      y->size[0] = acc->size[1];
      nRows = acc->size[0];
      y->size[1] = acc->size[0];
      emxEnsureCapacity_creal_T(y, i);
      xPerm_data = y->data;
      for (i = 0; i < nRows; i++) {
        for (i1 = 0; i1 < k; i1++) {
          xPerm_data[i1 + y->size[0] * i] = acc_data[i + acc->size[0] * i1];
        }
      }
    }
  }
  if (guard1) {
    i = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    xPerm_data = y->data;
    k = x->size[0] * x->size[1];
    for (i = 0; i < k; i++) {
      xPerm_data[i].re = 0.0;
      xPerm_data[i].im = 0.0;
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  emxFree_creal_T(&xPerm);
  emxFree_creal_T(&acc);
}

/* End of code generation (ifft2.c) */
