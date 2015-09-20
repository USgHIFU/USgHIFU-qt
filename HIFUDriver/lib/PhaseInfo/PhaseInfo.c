/*
 * PhaseInfo.c
 *
 * Code generation for function 'PhaseInfo'
 *
 * C source code generated on: Fri Sep 11 10:56:17 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "PhaseInfo_emxutil.h"
#include "PsuedoInverse.h"
#include "ForwardMatrix.h"
#include "ArrayDiv.h"
#include "getFocusInfo.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void PhaseInfo(uint8_T NumFocus, real_T PosXFocus, real_T PosYFocus, real_T
               PosZFocus, real_T Voltage[144], real_T AngleT[144])
{
  emxArray_real_T *XArray;
  emxArray_real_T *YArray;
  emxArray_real_T *ZArray;
  real_T expl_temp;
  real_T b_expl_temp;
  real_T focusInfo_z;
  real_T focusInfo_y;
  real_T focusInfo_x;
  uint8_T focusInfo_numfocus;
  int32_T XYZVectorArrayCor_size[2];
  real_T XYZVectorArrayCor_data[1200];
  int32_T DeltaS_size[2];
  real_T DeltaS_data[400];
  int32_T ZDiv_size[2];
  real_T ZDiv_data[400];
  int32_T YDiv_size[2];
  real_T YDiv_data[400];
  int32_T XDiv_size[2];
  real_T XDiv_data[400];
  creal_T H[144];
  creal_T U[144];
  int32_T k;
  emxInit_real_T(&XArray, 2);
  emxInit_real_T(&YArray, 2);
  emxInit_real_T(&ZArray, 2);

  /*  2012/09/19 */
  /*  Alpha Version */
  /*  AngleT为变换后的相位 */
  /* format long; */
  /*  TissueInfo; */
  /*  ArrayInfo; */
  /*  FocusInfo; */
  getFocusInfo(NumFocus, PosXFocus, PosYFocus, PosZFocus, &focusInfo_numfocus,
               &focusInfo_x, &focusInfo_y, &focusInfo_z, &b_expl_temp,
               &expl_temp);

  /*  [XDiv YDiv ZDiv DeltaS XYZVectorArrayCor] = ArrayDiv(ElementR,NumRadius,NumAngle); */
  ArrayDiv(0.005, 20.0, 20.0, XDiv_data, XDiv_size, YDiv_data, YDiv_size,
           ZDiv_data, ZDiv_size, DeltaS_data, DeltaS_size,
           XYZVectorArrayCor_data, XYZVectorArrayCor_size);
  ForwardMatrix(XYZVectorArrayCor_data, XYZVectorArrayCor_size, DeltaS_data,
                DeltaS_size, focusInfo_x, focusInfo_y, focusInfo_z, H, XArray,
                YArray, ZArray);
  PsuedoInverse(H, focusInfo_numfocus, U, AngleT);
  emxFree_real_T(&ZArray);
  emxFree_real_T(&YArray);
  emxFree_real_T(&XArray);
  for (k = 0; k < 144; k++) {
    Voltage[k] = rt_hypotd_snf(fabs(U[k].re), fabs(U[k].im));
  }
}

/* End of code generation (PhaseInfo.c) */
