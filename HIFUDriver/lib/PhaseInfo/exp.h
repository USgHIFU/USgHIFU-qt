/*
 * exp.h
 *
 * Code generation for function 'exp'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __EXP_H__
#define __EXP_H__
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
extern void b_exp(creal_T x[28]);
extern void c_exp(creal_T x[56]);
extern void d_exp(creal_T x[112]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (exp.h) */
