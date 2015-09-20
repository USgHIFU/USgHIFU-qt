/*
 * PsuedoInverse.c
 *
 * Code generation for function 'PsuedoInverse'
 *
 * C source code generated on: Fri Sep 11 10:56:18 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "PsuedoInverse.h"
#include "PhaseInfo_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real_T rt_atan2d_snf(real_T u0, real_T u1);
static real_T rt_roundd_snf(real_T u);

/* Function Definitions */
static real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T i3;
  int32_T i4;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u1 > 0.0) {
      i3 = 1;
    } else {
      i3 = -1;
    }

    if (u0 > 0.0) {
      i4 = 1;
    } else {
      i4 = -1;
    }

    y = atan2((real_T)i4, (real_T)i3);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

static real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = -0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void PsuedoInverse(const creal_T H[144], uint8_T focusInfo_numfocus, creal_T U
                   [144], real_T AngleT[144])
{
  real_T y[144];
  int32_T i;
  creal_T x[144];
  real_T r;
  real_T s;
  real_T AmpU_re;
  real_T AmpU_im;
  real_T brm;

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
    for (i = 0; i < 144; i++) {
      x[i].re = H[i].re;
      x[i].im = -H[i].im;
      y[i] = rt_atan2d_snf(x[i].im, x[i].re);
      r = rt_hypotd_snf(fabs(H[i].re), fabs(H[i].im));
      if (H[i].im == 0.0) {
        s = H[i].re / r;
        r = 0.0;
      } else if (H[i].re == 0.0) {
        s = 0.0;
        r = H[i].im / r;
      } else {
        s = H[i].re / r;
        r = H[i].im / r;
      }

      x[i].re = s;
      x[i].im = -r;
    }

    AmpU_re = 0.0;
    AmpU_im = 0.0;
    for (i = 0; i < 144; i++) {
      AmpU_re += H[i].re * x[i].re - H[i].im * x[i].im;
      AmpU_im += H[i].re * x[i].im + H[i].im * x[i].re;
    }

    if (AmpU_im == 0.0) {
      AmpU_re = 1.0904850535426885E+6 / AmpU_re;
      AmpU_im = 0.0;
    } else if (AmpU_re == 0.0) {
      AmpU_re = 0.0;
      AmpU_im = -(1.0904850535426885E+6 / AmpU_im);
    } else {
      brm = fabs(AmpU_re);
      r = fabs(AmpU_im);
      if (brm > r) {
        s = AmpU_im / AmpU_re;
        r = AmpU_re + s * AmpU_im;
        AmpU_re = (1.0904850535426885E+6 + s * 0.0) / r;
        AmpU_im = (0.0 - s * 1.0904850535426885E+6) / r;
      } else if (r == brm) {
        r = AmpU_re > 0.0 ? 0.5 : -0.5;
        s = AmpU_im > 0.0 ? 0.5 : -0.5;
        AmpU_re = 1.0904850535426885E+6 * r / brm;
        AmpU_im = (-0.0 - 1.0904850535426885E+6 * s) / brm;
      } else {
        s = AmpU_re / AmpU_im;
        r = AmpU_im + s * AmpU_re;
        AmpU_re = s * 1.0904850535426885E+6 / r;
        AmpU_im = (s * 0.0 - 1.0904850535426885E+6) / r;
      }
    }

    for (i = 0; i < 144; i++) {
      U[i].re = y[i] * 0.0;
      U[i].im = y[i];
      r = exp(U[i].re / 2.0);
      brm = U[i].im;
      U[i].re = r * (r * cos(U[i].im));
      U[i].im = r * (r * sin(brm));
      s = U[i].re;
      brm = U[i].im;
      U[i].re = AmpU_re * U[i].re - AmpU_im * U[i].im;
      U[i].im = AmpU_re * brm + AmpU_im * s;
    }

    /*      case 2 */
    /*              %双焦点 */
    /*              H11 = H(1:10); */
    /*              H12 = H(21:32); */
    /*              H13 = H(45:60); */
    /*              H14 = H(77:94); */
    /*              H1 = [H11 H12 H13 H14]; */
    /*               */
    /*              H21 = H(11:20); */
    /*              H22 = H(33:44); */
    /*              H23 = H(61:76); */
    /*              H24 = H(95:112); */
    /*              H2 = [H21 H22 H23 H24]; */
    /*               */
    /*              H_plane = H1 - H2; */
    /*              AngU1 = angle(H_plane') + angle(P); */
    /*              AmpU1 = P / (H_plane * (H_plane./abs(H_plane))'); */
    /*              U1 = AmpU1 * exp(1i*AngU1); */
    /*              U2 = -U1; */
    /*              U11 = U1(1:10); U12 = U1(11:22); U13 = U1(23:38); U14 = U1(39:56); */
    /*              U21 = U2(1:10); U22 = U2(11:22); U23 = U2(23:38); U24 = U2(39:56); */
    /*               */
    /*              U = [U11;U21;U12;U22;U13;U23;U14;U24]; */
    /*              AmpU = abs(U); */
    /*              AngU = angle(U); */
    /*           case 4 */
    /*                  %四焦点 */
    /*                  H11 = H(1:5); */
    /*                  H12 = H(21:26); */
    /*                  H13 = H(45:52); */
    /*                  H14 = H(77:85); */
    /*                  H1 = [H11 H12 H13 H14]; */
    /*                   */
    /*                  H21 = fliplr(H(6:10)); */
    /*                  H22 = fliplr(H(27:32)); */
    /*                  H23 = fliplr(H(53:60)); */
    /*                  H24 = fliplr(H(86:94)); */
    /*                  H2 = [H21 H22 H23 H24]; */
    /*                   */
    /*                  H31 = H(11:15); */
    /*                  H32 = H(33:38); */
    /*                  H33 = H(61:68); */
    /*                  H34 = H(95:103); */
    /*                  H3 = [H31 H32 H33 H34]; */
    /*                   */
    /*                  H41 = fliplr(H(16:20)); */
    /*                  H42 = fliplr(H(39:44)); */
    /*                  H43 = fliplr(H(69:76)); */
    /*                  H44 = fliplr(H(104:112)); */
    /*                  H4 = [H41 H42 H43 H44]; */
    /*                   */
    /*                  H_plane = H1 - H2 + H3 - H4; */
    /*                  AngU1 = angle(H_plane') + angle(P); */
    /*                  AmpU1 = P / (H_plane * (H_plane./abs(H_plane))'); */
    /*                  U1 = AmpU1 * exp(1i*AngU1); */
    /*                  U2 = -U1; */
    /*                  U11 = U1(1:5); U12 = U1(6:11); U13 = U1(12:19); U14 = U1(20:28); */
    /*                  U21 = flipud(U2(1:5)); U22 = flipud(U2(6:11)); U23 = flipud(U2(12:19)); U24 = flipud(U2(20:28)); */
    /*                  U31 = U11; U32 = U12; U33 = U13; U34 = U14; */
    /*                  U41 = U21; U42 = U22; U43 = U23; U44 = U24; */
    /*                   */
    /*                  U = [U11;U21;U31;U41;U12;U22;U32;U42;U13;U23;U33;U43;U14;U24;U34;U44]; */
    /*                  AmpU = abs(U); */
    /*                  AngU = angle(U); */
    break;

   default:
    for (i = 0; i < 144; i++) {
      U[i].re = 0.0;
      U[i].im = 0.0;
    }

    /*          U = zeros(112,1); */
    break;
  }

  /* 求近场增益G */
  /*  G = P' * P / ( U' * U ); */
  /*  save gain G; */
  /*  xlswrite('amp.xls',AmpU); */
  /*  xlswrite('angle.xls',AngU); */
  for (i = 0; i < 144; i++) {
    AngleT[i] = rt_roundd_snf((rt_atan2d_snf(U[i].im, U[i].re) * 180.0 /
      3.1415926535897931 + 180.0) / 1.40625);
  }

  /*  xlswrite('AngleD.xls',AngleD); */
  /*  dlmwrite('AngleT.txt','precision','%.0f','newline', 'pc'); */
}

/* End of code generation (PsuedoInverse.c) */
