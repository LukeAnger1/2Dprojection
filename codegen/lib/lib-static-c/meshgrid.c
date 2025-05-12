/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * meshgrid.c
 *
 * Code generation for function 'meshgrid'
 *
 */

/* Include files */
#include "meshgrid.h"
#include "lib-static-c_emxutil.h"
#include "lib-static-c_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void meshgrid(const emxArray_real_T *x, const emxArray_real_T *y,
              emxArray_real_T *xx, emxArray_real_T *yy)
{
  const double *x_data;
  const double *y_data;
  double *xx_data;
  double *yy_data;
  int i;
  int j;
  int nx_tmp;
  int ny_tmp;
  y_data = y->data;
  x_data = x->data;
  nx_tmp = x->size[1];
  ny_tmp = y->size[1];
  j = xx->size[0] * xx->size[1];
  xx->size[0] = y->size[1];
  xx->size[1] = x->size[1];
  emxEnsureCapacity_real_T(xx, j);
  xx_data = xx->data;
  j = yy->size[0] * yy->size[1];
  yy->size[0] = y->size[1];
  yy->size[1] = x->size[1];
  emxEnsureCapacity_real_T(yy, j);
  yy_data = yy->data;
  if ((x->size[1] != 0) && (y->size[1] != 0)) {
    for (j = 0; j < nx_tmp; j++) {
      for (i = 0; i < ny_tmp; i++) {
        xx_data[i + xx->size[0] * j] = x_data[j];
        yy_data[i + yy->size[0] * j] = y_data[i];
      }
    }
  }
}

/* End of code generation (meshgrid.c) */
