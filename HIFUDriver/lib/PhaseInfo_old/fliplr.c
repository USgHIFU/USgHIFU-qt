/*
 * fliplr.c
 *
 * Code generation for function 'fliplr'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "fliplr.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_fliplr(creal_T x[6])
{
  int32_T b_j1;
  real_T xtmp_re;
  real_T xtmp_im;
  for (b_j1 = 0; b_j1 < 3; b_j1++) {
    xtmp_re = x[b_j1].re;
    xtmp_im = x[b_j1].im;
    x[b_j1] = x[5 - b_j1];
    x[5 - b_j1].re = xtmp_re;
    x[5 - b_j1].im = xtmp_im;
  }
}

void c_fliplr(creal_T x[8])
{
  int32_T b_j1;
  real_T xtmp_re;
  real_T xtmp_im;
  for (b_j1 = 0; b_j1 < 4; b_j1++) {
    xtmp_re = x[b_j1].re;
    xtmp_im = x[b_j1].im;
    x[b_j1] = x[7 - b_j1];
    x[7 - b_j1].re = xtmp_re;
    x[7 - b_j1].im = xtmp_im;
  }
}

void d_fliplr(creal_T x[9])
{
  int32_T b_j1;
  real_T xtmp_re;
  real_T xtmp_im;
  for (b_j1 = 0; b_j1 < 4; b_j1++) {
    xtmp_re = x[b_j1].re;
    xtmp_im = x[b_j1].im;
    x[b_j1] = x[8 - b_j1];
    x[8 - b_j1].re = xtmp_re;
    x[8 - b_j1].im = xtmp_im;
  }
}

void fliplr(creal_T x[5])
{
  int32_T b_j1;
  real_T xtmp_re;
  real_T xtmp_im;
  for (b_j1 = 0; b_j1 < 2; b_j1++) {
    xtmp_re = x[b_j1].re;
    xtmp_im = x[b_j1].im;
    x[b_j1] = x[4 - b_j1];
    x[4 - b_j1].re = xtmp_re;
    x[4 - b_j1].im = xtmp_im;
  }
}

/* End of code generation (fliplr.c) */
