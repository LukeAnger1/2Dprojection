/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * libstatic_c_terminate.c
 *
 * Code generation for function 'libstatic_c_terminate'
 *
 */

/* Include files */
#include "libstatic_c_terminate.h"
#include "libstatic_c_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void libstatic_c_terminate(void)
{
  omp_destroy_nest_lock(&libstatic_c_nestLockGlobal);
  isInitialized_libstatic_c = false;
}

/* End of code generation (libstatic_c_terminate.c) */
