/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ExtractSliceFromUnifiedVolume.h
 *
 * Code generation for function 'ExtractSliceFromUnifiedVolume'
 *
 */

#ifndef EXTRACTSLICEFROMUNIFIEDVOLUME_H
#define EXTRACTSLICEFROMUNIFIEDVOLUME_H

/* Include files */
#include "initialize_main_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void ExtractSliceFromUnifiedVolume(const emxArray_real_T *volume, double N,
                                   double rotationVector[3], double angle,
                                   emxArray_real_T *sliceData);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (ExtractSliceFromUnifiedVolume.h) */
