/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * permute.c
 *
 * Code generation for function 'permute'
 *
 */

/* Include files */
#include "permute.h"
#include "libstatic_c_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
bool nomovement(const int perm[3], const emxArray_creal_T *a)
{
  bool b;
  b = true;
  if ((a->size[0] != 0) && (a->size[1] != 0) && (a->size[2] != 0)) {
    int k;
    int plast;
    bool exitg1;
    plast = 0;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 3)) {
      if (a->size[perm[k] - 1] != 1) {
        if (plast > perm[k]) {
          b = false;
          exitg1 = true;
        } else {
          plast = perm[k];
          k++;
        }
      } else {
        k++;
      }
    }
  }
  return b;
}

/* End of code generation (permute.c) */
