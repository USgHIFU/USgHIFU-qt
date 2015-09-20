/*
 * sin.c
 *
 * Code generation for function 'sin'
 *
 * C source code generated on: Fri Sep 11 10:56:17 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "sin.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_sin(real_T x_data[20], int32_T x_size[2])
{
  int32_T i6;
  int32_T k;
  i6 = x_size[1];
  for (k = 0; k <= i6 - 1; k++) {
    x_data[k] = sin(x_data[k]);
  }
}

/* End of code generation (sin.c) */
