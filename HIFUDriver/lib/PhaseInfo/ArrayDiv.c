/*
 * ArrayDiv.c
 *
 * Code generation for function 'ArrayDiv'
 *
 * C source code generated on: Fri Sep 11 10:56:17 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "ArrayDiv.h"
#include "ForwardMatrix.h"
#include "sum.h"
#include "sin.h"
#include "cos.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void ArrayDiv(real_T ArrayR, real_T RadiusNum, real_T AngleNum, real_T
              XDiv_data[400], int32_T XDiv_size[2], real_T YDiv_data[400],
              int32_T YDiv_size[2], real_T ZDiv_data[400], int32_T ZDiv_size[2],
              real_T DeltaS_data[400], int32_T DeltaS_size[2], real_T
              XYZVectorArrayCor_data[1200], int32_T XYZVectorArrayCor_size[2])
{
  real_T RadiusDiv_data[20];
  int8_T RadiusDiv_size[2];
  int32_T k;
  static const int8_T iv0[2] = { 1, 20 };

  real_T MTemp;
  real_T AngleDiv_data[20];
  int32_T AngleDiv_size[2];
  int32_T b_size[2];
  int32_T NTemp;
  real_T b_data[20];
  int32_T RadiusTemp;
  int32_T i0;
  real_T b_RadiusTemp;
  real_T b_DeltaS_data[20];
  int32_T b_DeltaS_size[1];
  int16_T XShape_size[2];
  static const int16_T iv1[2] = { 1, 400 };

  real_T XShape_data[400];
  int16_T YShape_size[2];
  real_T YShape_data[400];
  int16_T ZShape_size[2];
  real_T ZShape_data[400];

  /* ************************************************************************** */
  /* **************************************************************************    */
  /* *  时间:2006年6月14日                                                     *    */
  /* *  函数目的:将每个阵元离散化,求每个微元的的面积和XYZ坐标                     * */
  /* *  函数输入:ArrayR表示阵元半径                                             * */
  /* *  续上,RadiusNum表示半径的份数，AngleNum表示角度的份数                     *                     */
  /* *  函数输出:DeltaS表示阵元每份微元的面积                                    *  */
  /* *  续上, XDiv，YDiv，ZDiv分别表示阵元坐标系阵元上微元的XYZ坐标               * */
  /* *  XYZVectorArrayCor表示阵元坐标系中每个阵元RadiusNum*AngleNum个微元        * */
  /* *  续上,的XYZ坐标,矩阵中第一行代表X坐标,第二行代表Y向量,第三行代表Z向量       * */
  /* ************************************************************************** */
  /* ************************************************************************** */
  /* XDiv,YDiv,ZDiv为RadiusNum*AngleNum维 */
  for (k = 0; k < 2; k++) {
    RadiusDiv_size[k] = iv0[k];
  }

  RadiusDiv_data[0] = 0.000125;
  RadiusDiv_data[19] = 0.004875;
  for (k = 0; k < 8; k++) {
    MTemp = ((real_T)k + 1.0) * 0.00025;
    RadiusDiv_data[k + 1] = 0.000125 + MTemp;
    RadiusDiv_data[18 - k] = 0.004875 - MTemp;
  }

  RadiusDiv_data[9] = 0.0023750000000000004;
  RadiusDiv_data[10] = 0.0026249999999999997;
  for (k = 0; k < 2; k++) {
    AngleDiv_size[k] = iv0[k];
  }

  AngleDiv_data[0] = 0.31415926535897931;
  AngleDiv_data[19] = 6.2831853071795862;
  for (k = 0; k < 8; k++) {
    MTemp = ((real_T)k + 1.0) * 0.31415926535897931;
    AngleDiv_data[k + 1] = 0.31415926535897931 + MTemp;
    AngleDiv_data[18 - k] = 6.2831853071795862 - MTemp;
  }

  AngleDiv_data[9] = 3.1415926535897931;
  AngleDiv_data[10] = 3.4557519189487724;
  b_size[0] = 1;
  b_size[1] = AngleDiv_size[1];
  NTemp = AngleDiv_size[0] * AngleDiv_size[1] - 1;
  for (k = 0; k <= NTemp; k++) {
    b_data[k] = AngleDiv_data[k];
  }

  b_cos(b_data, b_size);
  XDiv_size[0] = RadiusDiv_size[1];
  XDiv_size[1] = b_size[1];
  NTemp = b_size[1] - 1;
  for (k = 0; k <= NTemp; k++) {
    RadiusTemp = RadiusDiv_size[1] - 1;
    for (i0 = 0; i0 <= RadiusTemp; i0++) {
      XDiv_data[i0 + XDiv_size[0] * k] = RadiusDiv_data[i0] * b_data[b_size[0] *
        k];
    }
  }

  b_sin(AngleDiv_data, AngleDiv_size);
  YDiv_size[0] = RadiusDiv_size[1];
  YDiv_size[1] = AngleDiv_size[1];
  NTemp = AngleDiv_size[1] - 1;
  for (k = 0; k <= NTemp; k++) {
    RadiusTemp = RadiusDiv_size[1] - 1;
    for (i0 = 0; i0 <= RadiusTemp; i0++) {
      YDiv_data[i0 + YDiv_size[0] * k] = RadiusDiv_data[i0] *
        AngleDiv_data[AngleDiv_size[0] * k];
    }
  }

  ZDiv_size[0] = 20;
  ZDiv_size[1] = 20;
  DeltaS_size[0] = 20;
  DeltaS_size[1] = 20;
  for (k = 0; k < 400; k++) {
    ZDiv_data[k] = 0.0;
    DeltaS_data[k] = 0.0;
  }

  MTemp = 0.0;

  /* 求DeltaS，一个阵元被分为RadiusNum*AngleNum个微元，DeltaS为微元的面积 */
  for (k = 0; k < 20; k++) {
    MTemp++;
    NTemp = -1;
    for (RadiusTemp = 0; RadiusTemp < 20; RadiusTemp++) {
      b_RadiusTemp = 0.00025 + (real_T)RadiusTemp * 0.00025;
      NTemp++;
      if (NTemp + 1 == 1) {
        DeltaS_data[20 * ((int32_T)MTemp - 1)] = rt_powd_snf(b_RadiusTemp, 2.0) *
          3.1415926535897931 / 20.0;
      } else {
        b_DeltaS_size[0] = 20;
        memcpy(&b_DeltaS_data[0], &DeltaS_data[20 * ((int32_T)MTemp - 1)], 20U *
               sizeof(real_T));
        DeltaS_data[NTemp + 20 * ((int32_T)MTemp - 1)] = rt_powd_snf
          (b_RadiusTemp, 2.0) * 3.1415926535897931 / 20.0 - sum(b_DeltaS_data,
          b_DeltaS_size);
      }
    }
  }

  /* 将XDiv,YDiv,ZDiv变成行向量,有利于后续的坐标变换的批量处理 */
  for (k = 0; k < 2; k++) {
    XShape_size[k] = iv1[k];
  }

  memcpy(&XShape_data[0], &XDiv_data[0], 400U * sizeof(real_T));
  for (k = 0; k < 2; k++) {
    YShape_size[k] = iv1[k];
  }

  memcpy(&YShape_data[0], &YDiv_data[0], 400U * sizeof(real_T));
  for (k = 0; k < 2; k++) {
    ZShape_size[k] = iv1[k];
  }

  memset(&ZShape_data[0], 0, 400U * sizeof(real_T));
  XYZVectorArrayCor_size[0] = 3;
  XYZVectorArrayCor_size[1] = 400;
  for (k = 0; k < 400; k++) {
    XYZVectorArrayCor_data[3 * k] = XShape_data[XShape_size[0] * k];
  }

  for (k = 0; k < 400; k++) {
    XYZVectorArrayCor_data[1 + 3 * k] = YShape_data[YShape_size[0] * k];
  }

  for (k = 0; k < 400; k++) {
    XYZVectorArrayCor_data[2 + 3 * k] = ZShape_data[ZShape_size[0] * k];
  }
}

/* End of code generation (ArrayDiv.c) */
