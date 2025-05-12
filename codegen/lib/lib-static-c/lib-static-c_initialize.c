/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * lib-static-c_initialize.c
 *
 * Code generation for function 'lib-static-c_initialize'
 *
 */

/* Include files */
#include "lib-static-c_initialize.h"
#include "lib-static-c_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void lib - static - c_initialize(void)
{
  omp_init_nest_lock(&lib - static - c_nestLockGlobal);
  isInitialized_lib - static - c = true;
}

/* End of code generation (lib-static-c_initialize.c) */
