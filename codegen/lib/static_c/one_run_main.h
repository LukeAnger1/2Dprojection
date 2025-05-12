/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * one_run_main.h
 *
 * Code generation for function 'one_run_main'
 *
 */

#ifndef ONE_RUN_MAIN_H
#define ONE_RUN_MAIN_H

/* Include files */
#include "rtwtypes.h"
#include "static_c_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void one_run_main(const emxArray_real_T *realVolume,
                         const emxArray_real_T *imagVolume, double N,
                         const double pivot[3], double angle,
                         emxArray_real_T *projection);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (one_run_main.h) */
