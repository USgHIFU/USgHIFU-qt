/*
 * PsuedoInverse.h
 *
 * Code generation for function 'PsuedoInverse'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __PSUEDOINVERSE_H__
#define __PSUEDOINVERSE_H__
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
extern void PsuedoInverse(const creal_T H[112], uint8_T focusInfo_numfocus, creal_T U[112], real_T AngleT[112]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (PsuedoInverse.h) */
