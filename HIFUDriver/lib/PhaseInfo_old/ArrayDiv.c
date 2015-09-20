/*
 * ArrayDiv.c
 *
 * Code generation for function 'ArrayDiv'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "ArrayDiv.h"
#include "ForwardMatrix.h"
#include "sum.h"
#include "PhaseInfo_emxutil.h"
#include "sin.h"
#include "cos.h"
#include "colon.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void ArrayDiv(real_T ArrayR, real_T RadiusNum, real_T AngleNum, emxArray_real_T *
              XDiv, emxArray_real_T *YDiv, real_T ZDiv_data[400], int32_T
              ZDiv_size[2], real_T DeltaS_data[400], int32_T DeltaS_size[2],
              real_T XYZVectorArrayCor_data[1200], int32_T
              XYZVectorArrayCor_size[2])
{
  boolean_T n_too_large;
  real_T bnew;
  real_T MTemp;
  int32_T n;
  real_T y_data[64];
  int32_T nm1;
  int32_T nm1d2;
  int32_T k;
  real_T kd;
  emxArray_real_T *AngleDiv;
  int32_T b_n;
  int32_T i0;
  emxArray_real_T *b;
  real_T b_y_data[20];
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
  float_colon_length(0.000125, 0.00025, 0.004875, &n, &MTemp, &bnew,
                     &n_too_large);
  if (n > 0) {
    y_data[0] = MTemp;
    if (n > 1) {
      y_data[n - 1] = bnew;
      nm1 = n - 1;
      nm1d2 = nm1 / 2;
      for (k = 1; k <= nm1d2 - 1; k++) {
        kd = (real_T)k * 0.00025;
        y_data[k] = MTemp + kd;
        y_data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == nm1) {
        y_data[nm1d2] = (MTemp + bnew) / 2.0;
      } else {
        kd = (real_T)nm1d2 * 0.00025;
        y_data[nm1d2] = MTemp + kd;
        y_data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  emxInit_real_T(&AngleDiv, 2);
  float_colon_length(0.31415926535897931, 0.31415926535897931,
                     6.2831853071795862, &b_n, &MTemp, &bnew, &n_too_large);
  i0 = AngleDiv->size[0] * AngleDiv->size[1];
  AngleDiv->size[0] = 1;
  AngleDiv->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)AngleDiv, i0, (int32_T)sizeof(real_T));
  if (b_n > 0) {
    AngleDiv->data[0] = MTemp;
    if (b_n > 1) {
      AngleDiv->data[b_n - 1] = bnew;
      nm1 = b_n - 1;
      nm1d2 = nm1 / 2;
      for (k = 1; k <= nm1d2 - 1; k++) {
        kd = (real_T)k * 0.31415926535897931;
        AngleDiv->data[k] = MTemp + kd;
        AngleDiv->data[(b_n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == nm1) {
        AngleDiv->data[nm1d2] = (MTemp + bnew) / 2.0;
      } else {
        kd = (real_T)nm1d2 * 0.31415926535897931;
        AngleDiv->data[nm1d2] = MTemp + kd;
        AngleDiv->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  emxInit_real_T(&b, 2);
  i0 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = AngleDiv->size[1];
  emxEnsureCapacity((emxArray__common *)b, i0, (int32_T)sizeof(real_T));
  nm1 = AngleDiv->size[0] * AngleDiv->size[1] - 1;
  for (i0 = 0; i0 <= nm1; i0++) {
    b->data[i0] = AngleDiv->data[i0];
  }

  b_cos(b);
  nm1 = n - 1;
  for (i0 = 0; i0 <= nm1; i0++) {
    b_y_data[i0] = y_data[i0];
  }

  i0 = XDiv->size[0] * XDiv->size[1];
  XDiv->size[0] = n;
  XDiv->size[1] = b->size[1];
  emxEnsureCapacity((emxArray__common *)XDiv, i0, (int32_T)sizeof(real_T));
  nm1 = b->size[1] - 1;
  for (i0 = 0; i0 <= nm1; i0++) {
    nm1d2 = n - 1;
    for (k = 0; k <= nm1d2; k++) {
      XDiv->data[k + XDiv->size[0] * i0] = b_y_data[k] * b->data[b->size[0] * i0];
    }
  }

  emxFree_real_T(&b);
  b_sin(AngleDiv);
  nm1 = n - 1;
  for (i0 = 0; i0 <= nm1; i0++) {
    b_y_data[i0] = y_data[i0];
  }

  i0 = YDiv->size[0] * YDiv->size[1];
  YDiv->size[0] = n;
  YDiv->size[1] = AngleDiv->size[1];
  emxEnsureCapacity((emxArray__common *)YDiv, i0, (int32_T)sizeof(real_T));
  nm1 = AngleDiv->size[1] - 1;
  for (i0 = 0; i0 <= nm1; i0++) {
    nm1d2 = n - 1;
    for (k = 0; k <= nm1d2; k++) {
      YDiv->data[k + YDiv->size[0] * i0] = b_y_data[k] * AngleDiv->data
        [AngleDiv->size[0] * i0];
    }
  }

  emxFree_real_T(&AngleDiv);
  ZDiv_size[0] = 20;
  ZDiv_size[1] = 20;
  for (i0 = 0; i0 < 400; i0++) {
    ZDiv_data[i0] = 0.0;
  }

  DeltaS_size[0] = 20;
  DeltaS_size[1] = 20;
  for (i0 = 0; i0 < 400; i0++) {
    DeltaS_data[i0] = 0.0;
  }

  MTemp = 0.0;

  /* 求DeltaS，一个阵元被分为RadiusNum*AngleNum个微元，DeltaS为微元的面积 */
  for (nm1 = 0; nm1 < 20; nm1++) {
    MTemp++;
    nm1d2 = -1;
    for (k = 0; k < 20; k++) {
      bnew = 0.00025 + (real_T)k * 0.00025;
      nm1d2++;
      if (nm1d2 + 1 == 1) {
        DeltaS_data[DeltaS_size[0] * ((int32_T)MTemp - 1)] = rt_powd_snf(bnew,
          2.0) * 3.1415926535897931 / 20.0;
      } else {
        b_DeltaS_size[0] = 20;
        for (i0 = 0; i0 < 20; i0++) {
          b_y_data[i0] = DeltaS_data[i0 + DeltaS_size[0] * ((int32_T)MTemp - 1)];
        }

        DeltaS_data[nm1d2 + DeltaS_size[0] * ((int32_T)MTemp - 1)] = rt_powd_snf
          (bnew, 2.0) * 3.1415926535897931 / 20.0 - sum(b_y_data, b_DeltaS_size);
      }
    }
  }

  /* 将XDiv,YDiv,ZDiv变成行向量,有利于后续的坐标变换的批量处理 */
  for (i0 = 0; i0 < 2; i0++) {
    XShape_size[i0] = iv1[i0];
  }

  for (k = 0; k < 400; k++) {
    XShape_data[k] = XDiv->data[k];
  }

  for (i0 = 0; i0 < 2; i0++) {
    YShape_size[i0] = iv1[i0];
  }

  for (k = 0; k < 400; k++) {
    YShape_data[k] = YDiv->data[k];
  }

  for (i0 = 0; i0 < 2; i0++) {
    ZShape_size[i0] = iv1[i0];
  }

  memset(&ZShape_data[0], 0, 400U * sizeof(real_T));
  XYZVectorArrayCor_size[0] = 3;
  XYZVectorArrayCor_size[1] = 400;
  for (i0 = 0; i0 < 400; i0++) {
    XYZVectorArrayCor_data[XYZVectorArrayCor_size[0] * i0] =
      XShape_data[XShape_size[0] * i0];
  }

  for (i0 = 0; i0 < 400; i0++) {
    XYZVectorArrayCor_data[1 + XYZVectorArrayCor_size[0] * i0] =
      YShape_data[YShape_size[0] * i0];
  }

  for (i0 = 0; i0 < 400; i0++) {
    XYZVectorArrayCor_data[2 + XYZVectorArrayCor_size[0] * i0] =
      ZShape_data[ZShape_size[0] * i0];
  }
}

/* End of code generation (ArrayDiv.c) */
