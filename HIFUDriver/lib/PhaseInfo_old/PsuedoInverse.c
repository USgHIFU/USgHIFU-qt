/*
 * PsuedoInverse.c
 *
 * Code generation for function 'PsuedoInverse'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "PsuedoInverse.h"
#include "round.h"
#include "angle.h"
#include "flipud.h"
#include "exp.h"
#include "rdivide.h"
#include "abs.h"
#include "fliplr.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void PsuedoInverse(const creal_T H[112], uint8_T focusInfo_numfocus, creal_T U
                   [112], real_T AngleT[112])
{
  real_T dv6[112];
  creal_T b_H[112];
  creal_T b[112];
  int32_T i;
  real_T AmpU_re;
  real_T AmpU_im;
  real_T brm;
  real_T bim;
  real_T s;
  real_T dv7[112];
  creal_T c_H[56];
  creal_T d_H[56];
  creal_T H_plane[56];
  real_T dv8[56];
  creal_T b_H_plane[56];
  creal_T U1[56];
  real_T dv9[56];
  creal_T U2[56];
  creal_T dcv0[5];
  creal_T dcv1[6];
  creal_T dcv2[8];
  creal_T dcv3[9];
  creal_T dcv4[5];
  creal_T dcv5[6];
  creal_T dcv6[8];
  creal_T dcv7[9];
  creal_T e_H[28];
  creal_T dcv8[28];
  creal_T f_H[28];
  creal_T dcv9[28];
  creal_T c_H_plane[28];
  real_T dv10[28];
  creal_T d_H_plane[28];
  creal_T b_U1[28];
  real_T dv11[28];
  creal_T b_U2[28];
  creal_T U21[5];
  creal_T U22[6];
  creal_T U23[8];
  creal_T U24[9];

  /* ************************************************************************** */
  /* ************************************************************************** */
  /* *  时间：2006年6月14日                                                    * */
  /* *  函数目的：通过特征向量法求出控制点声压向量PControl                       * */
  /* *  续上，算出H矩阵的伪逆HPlus，通过伪逆算法求出激励向量U                    * */
  /* *  函数输入：H矩阵，控制点未处理声压向量                                   * */
  /* *  函数输出：阵元激励向量U，控制点声压向量PControl                         * */
  /* *           以及近场增益G                                                * */
  /* ************************************************************************** */
  /* ************************************************************************** */
  /*  load FocusInfo; */
  switch (focusInfo_numfocus) {
   case 1:
    /* 第二种计算相位的方法 */
    d_abs(H, dv6);
    c_rdivide(H, dv6, b_H);
    for (i = 0; i < 112; i++) {
      b[i].re = b_H[i].re;
      b[i].im = -b_H[i].im;
    }

    AmpU_re = 0.0;
    AmpU_im = 0.0;
    for (i = 0; i < 112; i++) {
      AmpU_re += H[i].re * b[i].re - H[i].im * b[i].im;
      AmpU_im += H[i].re * b[i].im + H[i].im * b[i].re;
    }

    if (AmpU_im == 0.0) {
      AmpU_re = 1.0904850535426885E+6 / AmpU_re;
      AmpU_im = 0.0;
    } else if (AmpU_re == 0.0) {
      AmpU_re = 0.0;
      AmpU_im = -(1.0904850535426885E+6 / AmpU_im);
    } else {
      brm = fabs(AmpU_re);
      bim = fabs(AmpU_im);
      if (brm > bim) {
        s = AmpU_im / AmpU_re;
        bim = AmpU_re + s * AmpU_im;
        AmpU_re = (1.0904850535426885E+6 + s * 0.0) / bim;
        AmpU_im = (0.0 - s * 1.0904850535426885E+6) / bim;
      } else if (bim == brm) {
        bim = AmpU_re > 0.0 ? 0.5 : -0.5;
        s = AmpU_im > 0.0 ? 0.5 : -0.5;
        AmpU_re = 1.0904850535426885E+6 * bim / brm;
        AmpU_im = (-0.0 - 1.0904850535426885E+6 * s) / brm;
      } else {
        s = AmpU_re / AmpU_im;
        bim = AmpU_im + s * AmpU_re;
        AmpU_re = s * 1.0904850535426885E+6 / bim;
        AmpU_im = (s * 0.0 - 1.0904850535426885E+6) / bim;
      }
    }

    for (i = 0; i < 112; i++) {
      b_H[i].re = H[i].re;
      b_H[i].im = -H[i].im;
    }

    b_angle(b_H, dv7);
    for (i = 0; i < 112; i++) {
      U[i].re = dv7[i] * 0.0;
      U[i].im = dv7[i];
    }

    d_exp(U);
    for (i = 0; i < 112; i++) {
      bim = U[i].re;
      s = U[i].im;
      U[i].re = AmpU_re * U[i].re - AmpU_im * U[i].im;
      U[i].im = AmpU_re * s + AmpU_im * bim;
    }
    break;

   case 2:
    /* 双焦点 */
    memcpy(&c_H[0], &H[0], 10U * sizeof(creal_T));
    memcpy(&c_H[10], &H[20], 12U * sizeof(creal_T));
    memcpy(&c_H[22], &H[44], sizeof(creal_T) << 4);
    memcpy(&c_H[38], &H[76], 18U * sizeof(creal_T));
    memcpy(&d_H[0], &H[10], 10U * sizeof(creal_T));
    memcpy(&d_H[10], &H[32], 12U * sizeof(creal_T));
    memcpy(&d_H[22], &H[60], sizeof(creal_T) << 4);
    memcpy(&d_H[38], &H[94], 18U * sizeof(creal_T));
    for (i = 0; i < 56; i++) {
      H_plane[i].re = c_H[i].re - d_H[i].re;
      H_plane[i].im = c_H[i].im - d_H[i].im;
    }

    c_abs(H_plane, dv8);
    b_rdivide(H_plane, dv8, b_H_plane);
    for (i = 0; i < 56; i++) {
      U1[i].re = b_H_plane[i].re;
      U1[i].im = -b_H_plane[i].im;
    }

    AmpU_re = 0.0;
    AmpU_im = 0.0;
    for (i = 0; i < 56; i++) {
      AmpU_re += H_plane[i].re * U1[i].re - H_plane[i].im * U1[i].im;
      AmpU_im += H_plane[i].re * U1[i].im + H_plane[i].im * U1[i].re;
    }

    if (AmpU_im == 0.0) {
      AmpU_re = 1.0904850535426885E+6 / AmpU_re;
      AmpU_im = 0.0;
    } else if (AmpU_re == 0.0) {
      AmpU_re = 0.0;
      AmpU_im = -(1.0904850535426885E+6 / AmpU_im);
    } else {
      brm = fabs(AmpU_re);
      bim = fabs(AmpU_im);
      if (brm > bim) {
        s = AmpU_im / AmpU_re;
        bim = AmpU_re + s * AmpU_im;
        AmpU_re = (1.0904850535426885E+6 + s * 0.0) / bim;
        AmpU_im = (0.0 - s * 1.0904850535426885E+6) / bim;
      } else if (bim == brm) {
        bim = AmpU_re > 0.0 ? 0.5 : -0.5;
        s = AmpU_im > 0.0 ? 0.5 : -0.5;
        AmpU_re = 1.0904850535426885E+6 * bim / brm;
        AmpU_im = (-0.0 - 1.0904850535426885E+6 * s) / brm;
      } else {
        s = AmpU_re / AmpU_im;
        bim = AmpU_im + s * AmpU_re;
        AmpU_re = s * 1.0904850535426885E+6 / bim;
        AmpU_im = (s * 0.0 - 1.0904850535426885E+6) / bim;
      }
    }

    for (i = 0; i < 56; i++) {
      b_H_plane[i].re = H_plane[i].re;
      b_H_plane[i].im = -H_plane[i].im;
    }

    c_angle(b_H_plane, dv9);
    for (i = 0; i < 56; i++) {
      U1[i].re = dv9[i] * 0.0;
      U1[i].im = dv9[i];
    }

    c_exp(U1);
    for (i = 0; i < 56; i++) {
      bim = U1[i].re;
      s = U1[i].im;
      U1[i].re = AmpU_re * U1[i].re - AmpU_im * U1[i].im;
      U1[i].im = AmpU_re * s + AmpU_im * bim;
      U2[i].re = -U1[i].re;
      U2[i].im = -U1[i].im;
    }

    memcpy(&U[0], &U1[0], 10U * sizeof(creal_T));
    memcpy(&U[10], &U2[0], 10U * sizeof(creal_T));
    memcpy(&U[20], &U1[10], 12U * sizeof(creal_T));
    memcpy(&U[32], &U2[10], 12U * sizeof(creal_T));
    memcpy(&U[44], &U1[22], sizeof(creal_T) << 4);
    memcpy(&U[60], &U2[22], sizeof(creal_T) << 4);
    memcpy(&U[76], &U1[38], 18U * sizeof(creal_T));
    memcpy(&U[94], &U2[38], 18U * sizeof(creal_T));
    break;

   case 4:
    /* 四焦点 */
    memcpy(&dcv0[0], &H[5], 5U * sizeof(creal_T));
    fliplr(dcv0);
    memcpy(&dcv1[0], &H[26], 6U * sizeof(creal_T));
    b_fliplr(dcv1);
    memcpy(&dcv2[0], &H[52], sizeof(creal_T) << 3);
    c_fliplr(dcv2);
    memcpy(&dcv3[0], &H[85], 9U * sizeof(creal_T));
    d_fliplr(dcv3);
    memcpy(&dcv4[0], &H[15], 5U * sizeof(creal_T));
    fliplr(dcv4);
    memcpy(&dcv5[0], &H[38], 6U * sizeof(creal_T));
    b_fliplr(dcv5);
    memcpy(&dcv6[0], &H[68], sizeof(creal_T) << 3);
    c_fliplr(dcv6);
    memcpy(&dcv7[0], &H[103], 9U * sizeof(creal_T));
    d_fliplr(dcv7);
    memcpy(&e_H[0], &H[0], 5U * sizeof(creal_T));
    memcpy(&e_H[5], &H[20], 6U * sizeof(creal_T));
    memcpy(&e_H[11], &H[44], sizeof(creal_T) << 3);
    memcpy(&e_H[19], &H[76], 9U * sizeof(creal_T));
    memcpy(&dcv8[0], &dcv0[0], 5U * sizeof(creal_T));
    memcpy(&dcv8[5], &dcv1[0], 6U * sizeof(creal_T));
    memcpy(&dcv8[11], &dcv2[0], sizeof(creal_T) << 3);
    memcpy(&dcv8[19], &dcv3[0], 9U * sizeof(creal_T));
    memcpy(&f_H[0], &H[10], 5U * sizeof(creal_T));
    memcpy(&f_H[5], &H[32], 6U * sizeof(creal_T));
    memcpy(&f_H[11], &H[60], sizeof(creal_T) << 3);
    memcpy(&f_H[19], &H[94], 9U * sizeof(creal_T));
    memcpy(&dcv9[0], &dcv4[0], 5U * sizeof(creal_T));
    memcpy(&dcv9[5], &dcv5[0], 6U * sizeof(creal_T));
    memcpy(&dcv9[11], &dcv6[0], sizeof(creal_T) << 3);
    memcpy(&dcv9[19], &dcv7[0], 9U * sizeof(creal_T));
    for (i = 0; i < 28; i++) {
      c_H_plane[i].re = ((e_H[i].re - dcv8[i].re) + f_H[i].re) - dcv9[i].re;
      c_H_plane[i].im = ((e_H[i].im - dcv8[i].im) + f_H[i].im) - dcv9[i].im;
    }

    b_abs(c_H_plane, dv10);
    rdivide(c_H_plane, dv10, d_H_plane);
    for (i = 0; i < 28; i++) {
      b_U1[i].re = d_H_plane[i].re;
      b_U1[i].im = -d_H_plane[i].im;
    }

    AmpU_re = 0.0;
    AmpU_im = 0.0;
    for (i = 0; i < 28; i++) {
      AmpU_re += c_H_plane[i].re * b_U1[i].re - c_H_plane[i].im * b_U1[i].im;
      AmpU_im += c_H_plane[i].re * b_U1[i].im + c_H_plane[i].im * b_U1[i].re;
    }

    if (AmpU_im == 0.0) {
      AmpU_re = 1.0904850535426885E+6 / AmpU_re;
      AmpU_im = 0.0;
    } else if (AmpU_re == 0.0) {
      AmpU_re = 0.0;
      AmpU_im = -(1.0904850535426885E+6 / AmpU_im);
    } else {
      brm = fabs(AmpU_re);
      bim = fabs(AmpU_im);
      if (brm > bim) {
        s = AmpU_im / AmpU_re;
        bim = AmpU_re + s * AmpU_im;
        AmpU_re = (1.0904850535426885E+6 + s * 0.0) / bim;
        AmpU_im = (0.0 - s * 1.0904850535426885E+6) / bim;
      } else if (bim == brm) {
        bim = AmpU_re > 0.0 ? 0.5 : -0.5;
        s = AmpU_im > 0.0 ? 0.5 : -0.5;
        AmpU_re = 1.0904850535426885E+6 * bim / brm;
        AmpU_im = (-0.0 - 1.0904850535426885E+6 * s) / brm;
      } else {
        s = AmpU_re / AmpU_im;
        bim = AmpU_im + s * AmpU_re;
        AmpU_re = s * 1.0904850535426885E+6 / bim;
        AmpU_im = (s * 0.0 - 1.0904850535426885E+6) / bim;
      }
    }

    for (i = 0; i < 28; i++) {
      d_H_plane[i].re = c_H_plane[i].re;
      d_H_plane[i].im = -c_H_plane[i].im;
    }

    angle(d_H_plane, dv11);
    for (i = 0; i < 28; i++) {
      b_U1[i].re = dv11[i] * 0.0;
      b_U1[i].im = dv11[i];
    }

    b_exp(b_U1);
    for (i = 0; i < 28; i++) {
      bim = b_U1[i].re;
      s = b_U1[i].im;
      b_U1[i].re = AmpU_re * b_U1[i].re - AmpU_im * b_U1[i].im;
      b_U1[i].im = AmpU_re * s + AmpU_im * bim;
      b_U2[i].re = -b_U1[i].re;
      b_U2[i].im = -b_U1[i].im;
    }

    memcpy(&U21[0], &b_U2[0], 5U * sizeof(creal_T));
    flipud(U21);
    memcpy(&U22[0], &b_U2[5], 6U * sizeof(creal_T));
    b_flipud(U22);
    memcpy(&U23[0], &b_U2[11], sizeof(creal_T) << 3);
    c_flipud(U23);
    memcpy(&U24[0], &b_U2[19], 9U * sizeof(creal_T));
    d_flipud(U24);
    memcpy(&U[0], &b_U1[0], 5U * sizeof(creal_T));
    memcpy(&U[5], &U21[0], 5U * sizeof(creal_T));
    memcpy(&U[10], &b_U1[0], 5U * sizeof(creal_T));
    memcpy(&U[15], &U21[0], 5U * sizeof(creal_T));
    memcpy(&U[20], &b_U1[5], 6U * sizeof(creal_T));
    memcpy(&U[26], &U22[0], 6U * sizeof(creal_T));
    memcpy(&U[32], &b_U1[5], 6U * sizeof(creal_T));
    memcpy(&U[38], &U22[0], 6U * sizeof(creal_T));
    memcpy(&U[44], &b_U1[11], sizeof(creal_T) << 3);
    memcpy(&U[52], &U23[0], sizeof(creal_T) << 3);
    memcpy(&U[60], &b_U1[11], sizeof(creal_T) << 3);
    memcpy(&U[68], &U23[0], sizeof(creal_T) << 3);
    memcpy(&U[76], &b_U1[19], 9U * sizeof(creal_T));
    memcpy(&U[85], &U24[0], 9U * sizeof(creal_T));
    memcpy(&U[94], &b_U1[19], 9U * sizeof(creal_T));
    memcpy(&U[103], &U24[0], 9U * sizeof(creal_T));
    break;

   default:
    for (i = 0; i < 112; i++) {
      U[i].re = 0.0;
      U[i].im = 0.0;
    }
    break;
  }

  /* 求近场增益G */
  /*  G = P' * P / ( U' * U ); */
  /*  save gain G; */
  /*  xlswrite('amp.xls',AmpU); */
  /*  xlswrite('angle.xls',AngU); */
  b_angle(U, AngleT);
  for (i = 0; i < 112; i++) {
    AngleT[i] = (AngleT[i] * 180.0 / 3.1415926535897931 + 180.0) / 1.40625;
  }

  b_round(AngleT);

  /*  xlswrite('AngleD.xls',AngleD); */
  /*  dlmwrite('AngleT.txt','precision','%.0f','newline', 'pc'); */
}

/* End of code generation (PsuedoInverse.c) */
