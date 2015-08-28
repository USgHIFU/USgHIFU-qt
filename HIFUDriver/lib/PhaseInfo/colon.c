/*
 * colon.c
 *
 * Code generation for function 'colon'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "colon.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void float_colon_length(real_T a, real_T d, real_T b, int32_T *n, real_T *anew,
  real_T *bnew, boolean_T *n_too_large)
{
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  if (b < a) {
    *n = 0;
    *anew = a;
    *bnew = b;
    *n_too_large = FALSE;
  } else {
    *anew = a;
    ndbl = floor((b - a) / d + 0.5);
    *bnew = a + ndbl * d;
    cdiff = *bnew - b;
    absa = fabs(a);
    absb = fabs(b);
    if (absa > absb) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      *bnew = b;
    } else if (cdiff > 0.0) {
      *bnew = a + (ndbl - 1.0) * d;
    } else {
      ndbl++;
    }

    *n_too_large = FALSE;
    if (ndbl >= 0.0) {
      *n = (int32_T)ndbl;
    } else {
      *n = 0;
    }
  }
}

/* End of code generation (colon.c) */
