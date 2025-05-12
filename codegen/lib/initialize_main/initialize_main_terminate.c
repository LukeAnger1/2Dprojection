/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * initialize_main_terminate.c
 *
 * Code generation for function 'initialize_main_terminate'
 *
 */

/* Include files */
#include "initialize_main_terminate.h"
#include "initialize_main_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void initialize_main_terminate(void)
{
  omp_destroy_nest_lock(&initialize_main_nestLockGlobal);
  isInitialized_initialize_main = false;
}

/* End of code generation (initialize_main_terminate.c) */
