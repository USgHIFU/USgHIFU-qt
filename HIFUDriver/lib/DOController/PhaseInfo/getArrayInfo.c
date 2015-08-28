/*
 * getArrayInfo.c
 *
 * Code generation for function 'getArrayInfo'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "getArrayInfo.h"
#include "PhaseInfo_emxutil.h"
#include "colon.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void getArrayInfo(real_T *arrayInfo_roc, real_T *arrayInfo_radius, real_T
                  *arrayInfo_numradius, real_T *arrayInfo_numangle, real_T
                  arrayInfo_numringelement[4], real_T arrayInfo_anglez[4],
                  real_T arrayInfo_anglefirstx[4], real_T *arrayInfo_numring,
                  real_T *arrayInfo_numelement, emxArray_real_T
                  *arrayInfo_anglexelement, emxArray_real_T
                  *arrayInfo_anglezelement)
{
  emxArray_real_T *AngleXElement;
  emxArray_real_T *AngleZElement;
  int32_T nm1;
  emxArray_real_T *b_AngleXElement;
  emxArray_real_T *b_AngleZElement;
  int32_T i;
  static const real_T dv0[4] = { 0.15707963267948966, 0.1308996938995747,
    0.098174770424681035, 0.087266462599716474 };

  real_T y;
  boolean_T n_too_large;
  real_T bnew;
  real_T anew;
  int32_T n;
  static const int8_T iv0[4] = { 20, 24, 32, 36 };

  real_T y_data[64];
  int32_T nm1d2;
  int32_T k;
  real_T kd;
  static const real_T dv1[4] = { 0.26878070480712674, 0.34470252726888007,
    0.42236967898262778, 0.50265482457436694 };

  static const int8_T NumRingElement[4] = { 20, 24, 32, 36 };

  static const real_T AngleZ[4] = { 0.26878070480712674, 0.34470252726888007,
    0.42236967898262778, 0.50265482457436694 };

  static const real_T AngleFirstX[4] = { 0.15707963267948966, 0.1308996938995747,
    0.098174770424681035, 0.087266462599716474 };

  emxInit_real_T(&AngleXElement, 2);
  emxInit_real_T(&AngleZElement, 2);

  /*  2012/09/19 */
  /*  Alpha Version */
  /*  输入相控阵参数 */
  /* 凹球面曲率半径，单位：m */
  /* 圆形阵元半径，单位：m */
  /* 半径划分份数 */
  /* 角度划分份数 */
  /* 每环阵元数量 */
  /* 每环与Z轴夹角，单位：rad */
  /* 每环首阵元与X轴夹角，单位：rad */
  /* 阵元环数 */
  /* 相控阵阵元数量 */
  /* 每个阵元与X轴、Z轴夹角，单位：rad */
  nm1 = AngleXElement->size[0] * AngleXElement->size[1];
  AngleXElement->size[0] = 1;
  AngleXElement->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)AngleXElement, nm1, (int32_T)sizeof
                    (real_T));
  nm1 = AngleZElement->size[0] * AngleZElement->size[1];
  AngleZElement->size[0] = 1;
  AngleZElement->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)AngleZElement, nm1, (int32_T)sizeof
                    (real_T));
  emxInit_real_T(&b_AngleXElement, 2);
  emxInit_real_T(&b_AngleZElement, 2);
  for (i = 0; i < 4; i++) {
    y = 2.0 * dv0[i];
    float_colon_length(dv0[i], y, 2.0 * dv0[i] * ((real_T)iv0[i] - 1.0) + dv0[i],
                       &n, &anew, &bnew, &n_too_large);
    if (n > 0) {
      y_data[0] = anew;
      if (n > 1) {
        y_data[n - 1] = bnew;
        nm1 = n - 1;
        nm1d2 = nm1 / 2;
        for (k = 1; k <= nm1d2 - 1; k++) {
          kd = (real_T)k * y;
          y_data[k] = anew + kd;
          y_data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == nm1) {
          y_data[nm1d2] = (anew + bnew) / 2.0;
        } else {
          kd = (real_T)nm1d2 * y;
          y_data[nm1d2] = anew + kd;
          y_data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    nm1 = b_AngleXElement->size[0] * b_AngleXElement->size[1];
    b_AngleXElement->size[0] = 1;
    b_AngleXElement->size[1] = AngleXElement->size[1] + n;
    emxEnsureCapacity((emxArray__common *)b_AngleXElement, nm1, (int32_T)sizeof
                      (real_T));
    nm1d2 = AngleXElement->size[1] - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      b_AngleXElement->data[b_AngleXElement->size[0] * nm1] =
        AngleXElement->data[AngleXElement->size[0] * nm1];
    }

    nm1d2 = n - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      b_AngleXElement->data[b_AngleXElement->size[0] * (nm1 +
        AngleXElement->size[1])] = y_data[nm1];
    }

    nm1 = AngleXElement->size[0] * AngleXElement->size[1];
    AngleXElement->size[0] = 1;
    AngleXElement->size[1] = b_AngleXElement->size[1];
    emxEnsureCapacity((emxArray__common *)AngleXElement, nm1, (int32_T)sizeof
                      (real_T));
    nm1d2 = b_AngleXElement->size[1] - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      AngleXElement->data[AngleXElement->size[0] * nm1] = b_AngleXElement->
        data[b_AngleXElement->size[0] * nm1];
    }

    nm1 = b_AngleZElement->size[0] * b_AngleZElement->size[1];
    b_AngleZElement->size[0] = 1;
    b_AngleZElement->size[1] = AngleZElement->size[1] + iv0[i];
    emxEnsureCapacity((emxArray__common *)b_AngleZElement, nm1, (int32_T)sizeof
                      (real_T));
    nm1d2 = AngleZElement->size[1] - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      b_AngleZElement->data[b_AngleZElement->size[0] * nm1] =
        AngleZElement->data[AngleZElement->size[0] * nm1];
    }

    nm1d2 = iv0[i] - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      b_AngleZElement->data[b_AngleZElement->size[0] * (nm1 +
        AngleZElement->size[1])] = dv1[i];
    }

    nm1 = AngleZElement->size[0] * AngleZElement->size[1];
    AngleZElement->size[0] = 1;
    AngleZElement->size[1] = b_AngleZElement->size[1];
    emxEnsureCapacity((emxArray__common *)AngleZElement, nm1, (int32_T)sizeof
                      (real_T));
    nm1d2 = b_AngleZElement->size[1] - 1;
    for (nm1 = 0; nm1 <= nm1d2; nm1++) {
      AngleZElement->data[AngleZElement->size[0] * nm1] = b_AngleZElement->
        data[b_AngleZElement->size[0] * nm1];
    }
  }

  emxFree_real_T(&b_AngleZElement);
  emxFree_real_T(&b_AngleXElement);
  *arrayInfo_roc = 0.14;
  *arrayInfo_radius = 0.005;
  *arrayInfo_numradius = 20.0;
  *arrayInfo_numangle = 20.0;
  for (nm1 = 0; nm1 < 4; nm1++) {
    arrayInfo_numringelement[nm1] = (real_T)NumRingElement[nm1];
  }

  for (nm1 = 0; nm1 < 4; nm1++) {
    arrayInfo_anglez[nm1] = AngleZ[nm1];
  }

  for (nm1 = 0; nm1 < 4; nm1++) {
    arrayInfo_anglefirstx[nm1] = AngleFirstX[nm1];
  }

  *arrayInfo_numring = 4.0;
  *arrayInfo_numelement = 112.0;
  nm1 = arrayInfo_anglexelement->size[0] * arrayInfo_anglexelement->size[1];
  arrayInfo_anglexelement->size[0] = 1;
  arrayInfo_anglexelement->size[1] = AngleXElement->size[1];
  emxEnsureCapacity((emxArray__common *)arrayInfo_anglexelement, nm1, (int32_T)
                    sizeof(real_T));
  nm1d2 = AngleXElement->size[0] * AngleXElement->size[1] - 1;
  for (nm1 = 0; nm1 <= nm1d2; nm1++) {
    arrayInfo_anglexelement->data[nm1] = AngleXElement->data[nm1];
  }

  emxFree_real_T(&AngleXElement);
  nm1 = arrayInfo_anglezelement->size[0] * arrayInfo_anglezelement->size[1];
  arrayInfo_anglezelement->size[0] = 1;
  arrayInfo_anglezelement->size[1] = AngleZElement->size[1];
  emxEnsureCapacity((emxArray__common *)arrayInfo_anglezelement, nm1, (int32_T)
                    sizeof(real_T));
  nm1d2 = AngleZElement->size[0] * AngleZElement->size[1] - 1;
  for (nm1 = 0; nm1 <= nm1d2; nm1++) {
    arrayInfo_anglezelement->data[nm1] = AngleZElement->data[nm1];
  }

  emxFree_real_T(&AngleZElement);
}

/* End of code generation (getArrayInfo.c) */
