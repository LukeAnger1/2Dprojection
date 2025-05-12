/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * static_c_terminate.c
 *
 * Code generation for function 'static_c_terminate'
 *
 */

/* Include files */
#include "static_c_terminate.h"
#include "rt_nonfinite.h"
#include "static_c_data.h"
#include "omp.h"

/* Function Definitions */
void static_c_terminate(void)
{
  omp_destroy_nest_lock(&static_c_nestLockGlobal);
  isInitialized_static_c = false;
}

/* End of code generation (static_c_terminate.c) */
