/*
 * cos.c
 *
 * Code generation for function 'cos'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
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
void b_cos(emxArray_real_T *x)
{
  int32_T i8;
  int32_T k;
  i8 = x->size[1];
  for (k = 0; k <= i8 - 1; k++) {
    x->data[k] = cos(x->data[k]);
  }
}

/* End of code generation (cos.c) */
