/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * abs.c
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include "abs.h"
#include "lib-static-c_emxutil.h"
#include "lib-static-c_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  const creal_T *x_data;
  double *y_data;
  int k;
  int nx_tmp;
  x_data = x->data;
  nx_tmp = x->size[0] * x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = x->size[0];
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, k);
  y_data = y->data;
  for (k = 0; k < nx_tmp; k++) {
    double a;
    double b;
    a = fabs(x_data[k].re);
    b = fabs(x_data[k].im);
    if (a < b) {
      a /= b;
      y_data[k] = b * sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      y_data[k] = a * sqrt(b * b + 1.0);
    } else if (rtIsNaN(b)) {
      y_data[k] = rtNaN;
    } else {
      y_data[k] = a * 1.4142135623730951;
    }
  }
}

/* End of code generation (abs.c) */
