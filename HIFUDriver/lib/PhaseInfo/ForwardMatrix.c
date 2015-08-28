/*
 * ForwardMatrix.c
 *
 * Code generation for function 'ForwardMatrix'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "ForwardMatrix.h"
#include "repmat.h"
#include "PhaseInfo_emxutil.h"
#include "getArrayInfo.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void eml_xgemm(int32_T n, const real_T A[9], const real_T B_data[1200],
                      const int32_T B_size[2], real_T C_data[1200], int32_T
                      C_size[2]);

/* Function Definitions */
static void eml_xgemm(int32_T n, const real_T A[9], const real_T B_data[1200],
                      const int32_T B_size[2], real_T C_data[1200], int32_T
                      C_size[2])
{
  int32_T cr;
  int32_T ic;
  int32_T br;
  int32_T ar;
  int32_T ib;
  int32_T ia;
  for (cr = 0; cr < 1198; cr += 3) {
    for (ic = cr; ic + 1 <= cr + 3; ic++) {
      C_data[ic] = 0.0;
    }
  }

  br = 0;
  for (cr = 0; cr < 1198; cr += 3) {
    ar = -1;
    for (ib = br; ib + 1 <= br + 3; ib++) {
      if (B_data[ib] != 0.0) {
        ia = ar;
        for (ic = cr; ic + 1 <= cr + 3; ic++) {
          ia++;
          C_data[ic] += B_data[ib] * A[ia];
        }
      }

      ar += 3;
    }

    br += 3;
  }
}

