/*
 * exp.c
 *
 * Code generation for function 'exp'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "exp.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_exp(creal_T x[28])
{
  int32_T k;
  real_T r;
  real_T x_im;
  real_T b_x_im;
  for (k = 0; k < 28; k++) {
    r = exp(x[k].re / 2.0);
    x_im = x[k].im;
    b_x_im = x[k].im;
    x[k].re = r * (r * cos(x_im));
    x[k].im = r * (r * sin(b_x_im));
  }
}

void c_exp(creal_T x[56])
{
  int32_T k;
  real_T r;
  real_T x_im;
  real_T b_x_im;
  for (k = 0; k < 56; k++) {
    r = exp(x[k].re / 2.0);
    x_im = x[k].im;
    b_x_im = x[k].im;
    x[k].re = r * (r * cos(x_im));
    x[k].im = r * (r * sin(b_x_im));
  }
}

void d_exp(creal_T x[112])
{
  int32_T k;
  real_T r;
  real_T x_im;
  real_T b_x_im;
  for (k = 0; k < 112; k++) {
    r = exp(x[k].re / 2.0);
    x_im = x[k].im;
    b_x_im = x[k].im;
    x[k].re = r * (r * cos(x_im));
    x[k].im = r * (r * sin(b_x_im));
  }
}

/* End of code generation (exp.c) */
