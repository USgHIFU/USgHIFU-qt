/*
 * angle.c
 *
 * Code generation for function 'angle'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "angle.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real_T rt_atan2d_snf(real_T u0, real_T u1);

/* Function Definitions */
static real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T i6;
  int32_T i7;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u1 > 0.0) {
      i6 = 1;
    } else {
      i6 = -1;
    }

    if (u0 > 0.0) {
      i7 = 1;
    } else {
      i7 = -1;
    }

    y = atan2((real_T)i7, (real_T)i6);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

void angle(const creal_T x[28], real_T y[28])
{
  int32_T k;
  for (k = 0; k < 28; k++) {
    y[k] = rt_atan2d_snf(x[k].im, x[k].re);
  }
}

void b_angle(const creal_T x[112], real_T y[112])
{
  int32_T k;
  for (k = 0; k < 112; k++) {
    y[k] = rt_atan2d_snf(x[k].im, x[k].re);
  }
}

void c_angle(const creal_T x[56], real_T y[56])
{
  int32_T k;
  for (k = 0; k < 56; k++) {
    y[k] = rt_atan2d_snf(x[k].im, x[k].re);
  }
}

/* End of code generation (angle.c) */
