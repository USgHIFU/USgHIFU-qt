/*
 * ForwardMatrix.h
 *
 * Code generation for function 'ForwardMatrix'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __FORWARDMATRIX_H__
#define __FORWARDMATRIX_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "PhaseInfo_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
#ifdef __cplusplus
extern "C" {
#endif
extern void ForwardMatrix(const real_T XYZVectorArrayCor_data[1200], const int32_T XYZVectorArrayCor_size[2], const real_T DeltaS_data[400], const int32_T DeltaS_size[2], real_T focusInfo_x, real_T focusInfo_y, real_T focusInfo_z, creal_T H[112], emxArray_real_T *XArray, emxArray_real_T *YArray, emxArray_real_T *ZArray);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (ForwardMatrix.h) */
