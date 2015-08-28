/*
 * ArrayDiv.h
 *
 * Code generation for function 'ArrayDiv'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __ARRAYDIV_H__
#define __ARRAYDIV_H__
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
extern void ArrayDiv(real_T ArrayR, real_T RadiusNum, real_T AngleNum, emxArray_real_T *XDiv, emxArray_real_T *YDiv, real_T ZDiv_data[400], int32_T ZDiv_size[2], real_T DeltaS_data[400], int32_T DeltaS_size[2], real_T XYZVectorArrayCor_data[1200], int32_T XYZVectorArrayCor_size[2]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (ArrayDiv.h) */
