/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fftshift.h
 *
 * Code generation for function 'fftshift'
 *
 */

#ifndef FFTSHIFT_H
#define FFTSHIFT_H

/* Include files */
#include "rtwtypes.h"
#include "static_c_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_fftshift(emxArray_creal_T *x);

void c_fftshift(emxArray_real_T *x);

void fftshift(emxArray_real_T *x);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (fftshift.h) */
