/*
 * abs.h
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __ABS_H__
#define __ABS_H__
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
extern void b_abs(const creal_T x[28], real_T y[28]);
extern void c_abs(const creal_T x[56], real_T y[56]);
extern void d_abs(const creal_T x[112], real_T y[112]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (abs.h) */
