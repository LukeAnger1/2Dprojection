/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "initialize_main.h"
#include "one_run_main.h"
#include "render_emxAPI.h"
#include "render_terminate.h"
#include "render_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_1x3_real_T(double result[3]);

static double argInit_real_T(void);

static emxArray_real_T *c_argInit_UnboundedxUnboundedxU(void);

/* Function Definitions */
static void argInit_1x3_real_T(double result[3])
{
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 3; idx1++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

static double argInit_real_T(void)
{
  return 0.0;
}

static emxArray_real_T *c_argInit_UnboundedxUnboundedxU(void)
{
  emxArray_real_T *result;
  double *result_data;
  int iv[3] = {2, 2, 2};
  int idx0;
  int idx1;
  int idx2;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_real_T(3, &iv[0]);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      for (idx2 = 0; idx2 < result->size[2U]; idx2++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result_data[(idx0 + result->size[0] * idx1) +
                    result->size[0] * result->size[1] * idx2] =
            argInit_real_T();
      }
    }
  }
  return result;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_initialize_main();
  main_one_run_main();
  /* Terminate the application.
You do not need to do this more than one time. */
  render_terminate();
  return 0;
}

void main_initialize_main(void)
{
  emxArray_real_T *imagVolume;
  emxArray_real_T *realVolume;
  /* Initialize function 'initialize_main' input arguments. */
  /* Call the entry-point 'initialize_main'. */
  emxInitArray_real_T(&realVolume, 3);
  emxInitArray_real_T(&imagVolume, 3);
  initialize_main(argInit_real_T(), realVolume, imagVolume);
  emxDestroyArray_real_T(realVolume);
  emxDestroyArray_real_T(imagVolume);
}

void main_one_run_main(void)
{
  emxArray_real_T *imagVolume;
  emxArray_real_T *projection;
  emxArray_real_T *realVolume;
  double dv[3];
  double N_tmp;
  /* Initialize function 'one_run_main' input arguments. */
  /* Initialize function input argument 'realVolume'. */
  realVolume = c_argInit_UnboundedxUnboundedxU();
  /* Initialize function input argument 'imagVolume'. */
  imagVolume = c_argInit_UnboundedxUnboundedxU();
  N_tmp = argInit_real_T();
  /* Initialize function input argument 'pivot'. */
  /* Call the entry-point 'one_run_main'. */
  emxInitArray_real_T(&projection, 2);
  argInit_1x3_real_T(dv);
  one_run_main(realVolume, imagVolume, N_tmp, dv, N_tmp, projection);
  emxDestroyArray_real_T(imagVolume);
  emxDestroyArray_real_T(realVolume);
  emxDestroyArray_real_T(projection);
}

/* End of code generation (main.c) */
