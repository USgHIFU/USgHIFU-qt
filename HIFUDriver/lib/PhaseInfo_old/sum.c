/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "sum.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
real_T sum(const real_T x_data[20], const int32_T x_size[1])
{
  real_T y;
  int32_T k;
  y = x_data[0];
  for (k = 0; k < 19; k++) {
    y += x_data[k + 1];
  }

  return y;
}

/* End of code generation (sum.c) */
