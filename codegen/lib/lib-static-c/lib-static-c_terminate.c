/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * lib-static-c_terminate.c
 *
 * Code generation for function 'lib-static-c_terminate'
 *
 */

/* Include files */
#include "lib-static-c_terminate.h"
#include "lib-static-c_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void lib - static - c_terminate(void)
{
  omp_destroy_nest_lock(&lib - static - c_nestLockGlobal);
  isInitialized_lib - static - c = false;
}

/* End of code generation (lib-static-c_terminate.c) */
