/*
 * sin.c
 *
 * Code generation for function 'sin'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
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
void b_sin(emxArray_real_T *x)
{
  int32_T i9;
  int32_T k;
  i9 = x->size[1];
  for (k = 0; k <= i9 - 1; k++) {
    x->data[k] = sin(x->data[k]);
  }
}

/* End of code generation (sin.c) */
