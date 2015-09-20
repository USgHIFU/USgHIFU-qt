/*
 * PhaseInfo_emxutil.h
 *
 * Code generation for function 'PhaseInfo_emxutil'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __PHASEINFO_EMXUTIL_H__
#define __PHASEINFO_EMXUTIL_H__
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
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (PhaseInfo_emxutil.h) */
