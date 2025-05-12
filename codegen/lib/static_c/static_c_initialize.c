/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * static_c_initialize.c
 *
 * Code generation for function 'static_c_initialize'
 *
 */

/* Include files */
#include "static_c_initialize.h"
#include "rt_nonfinite.h"
#include "static_c_data.h"
#include "omp.h"

/* Function Definitions */
void static_c_initialize(void)
{
  omp_init_nest_lock(&static_c_nestLockGlobal);
  isInitialized_static_c = true;
}

/* End of code generation (static_c_initialize.c) */
