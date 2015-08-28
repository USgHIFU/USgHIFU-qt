/*
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "repmat.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void repmat(const real_T a[3], real_T n, real_T b_data[1200], int32_T b_size[2])
{
  int32_T ib;
  static const int16_T iv5[2] = { 3, 400 };

  int32_T jtilecol;
  int32_T ia;
  int32_T k;
  for (ib = 0; ib < 2; ib++) {
    b_size[ib] = iv5[ib];
  }

  ib = 0;
  for (jtilecol = 0; jtilecol < 400; jtilecol++) {
    ia = 0;
    for (k = 0; k < 3; k++) {
      b_data[ib] = a[ia];
      ia++;
      ib++;
    }
  }
}

/* End of code generation (repmat.c) */
