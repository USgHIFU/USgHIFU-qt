/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "abs.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_abs(const creal_T x[28], real_T y[28])
{
  int32_T k;
  for (k = 0; k < 28; k++) {
    y[k] = rt_hypotd_snf(fabs(x[k].re), fabs(x[k].im));
  }
}

void c_abs(const creal_T x[56], real_T y[56])
{
  int32_T k;
  for (k = 0; k < 56; k++) {
    y[k] = rt_hypotd_snf(fabs(x[k].re), fabs(x[k].im));
  }
}

void d_abs(const creal_T x[112], real_T y[112])
{
  int32_T k;
  for (k = 0; k < 112; k++) {
    y[k] = rt_hypotd_snf(fabs(x[k].re), fabs(x[k].im));
  }
}

/* End of code generation (abs.c) */
