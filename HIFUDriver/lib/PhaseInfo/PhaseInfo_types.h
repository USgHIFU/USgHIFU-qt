/*
 * PhaseInfo_types.h
 *
 * Code generation for function 'PhaseInfo'
 *
 * C source code generated on: Thu Jul 02 16:18:09 2015
 *
 */

#ifndef __PHASEINFO_TYPES_H__
#define __PHASEINFO_TYPES_H__

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common
typedef struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray__common;
#endif
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
typedef struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_real_T;
#endif
#ifndef struct_emxArray_real_T_1x20
#define struct_emxArray_real_T_1x20
typedef struct emxArray_real_T_1x20
{
    real_T data[20];
    int32_T size[2];
} emxArray_real_T_1x20;
#endif
#ifndef struct_emxArray_real_T_1x400
#define struct_emxArray_real_T_1x400
typedef struct emxArray_real_T_1x400
{
    real_T data[400];
    int32_T size[2];
} emxArray_real_T_1x400;
#endif
#ifndef struct_emxArray_real_T_1x64
#define struct_emxArray_real_T_1x64
typedef struct emxArray_real_T_1x64
{
    real_T data[64];
    int32_T size[2];
} emxArray_real_T_1x64;
#endif
#ifndef struct_emxArray_real_T_20
#define struct_emxArray_real_T_20
typedef struct emxArray_real_T_20
{
    real_T data[20];
    int32_T size[1];
} emxArray_real_T_20;
#endif
#ifndef struct_emxArray_real_T_3x400
#define struct_emxArray_real_T_3x400
typedef struct emxArray_real_T_3x400
{
    real_T data[1200];
    int32_T size[2];
} emxArray_real_T_3x400;
#endif
typedef struct
{
    real_T rou;
    real_T usfreq;
    real_T c;
    real_T alpha;
    real_T k;
} struct_T;

#endif
/* End of code generation (PhaseInfo_types.h) */
