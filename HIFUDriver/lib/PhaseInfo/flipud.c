/*
 * flipud.c
 *
 * Code generation for function 'flipud'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "flipud.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_flipud(creal_T x[6])
{
  int32_T i;
  real_T xtmp_re;
  real_T xtmp_im;
  for (i = 0; i < 3; i++) {
    xtmp_re = x[i].re;
    xtmp_im = x[i].im;
    x[i] = x[5 - i];
    x[5 - i].re = xtmp_re;
    x[5 - i].im = xtmp_im;
  }
}

void c_flipud(creal_T x[8])
{
  int32_T i;
  real_T xtmp_re;
  real_T xtmp_im;
  for (i = 0; i < 4; i++) {
    xtmp_re = x[i].re;
    xtmp_im = x[i].im;
    x[i] = x[7 - i];
    x[7 - i].re = xtmp_re;
    x[7 - i].im = xtmp_im;
  }
}

void d_flipud(creal_T x[9])
{
  int32_T i;
  real_T xtmp_re;
  real_T xtmp_im;
  for (i = 0; i < 4; i++) {
    xtmp_re = x[i].re;
    xtmp_im = x[i].im;
    x[i] = x[8 - i];
    x[8 - i].re = xtmp_re;
    x[8 - i].im = xtmp_im;
  }
}

void flipud(creal_T x[5])
{
  int32_T i;
  real_T xtmp_re;
  real_T xtmp_im;
  for (i = 0; i < 2; i++) {
    xtmp_re = x[i].re;
    xtmp_im = x[i].im;
    x[i] = x[4 - i];
    x[4 - i].re = xtmp_re;
    x[4 - i].im = xtmp_im;
  }
}

/* End of code generation (flipud.c) */
