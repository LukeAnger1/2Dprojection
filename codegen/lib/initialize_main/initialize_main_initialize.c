/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * initialize_main_initialize.c
 *
 * Code generation for function 'initialize_main_initialize'
 *
 */

/* Include files */
#include "initialize_main_initialize.h"
#include "initialize_main_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void initialize_main_initialize(void)
{
  omp_init_nest_lock(&initialize_main_nestLockGlobal);
  isInitialized_initialize_main = true;
}

/* End of code generation (initialize_main_initialize.c) */
