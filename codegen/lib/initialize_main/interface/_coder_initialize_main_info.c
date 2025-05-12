/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_initialize_main_info.c
 *
 * Code generation for function 'initialize_main'
 *
 */

/* Include files */
#include "_coder_initialize_main_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void);

/* Function Definitions */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[6] = {
      "789cdd564d4bdc50147da356c4623bb5a53be9b214a461b4c591ae9c0f6dfd1c185b1ca5"
      "684caee439ef23246f24cecaa53bb7fd0975512814baf707f847bae9"
      "a63fa08e933793a4bc2610c9e0dccdcde5e4e59cdccb3d09ca7dd8c821841ea16ebc7fd2"
      "cd537e9df7f3080a4714cff9793452cb7880c642e7247ee167833301",
      "9ee8164ca7d03b69728a99cec4f6a90dc801979313306f91234c601b53a8078bcd4e4597"
      "0350afe8409debb20546b3dea2c8b1dcbe42122c7afdf8a278dfb184"
      "fd78a3e8473e82ef553f6b16a7a039d8686a15709b82dbda5cc576f831180273a6618605"
      "d6096ec33ed5317b4d833abd943aa763744abc6e132cca9cda04bc4f",
      "9cb4e4a0a48e83943ac6953aba88c95b8704ee6e3e0b4abe309e603effb6e66644717d79"
      "9c506734f7ef9fb8cdbfae9e599d9c15dfe4abdf4fb3e4933128beb4"
      "fbf55cc1978fe09c116fabb9225ccbb2f5c692582d1a8ddd95be8e5a0c4f9c0ea4a8b37a"
      "7eda7d2d289e9f8fe009f69533d8775a2c60a6019de72975be8cd129",
      "f1aa271cdd10b59eac3ac1062c3b9c7e64f80883e99beca0fcf57b4abe75255f184f30af"
      "84ad0a7f170f14faeeca27fe7c7b91a9ef5e5fcc16b2e49331ecbe2b"
      "d65c738188b7bb3b27b05e5a2c42cd99e7e5e1f1ddfbbec76729f5cfc4e897b82f4ee1c2"
      "83fbcffd9a92afa4e40be3c9e7f7bfa965e7173f2fb3f5df87ef7e4c",
      "65c92763d8fd97e8502c6d1c1e57768cb579da28e076a96d56efbffffe05e1161daf",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 4448U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9] = {"Version",
                                    "ResolvedFunctions",
                                    "Checksum",
                                    "EntryPoints",
                                    "CoverageInfo",
                                    "IsPolymorphic",
                                    "PropertyList",
                                    "UUID",
                                    "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8] = {
      "QualifiedName",    "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "ResolvedFilePath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 2, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, "QualifiedName",
                emlrtMxCreateString("initialize_main"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, "ResolvedFilePath",
      emlrtMxCreateString("/home/rick/Desktop/2Dprojection/initialize_main.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739747.64678240742));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xInputs = emlrtCreateLogicalMatrix(1, 5);
  emlrtSetField(xEntryPoints, 1, "QualifiedName",
                emlrtMxCreateString("one_run_main"));
  emlrtSetField(xEntryPoints, 1, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(5.0));
  emlrtSetField(xEntryPoints, 1, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 1, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 1, "ResolvedFilePath",
      emlrtMxCreateString("/home/rick/Desktop/2Dprojection/one_run_main.m"));
  emlrtSetField(xEntryPoints, 1, "TimeStamp",
                emlrtMxCreateDoubleScalar(739747.64606481476));
  emlrtSetField(xEntryPoints, 1, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 1, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.2.0.2923080 (R2024b) Update 6"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)c_emlrtMexFcnResolvedFunctionsI());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("ltwEMHMBfKDlKecmxs2jlE"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_initialize_main_info.c) */