void ForwardMatrix(const real_T XYZVectorArrayCor_data[1200], const int32_T
                   XYZVectorArrayCor_size[2], const real_T DeltaS_data[400],
                   const int32_T DeltaS_size[2], real_T focusInfo_x, real_T
                   focusInfo_y, real_T focusInfo_z, creal_T H[112],
                   emxArray_real_T *XArray, emxArray_real_T *YArray,
                   emxArray_real_T *ZArray)
{
  emxArray_real_T *arrayInfo_anglexelement;
  emxArray_real_T *arrayInfo_anglezelement;
  real_T expl_temp;
  real_T b_expl_temp;
  real_T c_expl_temp[4];
  real_T d_expl_temp[4];
  real_T e_expl_temp[4];
  real_T f_expl_temp;
  real_T theta;
  real_T phi;
  real_T r2;
  int32_T k;
  int32_T iElement;
  real_T O[3];
  real_T P1_data[1200];
  static const int16_T iv2[2] = { 3, 400 };

  int32_T P1_size[2];
  int32_T i1;
  real_T dv2[9];
  real_T dv3[9];
  static const int8_T iv3[3] = { 0, 0, 1 };

  static const int8_T iv4[3] = { 0, 1, 0 };

  real_T dv4[9];
  int32_T i2;
  real_T dv5[9];
  static const int8_T b[9] = { 0, -1, 0, 1, 0, 0, 0, 0, 1 };

  int32_T deltaO_size[2];
  real_T deltaO_data[1200];
  real_T a_data[400];
  real_T r_data[400];
  real_T tmp_data[400];
  real_T b_tmp_data[400];
  creal_T Heds_data[400];
  emxInit_real_T(&arrayInfo_anglexelement, 2);
  emxInit_real_T(&arrayInfo_anglezelement, 2);

  /*  load FocusInfo; */
  /*  ArrayInfo; */
  /*  TissueInfo; */
  getArrayInfo(&r2, &phi, &theta, &f_expl_temp, e_expl_temp, d_expl_temp,
               c_expl_temp, &b_expl_temp, &expl_temp, arrayInfo_anglexelement,
               arrayInfo_anglezelement);
  k = XArray->size[0] * XArray->size[1];
  XArray->size[0] = 112;
  XArray->size[1] = 400;
  emxEnsureCapacity((emxArray__common *)XArray, k, (int32_T)sizeof(real_T));
  for (k = 0; k < 44800; k++) {
    XArray->data[k] = 0.0;
  }

  k = YArray->size[0] * YArray->size[1];
  YArray->size[0] = 112;
  YArray->size[1] = 400;
  emxEnsureCapacity((emxArray__common *)YArray, k, (int32_T)sizeof(real_T));
  for (k = 0; k < 44800; k++) {
    YArray->data[k] = 0.0;
  }

  k = ZArray->size[0] * ZArray->size[1];
  ZArray->size[0] = 112;
  ZArray->size[1] = 400;
  emxEnsureCapacity((emxArray__common *)ZArray, k, (int32_T)sizeof(real_T));
  for (k = 0; k < 44800; k++) {
    ZArray->data[k] = 0.0;
  }

  for (k = 0; k < 112; k++) {
    H[k].re = 0.0;
    H[k].im = 0.0;
  }

  for (iElement = 0; iElement < 112; iElement++) {
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* *  时间：2006年6月14日                                                    * */
    /* *  函数目的：将任意多个点的坐标（x，y，z）转变为（X，Y，Z）                  * */
    /* *  函数输入：O为xyz坐标系的原点在XYZ坐标系的坐标表示                        * */
    /* *  续上，P为任意多个点的xyz坐标系中的三维坐标，第一行为x坐标，以此类推        * */
    /* *  函数输出，newP为P所对应的XYZ坐标系的坐标表示                             * */
    /* *  函数描述：O为球面上的点，P为任意点（以O为原点的坐标系oxyz中的坐标）        * */
    /* *  续上，newP为点P在以球心为原点的直角坐标XYZ中的表示                       * */
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* 假定球冠在XY的上部 */
    O[0] = 0.14 * sin(arrayInfo_anglezelement->data[iElement]) * cos
      (arrayInfo_anglexelement->data[iElement]);
    O[1] = 0.14 * sin(arrayInfo_anglezelement->data[iElement]) * sin
      (arrayInfo_anglexelement->data[iElement]);
    O[2] = 0.14 * cos(arrayInfo_anglezelement->data[iElement]);

    /* z轴与-O夹角 */
    theta = acos(-O[2] / sqrt((O[0] * O[0] + O[1] * O[1]) + O[2] * O[2]));
    r2 = sqrt(O[0] * O[0] + O[1] * O[1]);
    if (r2 < 1.0E-6) {
      phi = 1.5707963267948966;
    } else {
      phi = acos(-O[0] / r2);
    }

    if (-O[1] < 0.0) {
      phi = 6.2831853071795862 - phi;
    }

    /* Z轴在xoy平面的投影方向即为oy的反方向 */
    /* 以z轴为旋转轴顺时针旋转90度，使得ox轴方向与Z轴在xoy平面的投影方向平行 */
    /* 是否旋转关系不大，关键是x、y轴方向的选择 */
    /* 以当前y轴为旋转轴顺时针旋转theta，使得oz轴方向与Z轴方向平行                           */
    /* 以当前z轴为旋转轴顺时针旋转phi，使得oy轴方向与Y轴方向平行  */
    for (k = 0; k < 2; k++) {
      P1_size[k] = iv2[k];
    }

    P1_size[0] = 3;
    P1_size[1] = 400;
    for (k = 0; k < 400; k++) {
      for (i1 = 0; i1 < 3; i1++) {
        P1_data[i1 + 3 * k] = 0.0;
      }
    }

    dv2[0] = cos(phi);
    dv2[3] = -sin(phi);
    dv2[6] = 0.0;
    dv2[1] = sin(phi);
    dv2[4] = cos(phi);
    dv2[7] = 0.0;
    dv3[0] = cos(theta);
    dv3[3] = 0.0;
    dv3[6] = sin(theta);
    for (k = 0; k < 3; k++) {
      dv2[2 + 3 * k] = (real_T)iv3[k];
      dv3[1 + 3 * k] = (real_T)iv4[k];
    }

    dv3[2] = -sin(theta);
    dv3[5] = 0.0;
    dv3[8] = cos(theta);
    for (k = 0; k < 3; k++) {
      for (i1 = 0; i1 < 3; i1++) {
        dv4[k + 3 * i1] = 0.0;
        for (i2 = 0; i2 < 3; i2++) {
          dv4[k + 3 * i1] += dv2[k + 3 * i2] * dv3[i2 + 3 * i1];
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        dv5[k + 3 * i1] = 0.0;
        for (i2 = 0; i2 < 3; i2++) {
          dv5[k + 3 * i1] += dv4[k + 3 * i2] * (real_T)b[i2 + 3 * i1];
        }
      }
    }

    eml_xgemm(400, dv5, XYZVectorArrayCor_data, XYZVectorArrayCor_size, P1_data,
              P1_size);
    repmat(O, 400.0, deltaO_data, deltaO_size);
    P1_size[0] = 3;
    P1_size[1] = 400;
    for (k = 0; k < 1200; k++) {
      P1_data[k] += deltaO_data[k];
    }

    /* 平移 */
    /* 保角、保距 */
    for (k = 0; k < 400; k++) {
      XArray->data[iElement + XArray->size[0] * k] = P1_data[3 * k];
    }

    for (k = 0; k < 400; k++) {
      YArray->data[iElement + YArray->size[0] * k] = P1_data[1 + 3 * k];
    }

    for (k = 0; k < 400; k++) {
      ZArray->data[iElement + ZArray->size[0] * k] = P1_data[2 + 3 * k];
    }

    for (k = 0; k < 400; k++) {
      a_data[k] = XArray->data[iElement + XArray->size[0] * k] - focusInfo_x;
    }

    for (k = 0; k < 400; k++) {
      r_data[k] = rt_powd_snf(a_data[k], 2.0);
    }

    for (k = 0; k < 400; k++) {
      a_data[k] = YArray->data[iElement + YArray->size[0] * k] - focusInfo_y;
    }

    for (k = 0; k < 400; k++) {
      tmp_data[k] = rt_powd_snf(a_data[k], 2.0);
    }

    for (k = 0; k < 400; k++) {
      a_data[k] = ZArray->data[iElement + ZArray->size[0] * k] - focusInfo_z;
    }

    for (k = 0; k < 400; k++) {
      b_tmp_data[k] = rt_powd_snf(a_data[k], 2.0);
    }

    for (k = 0; k < 400; k++) {
      r_data[k] = (r_data[k] + tmp_data[k]) + b_tmp_data[k];
    }

    for (k = 0; k < 400; k++) {
      r_data[k] = sqrt(r_data[k]);
    }

    for (k = 0; k < 400; k++) {
      Heds_data[k].re = r_data[k] * -12.24;
      Heds_data[k].im = r_data[k] * -5446.2281821314446;
    }

    for (k = 0; k < 400; k++) {
      r2 = exp(Heds_data[k].re / 2.0);
      phi = Heds_data[k].im;
      Heds_data[k].re = r2 * (r2 * cos(Heds_data[k].im));
      Heds_data[k].im = r2 * (r2 * sin(phi));
      tmp_data[k] = DeltaS_data[k];
    }

    for (k = 0; k < 400; k++) {
      r2 = tmp_data[k] * Heds_data[k].re;
      phi = tmp_data[k] * Heds_data[k].im;
      if (phi == 0.0) {
        Heds_data[k].re = r2 / r_data[k];
        Heds_data[k].im = 0.0;
      } else if (r2 == 0.0) {
        Heds_data[k].re = 0.0;
        Heds_data[k].im = phi / r_data[k];
      } else {
        Heds_data[k].re = r2 / r_data[k];
        Heds_data[k].im = phi / r_data[k];
      }
    }

    r2 = Heds_data[0].re;
    phi = Heds_data[0].im;
    for (k = 0; k < 399; k++) {
      r2 += Heds_data[k + 1].re;
      phi += Heds_data[k + 1].im;
    }

    H[iElement].re = r2;
    H[iElement].im = phi;
  }

  emxFree_real_T(&arrayInfo_anglezelement);
  emxFree_real_T(&arrayInfo_anglexelement);
  for (k = 0; k < 112; k++) {
    r2 = H[k].re;
    phi = H[k].im;
    H[k].re = 0.0 * r2 - 1.54768E+9 * phi;
    H[k].im = 0.0 * phi + 1.54768E+9 * r2;
  }
}

/* End of code generation (ForwardMatrix.c) */
