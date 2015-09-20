/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "rdivide.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_rdivide(const creal_T x[56], const real_T y[56], creal_T z[56])
{
  int32_T i4;
  for (i4 = 0; i4 < 56; i4++) {
    if (x[i4].im == 0.0) {
      z[i4].re = x[i4].re / y[i4];
      z[i4].im = 0.0;
    } else if (x[i4].re == 0.0) {
      z[i4].re = 0.0;
      z[i4].im = x[i4].im / y[i4];
    } else {
      z[i4].re = x[i4].re / y[i4];
      z[i4].im = x[i4].im / y[i4];
    }
  }
}

void c_rdivide(const creal_T x[112], const real_T y[112], creal_T z[112])
{
  int32_T i5;
  for (i5 = 0; i5 < 112; i5++) {
    if (x[i5].im == 0.0) {
      z[i5].re = x[i5].re / y[i5];
      z[i5].im = 0.0;
    } else if (x[i5].re == 0.0) {
      z[i5].re = 0.0;
      z[i5].im = x[i5].im / y[i5];
    } else {
      z[i5].re = x[i5].re / y[i5];
      z[i5].im = x[i5].im / y[i5];
    }
  }
}

void rdivide(const creal_T x[28], const real_T y[28], creal_T z[28])
{
  int32_T i3;
  for (i3 = 0; i3 < 28; i3++) {
    if (x[i3].im == 0.0) {
      z[i3].re = x[i3].re / y[i3];
      z[i3].im = 0.0;
    } else if (x[i3].re == 0.0) {
      z[i3].re = 0.0;
      z[i3].im = x[i3].im / y[i3];
    } else {
      z[i3].re = x[i3].re / y[i3];
      z[i3].im = x[i3].im / y[i3];
    }
  }
}

/* End of code generation (rdivide.c) */
