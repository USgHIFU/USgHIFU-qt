/*
 * cos.c
 *
 * Code generation for function 'cos'
 *
 * C source code generated on: Fri Sep 11 10:56:17 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "cos.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_cos(real_T x_data[20], int32_T x_size[2])
{
  int32_T i5;
  int32_T k;
  i5 = x_size[1];
  for (k = 0; k <= i5 - 1; k++) {
    x_data[k] = cos(x_data[k]);
  }
}

/* End of code generation (cos.c) */
