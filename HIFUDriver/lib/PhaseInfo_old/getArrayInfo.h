/*
 * getArrayInfo.h
 *
 * Code generation for function 'getArrayInfo'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __GETARRAYINFO_H__
#define __GETARRAYINFO_H__
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
extern void getArrayInfo(real_T *arrayInfo_roc, real_T *arrayInfo_radius, real_T *arrayInfo_numradius, real_T *arrayInfo_numangle, real_T arrayInfo_numringelement[4], real_T arrayInfo_anglez[4], real_T arrayInfo_anglefirstx[4], real_T *arrayInfo_numring, real_T *arrayInfo_numelement, emxArray_real_T *arrayInfo_anglexelement, emxArray_real_T *arrayInfo_anglezelement);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (getArrayInfo.h) */
