/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * render_terminate.c
 *
 * Code generation for function 'render_terminate'
 *
 */

/* Include files */
#include "render_terminate.h"
#include "render_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void render_terminate(void)
{
  omp_destroy_nest_lock(&render_nestLockGlobal);
  isInitialized_render = false;
}

/* End of code generation (render_terminate.c) */
