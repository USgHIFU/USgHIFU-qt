/*
 * getFocusInfo.c
 *
 * Code generation for function 'getFocusInfo'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "getFocusInfo.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void getFocusInfo(uint8_T NumFocus, real_T PosXFocus, real_T PosYFocus, real_T
                  PosZFocus, uint8_T *focusInfo_numfocus, real_T *focusInfo_x,
                  real_T *focusInfo_y, real_T *focusInfo_z, real_T *focusInfo_i,
                  real_T *focusInfo_p)
{
  /*  2012/09/19 */
  /*  Alpha Version */
  /*  输入焦点位置信息和声场范围 */
  /*  XFocus = PosXFocus; */
  /*  YFocus = PosYFocus; */
  /*  ZFocus = 0.14-PosZFocus; */
  *focusInfo_numfocus = NumFocus;
  *focusInfo_x = PosXFocus;
  *focusInfo_y = PosYFocus;
  *focusInfo_z = 0.14 - PosZFocus;
  *focusInfo_i = 333000.0;
  *focusInfo_p = 1.0904850535426885E+6;
}

/* End of code generation (getFocusInfo.c) */
