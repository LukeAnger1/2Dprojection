/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * render_initialize.c
 *
 * Code generation for function 'render_initialize'
 *
 */

/* Include files */
#include "render_initialize.h"
#include "render_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void render_initialize(void)
{
  omp_init_nest_lock(&render_nestLockGlobal);
  isInitialized_render = true;
}

/* End of code generation (render_initialize.c) */
