/*
 * rdivide.h
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __RDIVIDE_H__
#define __RDIVIDE_H__
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
extern void b_rdivide(const creal_T x[56], const real_T y[56], creal_T z[56]);
extern void c_rdivide(const creal_T x[112], const real_T y[112], creal_T z[112]);
extern void rdivide(const creal_T x[28], const real_T y[28], creal_T z[28]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (rdivide.h) */
