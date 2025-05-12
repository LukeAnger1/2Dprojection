/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * meshgrid.h
 *
 * Code generation for function 'meshgrid'
 *
 */

#ifndef MESHGRID_H
#define MESHGRID_H

/* Include files */
#include "libstatic_c_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void meshgrid(const emxArray_real_T *x, const emxArray_real_T *y,
              emxArray_real_T *xx, emxArray_real_T *yy);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (meshgrid.h) */
