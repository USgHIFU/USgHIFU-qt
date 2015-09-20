/*
 * getArrayInfo.c
 *
 * Code generation for function 'getArrayInfo'
 *
 * C source code generated on: Fri Sep 11 10:56:17 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "PhaseInfo.h"
#include "getArrayInfo.h"
#include "PhaseInfo_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void getArrayInfo(real_T *arrayInfo_roc, real_T *arrayInfo_radius, real_T
                  *arrayInfo_numradius, real_T *arrayInfo_numangle, real_T
                  arrayInfo_numringelement[6], real_T arrayInfo_anglez[6],
                  real_T arrayInfo_anglefirstx[6], real_T *arrayInfo_numring,
                  real_T *arrayInfo_numelement, emxArray_real_T
                  *arrayInfo_anglexelement, emxArray_real_T
                  *arrayInfo_anglezelement)
{
  emxArray_real_T *AngleXElement;
  emxArray_real_T *AngleZElement;
  int32_T nm1d2;
  emxArray_real_T *b_AngleXElement;
  emxArray_real_T *b_AngleZElement;
  int32_T i;
  int32_T ndbl;
  static const real_T dv0[6] = { 0.0, 0.1265363707695889, 0.0,
    0.1265363707695889, 0.0, 0.1265363707695889 };

  real_T cdiff;
  real_T y_data[24];
  int32_T loop_ub;
  real_T kd;
  static const real_T dv1[6] = { 0.41154863762026284, 0.46547931150688771,
    0.51312680008633282, 0.5536184387326013, 0.59847340050885556,
    0.64158303303311548 };

  static const real_T AngleZ[6] = { 0.41154863762026284, 0.46547931150688771,
    0.51312680008633282, 0.5536184387326013, 0.59847340050885556,
    0.64158303303311548 };

  static const real_T AngleFirstX[6] = { 0.0, 0.1265363707695889, 0.0,
    0.1265363707695889, 0.0, 0.1265363707695889 };

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
  nm1d2 = AngleXElement->size[0] * AngleXElement->size[1];
  AngleXElement->size[0] = 1;
  AngleXElement->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)AngleXElement, nm1d2, (int32_T)sizeof
                    (real_T));
  nm1d2 = AngleZElement->size[0] * AngleZElement->size[1];
  AngleZElement->size[0] = 1;
  AngleZElement->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)AngleZElement, nm1d2, (int32_T)sizeof
                    (real_T));
  emxInit_real_T(&b_AngleXElement, 2);
  emxInit_real_T(&b_AngleZElement, 2);
  for (i = 0; i < 6; i++) {
    ndbl = 22;
    cdiff = (dv0[i] + 6.0213859193804362) - (6.0213859193804362 + dv0[i]);
    if (fabs(cdiff) < 4.4408920985006262E-16 * (6.0213859193804362 + dv0[i])) {
      ndbl = 23;
      cdiff = 6.0213859193804362 + dv0[i];
    } else if (cdiff > 0.0) {
      cdiff = dv0[i] + 5.7595865315812871;
    } else {
      ndbl = 23;
      cdiff = dv0[i] + 6.0213859193804362;
    }

    y_data[0] = dv0[i];
    y_data[ndbl] = cdiff;
    nm1d2 = ndbl / 2;
    for (loop_ub = 1; loop_ub <= nm1d2 - 1; loop_ub++) {
      kd = (real_T)loop_ub * 0.26179938779914941;
      y_data[loop_ub] = dv0[i] + kd;
      y_data[ndbl - loop_ub] = cdiff - kd;
    }

    if (nm1d2 << 1 == ndbl) {
      y_data[nm1d2] = (dv0[i] + cdiff) / 2.0;
    } else {
      kd = (real_T)nm1d2 * 0.26179938779914941;
      y_data[nm1d2] = dv0[i] + kd;
      y_data[nm1d2 + 1] = cdiff - kd;
    }

    nm1d2 = b_AngleXElement->size[0] * b_AngleXElement->size[1];
    b_AngleXElement->size[0] = 1;
    b_AngleXElement->size[1] = (AngleXElement->size[1] + ndbl) + 1;
    emxEnsureCapacity((emxArray__common *)b_AngleXElement, nm1d2, (int32_T)
                      sizeof(real_T));
    loop_ub = AngleXElement->size[1] - 1;
    for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
      b_AngleXElement->data[b_AngleXElement->size[0] * nm1d2] =
        AngleXElement->data[AngleXElement->size[0] * nm1d2];
    }

    loop_ub = ndbl;
    for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
      b_AngleXElement->data[b_AngleXElement->size[0] * (nm1d2 +
        AngleXElement->size[1])] = y_data[nm1d2];
    }

    nm1d2 = AngleXElement->size[0] * AngleXElement->size[1];
    AngleXElement->size[0] = 1;
    AngleXElement->size[1] = b_AngleXElement->size[1];
    emxEnsureCapacity((emxArray__common *)AngleXElement, nm1d2, (int32_T)sizeof
                      (real_T));
    loop_ub = b_AngleXElement->size[1] - 1;
    for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
      AngleXElement->data[AngleXElement->size[0] * nm1d2] =
        b_AngleXElement->data[b_AngleXElement->size[0] * nm1d2];
    }

    nm1d2 = b_AngleZElement->size[0] * b_AngleZElement->size[1];
    b_AngleZElement->size[0] = 1;
    b_AngleZElement->size[1] = AngleZElement->size[1] + 24;
    emxEnsureCapacity((emxArray__common *)b_AngleZElement, nm1d2, (int32_T)
                      sizeof(real_T));
    loop_ub = AngleZElement->size[1] - 1;
    for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
      b_AngleZElement->data[b_AngleZElement->size[0] * nm1d2] =
        AngleZElement->data[AngleZElement->size[0] * nm1d2];
    }

    for (nm1d2 = 0; nm1d2 < 24; nm1d2++) {
      b_AngleZElement->data[b_AngleZElement->size[0] * (nm1d2 +
        AngleZElement->size[1])] = dv1[i];
    }

    nm1d2 = AngleZElement->size[0] * AngleZElement->size[1];
    AngleZElement->size[0] = 1;
    AngleZElement->size[1] = b_AngleZElement->size[1];
    emxEnsureCapacity((emxArray__common *)AngleZElement, nm1d2, (int32_T)sizeof
                      (real_T));
    loop_ub = b_AngleZElement->size[1] - 1;
    for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
      AngleZElement->data[AngleZElement->size[0] * nm1d2] =
        b_AngleZElement->data[b_AngleZElement->size[0] * nm1d2];
    }
  }

  emxFree_real_T(&b_AngleZElement);
  emxFree_real_T(&b_AngleXElement);
  *arrayInfo_roc = 0.14;
  *arrayInfo_radius = 0.005;
  *arrayInfo_numradius = 20.0;
  *arrayInfo_numangle = 20.0;
  for (nm1d2 = 0; nm1d2 < 6; nm1d2++) {
    arrayInfo_numringelement[nm1d2] = 24.0;
  }

  for (nm1d2 = 0; nm1d2 < 6; nm1d2++) {
    arrayInfo_anglez[nm1d2] = AngleZ[nm1d2];
  }

  for (nm1d2 = 0; nm1d2 < 6; nm1d2++) {
    arrayInfo_anglefirstx[nm1d2] = AngleFirstX[nm1d2];
  }

  *arrayInfo_numring = 6.0;
  *arrayInfo_numelement = 144.0;
  nm1d2 = arrayInfo_anglexelement->size[0] * arrayInfo_anglexelement->size[1];
  arrayInfo_anglexelement->size[0] = 1;
  arrayInfo_anglexelement->size[1] = AngleXElement->size[1];
  emxEnsureCapacity((emxArray__common *)arrayInfo_anglexelement, nm1d2, (int32_T)
                    sizeof(real_T));
  loop_ub = AngleXElement->size[0] * AngleXElement->size[1] - 1;
  for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
    arrayInfo_anglexelement->data[nm1d2] = AngleXElement->data[nm1d2];
  }

  emxFree_real_T(&AngleXElement);
  nm1d2 = arrayInfo_anglezelement->size[0] * arrayInfo_anglezelement->size[1];
  arrayInfo_anglezelement->size[0] = 1;
  arrayInfo_anglezelement->size[1] = AngleZElement->size[1];
  emxEnsureCapacity((emxArray__common *)arrayInfo_anglezelement, nm1d2, (int32_T)
                    sizeof(real_T));
  loop_ub = AngleZElement->size[0] * AngleZElement->size[1] - 1;
  for (nm1d2 = 0; nm1d2 <= loop_ub; nm1d2++) {
    arrayInfo_anglezelement->data[nm1d2] = AngleZElement->data[nm1d2];
  }

  emxFree_real_T(&AngleZElement);
}

/* End of code generation (getArrayInfo.c) */
