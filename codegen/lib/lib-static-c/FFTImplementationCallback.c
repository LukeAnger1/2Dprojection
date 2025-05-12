/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.c
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

/* Include files */
#include "FFTImplementationCallback.h"
#include "lib-static-c_emxutil.h"
#include "lib-static-c_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <math.h>

/* Function Declarations */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            int xoffInit, emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab);

static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv);

static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

/* Function Definitions */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            int xoffInit, emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab)
{
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_int32_T *bitrevIndex;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *hcostab;
  emxArray_real_T *hsintab;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  const double *x_data;
  double b_y_re_tmp;
  double im;
  double re;
  double temp2_im;
  double temp2_re;
  double temp_im;
  double temp_im_tmp;
  double temp_re;
  double temp_re_tmp;
  double y_re_tmp;
  double *hcostab_data;
  double *hsintab_data;
  int hszCostab;
  int i;
  int iheight;
  int ihi;
  int istart;
  int j;
  int ju;
  int k;
  int nRowsD2_tmp;
  int nRows_tmp;
  int *bitrevIndex_data;
  int *wrapIndex_data;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  y_data = y->data;
  x_data = x->data;
  nRows_tmp = (unsigned_nRows + (unsigned_nRows < 0)) >> 1;
  iheight = y->size[0];
  if (iheight > nRows_tmp) {
    iheight = nRows_tmp;
  }
  istart = iheight - 2;
  ihi = nRows_tmp - 2;
  nRowsD2_tmp = (nRows_tmp + (nRows_tmp < 0)) >> 1;
  k = (nRowsD2_tmp + (nRowsD2_tmp < 0)) >> 1;
  hszCostab = (int)((unsigned int)costab->size[1] >> 1);
  emxInit_real_T(&hcostab, 2);
  j = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, j);
  hcostab_data = hcostab->data;
  emxInit_real_T(&hsintab, 2);
  j = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, j);
  hsintab_data = hsintab->data;
  for (i = 0; i < hszCostab; i++) {
    j = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[j];
    hsintab_data[i] = sintab_data[j];
  }
  emxInit_creal_T(&reconVar1, 1);
  j = reconVar1->size[0];
  reconVar1->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar1, j);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  j = reconVar2->size[0];
  reconVar2->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar2, j);
  reconVar2_data = reconVar2->data;
  emxInit_int32_T(&wrapIndex, 2);
  j = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = nRows_tmp;
  emxEnsureCapacity_int32_T(wrapIndex, j);
  wrapIndex_data = wrapIndex->data;
  ju = 0;
  hszCostab = 1;
  emxInit_int32_T(&bitrevIndex, 1);
  j = bitrevIndex->size[0];
  bitrevIndex->size[0] = nRows_tmp;
  emxEnsureCapacity_int32_T(bitrevIndex, j);
  bitrevIndex_data = bitrevIndex->data;
  for (i = 0; i < nRows_tmp; i++) {
    temp2_re = sintab_data[i];
    temp2_im = costab_data[i];
    reconVar1_data[i].re = temp2_re + 1.0;
    reconVar1_data[i].im = -temp2_im;
    reconVar2_data[i].re = 1.0 - temp2_re;
    reconVar2_data[i].im = temp2_im;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (nRows_tmp - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
    bitrevIndex_data[i] = 0;
  }
  for (j = 0; j <= istart; j++) {
    bitrevIndex_data[j] = hszCostab;
    hszCostab = nRows_tmp;
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }
    hszCostab = ju + 1;
  }
  bitrevIndex_data[iheight - 1] = hszCostab;
  if (((unsigned int)x->size[0] & 1U) == 0U) {
    tst = true;
    iheight = x->size[0];
  } else if (x->size[0] >= unsigned_nRows) {
    tst = true;
    iheight = unsigned_nRows;
  } else {
    tst = false;
    iheight = x->size[0] - 1;
  }
  if (iheight > unsigned_nRows) {
    iheight = unsigned_nRows;
  }
  hszCostab = (iheight + (iheight < 0)) >> 1;
  for (i = 0; i < hszCostab; i++) {
    j = xoffInit + (i << 1);
    y_data[bitrevIndex_data[i] - 1].re = x_data[j];
    y_data[bitrevIndex_data[i] - 1].im = x_data[j + 1];
  }
  if (!tst) {
    if (hszCostab - 1 < 0) {
      iheight = xoffInit;
    } else {
      iheight = xoffInit + (hszCostab << 1);
    }
    y_data[bitrevIndex_data[hszCostab] - 1].re = x_data[iheight];
    y_data[bitrevIndex_data[hszCostab] - 1].im = 0.0;
  }
  emxFree_int32_T(&bitrevIndex);
  if (nRows_tmp > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp2_re = y_data[i + 1].re;
      temp2_im = y_data[i + 1].im;
      temp_re = temp2_re;
      temp_im = temp2_im;
      re = y_data[i].re;
      im = y_data[i].im;
      temp2_re = re - temp2_re;
      temp2_im = im - temp2_im;
      y_data[i + 1].re = temp2_re;
      y_data[i + 1].im = temp2_im;
      re += temp_re;
      im += temp_im;
      y_data[i].re = re;
      y_data[i].im = im;
    }
  }
  hszCostab = 2;
  ju = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + hszCostab;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2_tmp; j += k) {
      temp2_re = hcostab_data[j];
      temp2_im = hsintab_data[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + hszCostab;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        temp_im = y_data[b_temp_re_tmp].re;
        temp_re = temp2_re * temp_im - temp2_im * temp_re_tmp;
        temp_im = temp2_re * temp_re_tmp + temp2_im * temp_im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k >>= 1;
    hszCostab = ju;
    ju += ju;
    iheight -= hszCostab;
  }
  emxFree_real_T(&hsintab);
  emxFree_real_T(&hcostab);
  temp_re_tmp = y_data[0].re;
  temp_im = y_data[0].im;
  y_re_tmp = y_data[0].re * reconVar1_data[0].re;
  temp2_im = y_data[0].re * reconVar1_data[0].im;
  temp_re = -y_data[0].im;
  b_y_re_tmp = temp_re_tmp * reconVar2_data[0].re;
  temp2_re = temp_re_tmp * reconVar2_data[0].im;
  y_data[0].re = 0.5 * ((y_re_tmp - y_data[0].im * reconVar1_data[0].im) +
                        (b_y_re_tmp - temp_re * reconVar2_data[0].im));
  y_data[0].im = 0.5 * ((temp2_im + y_data[0].im * reconVar1_data[0].re) +
                        (temp2_re + temp_re * reconVar2_data[0].re));
  y_data[nRows_tmp].re = 0.5 * ((b_y_re_tmp - temp_im * reconVar2_data[0].im) +
                                (y_re_tmp - temp_re * reconVar1_data[0].im));
  y_data[nRows_tmp].im = 0.5 * ((temp2_re + temp_im * reconVar2_data[0].re) +
                                (temp2_im + temp_re * reconVar1_data[0].re));
  for (i = 2; i <= nRowsD2_tmp; i++) {
    temp_re_tmp = y_data[i - 1].re;
    temp_im_tmp = y_data[i - 1].im;
    j = wrapIndex_data[i - 1];
    temp2_im = y_data[j - 1].re;
    temp_re = y_data[j - 1].im;
    y_re_tmp = reconVar1_data[i - 1].im;
    b_y_re_tmp = reconVar1_data[i - 1].re;
    temp2_re = reconVar2_data[i - 1].im;
    temp_im = reconVar2_data[i - 1].re;
    y_data[i - 1].re =
        0.5 * ((temp_re_tmp * b_y_re_tmp - temp_im_tmp * y_re_tmp) +
               (temp2_im * temp_im - -temp_re * temp2_re));
    y_data[i - 1].im =
        0.5 * ((temp_re_tmp * y_re_tmp + temp_im_tmp * b_y_re_tmp) +
               (temp2_im * temp2_re + -temp_re * temp_im));
    hszCostab = (nRows_tmp + i) - 1;
    y_data[hszCostab].re =
        0.5 * ((temp_re_tmp * temp_im - temp_im_tmp * temp2_re) +
               (temp2_im * b_y_re_tmp - -temp_re * y_re_tmp));
    y_data[hszCostab].im =
        0.5 * ((temp_re_tmp * temp2_re + temp_im_tmp * temp_im) +
               (temp2_im * y_re_tmp + -temp_re * b_y_re_tmp));
    re = reconVar1_data[j - 1].im;
    im = reconVar1_data[j - 1].re;
    temp_im = reconVar2_data[j - 1].im;
    temp2_re = reconVar2_data[j - 1].re;
    y_data[j - 1].re =
        0.5 * ((temp2_im * im - temp_re * re) +
               (temp_re_tmp * temp2_re - -temp_im_tmp * temp_im));
    y_data[j - 1].im =
        0.5 * ((temp2_im * re + temp_re * im) +
               (temp_re_tmp * temp_im + -temp_im_tmp * temp2_re));
    j = (j + nRows_tmp) - 1;
    y_data[j].re = 0.5 * ((temp2_im * temp2_re - temp_re * temp_im) +
                          (temp_re_tmp * im - -temp_im_tmp * re));
    y_data[j].im = 0.5 * ((temp2_im * temp_im + temp_re * temp2_re) +
                          (temp_re_tmp * re + -temp_im_tmp * im));
  }
  emxFree_int32_T(&wrapIndex);
  if (nRowsD2_tmp != 0) {
    temp_re_tmp = y_data[nRowsD2_tmp].re;
    temp_im_tmp = y_data[nRowsD2_tmp].im;
    y_re_tmp = reconVar1_data[nRowsD2_tmp].im;
    b_y_re_tmp = reconVar1_data[nRowsD2_tmp].re;
    temp2_re = temp_re_tmp * b_y_re_tmp;
    temp2_im = temp_re_tmp * y_re_tmp;
    temp_im = reconVar2_data[nRowsD2_tmp].im;
    re = reconVar2_data[nRowsD2_tmp].re;
    im = temp_re_tmp * re;
    temp_re = temp_re_tmp * temp_im;
    y_data[nRowsD2_tmp].re = 0.5 * ((temp2_re - temp_im_tmp * y_re_tmp) +
                                    (im - -temp_im_tmp * temp_im));
    y_data[nRowsD2_tmp].im = 0.5 * ((temp2_im + temp_im_tmp * b_y_re_tmp) +
                                    (temp_re + -temp_im_tmp * re));
    j = nRows_tmp + nRowsD2_tmp;
    y_data[j].re = 0.5 * ((im - temp_im_tmp * temp_im) +
                          (temp2_re - -temp_im_tmp * y_re_tmp));
    y_data[j].im = 0.5 * ((temp_re + temp_im_tmp * re) +
                          (temp2_im + -temp_im_tmp * b_y_re_tmp));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
}

static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_creal_T *ytmp;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *b_costab;
  emxArray_real_T *b_sintab;
  emxArray_real_T *costab1q;
  emxArray_real_T *hcostabinv;
  emxArray_real_T *hsintab;
  emxArray_real_T *hsintabinv;
  const creal_T *wwc_data;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  creal_T *ytmp_data;
  const double *costab_data;
  const double *costabinv_data;
  const double *sintab_data;
  const double *sintabinv_data;
  const double *x_data;
  double b_temp_re_tmp;
  double e;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double *b_costab_data;
  double *b_sintab_data;
  double *costab1q_data;
  double *hcostabinv_data;
  double *hsintab_data;
  double *hsintabinv_data;
  int hnRows;
  int i;
  int istart;
  int j;
  int ju;
  int k;
  int minHnrowsNxBy2;
  int nRowsD2;
  int nd2;
  int nfft_tmp;
  int temp_re_tmp;
  int *wrapIndex_data;
  bool tst;
  sintabinv_data = sintabinv->data;
  costabinv_data = costabinv->data;
  sintab_data = sintab->data;
  costab_data = costab->data;
  wwc_data = wwc->data;
  y_data = y->data;
  x_data = x->data;
  hnRows = (nRows + (nRows < 0)) >> 1;
  emxInit_creal_T(&ytmp, 1);
  minHnrowsNxBy2 = ytmp->size[0];
  ytmp->size[0] = hnRows;
  emxEnsureCapacity_creal_T(ytmp, minHnrowsNxBy2);
  ytmp_data = ytmp->data;
  if (hnRows > nrowsx) {
    minHnrowsNxBy2 = ytmp->size[0];
    ytmp->size[0] = hnRows;
    emxEnsureCapacity_creal_T(ytmp, minHnrowsNxBy2);
    ytmp_data = ytmp->data;
    for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
      ytmp_data[minHnrowsNxBy2].re = 0.0;
      ytmp_data[minHnrowsNxBy2].im = 0.0;
    }
  }
  if (((unsigned int)x->size[0] & 1U) == 0U) {
    tst = true;
    j = x->size[0];
  } else if (x->size[0] >= nRows) {
    tst = true;
    j = nRows;
  } else {
    tst = false;
    j = x->size[0] - 1;
  }
  nd2 = nRows << 1;
  e = 6.2831853071795862 / (double)nd2;
  minHnrowsNxBy2 = (nd2 + (nd2 < 0)) >> 1;
  istart = (minHnrowsNxBy2 + (minHnrowsNxBy2 < 0)) >> 1;
  emxInit_real_T(&costab1q, 2);
  minHnrowsNxBy2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = istart + 1;
  emxEnsureCapacity_real_T(costab1q, minHnrowsNxBy2);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = (int)((unsigned int)istart >> 1) - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  minHnrowsNxBy2 = nd2 + 2;
  for (k = minHnrowsNxBy2; k < istart; k++) {
    costab1q_data[k] = sin(e * (double)(istart - k));
  }
  costab1q_data[istart] = 0.0;
  istart = costab1q->size[1] - 1;
  nd2 = (costab1q->size[1] - 1) << 1;
  emxInit_real_T(&b_costab, 2);
  minHnrowsNxBy2 = b_costab->size[0] * b_costab->size[1];
  b_costab->size[0] = 1;
  b_costab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_costab, minHnrowsNxBy2);
  b_costab_data = b_costab->data;
  emxInit_real_T(&b_sintab, 2);
  minHnrowsNxBy2 = b_sintab->size[0] * b_sintab->size[1];
  b_sintab->size[0] = 1;
  b_sintab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_sintab, minHnrowsNxBy2);
  b_sintab_data = b_sintab->data;
  b_costab_data[0] = 1.0;
  b_sintab_data[0] = 0.0;
  for (k = 0; k < istart; k++) {
    b_costab_data[k + 1] = costab1q_data[k + 1];
    b_sintab_data[k + 1] = -costab1q_data[(istart - k) - 1];
  }
  minHnrowsNxBy2 = costab1q->size[1];
  for (k = minHnrowsNxBy2; k <= nd2; k++) {
    b_costab_data[k] = -costab1q_data[nd2 - k];
    b_sintab_data[k] = -costab1q_data[k - istart];
  }
  nd2 = (int)((unsigned int)costab->size[1] >> 1);
  minHnrowsNxBy2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = nd2;
  emxEnsureCapacity_real_T(costab1q, minHnrowsNxBy2);
  costab1q_data = costab1q->data;
  emxInit_real_T(&hsintab, 2);
  minHnrowsNxBy2 = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = nd2;
  emxEnsureCapacity_real_T(hsintab, minHnrowsNxBy2);
  hsintab_data = hsintab->data;
  emxInit_real_T(&hcostabinv, 2);
  minHnrowsNxBy2 = hcostabinv->size[0] * hcostabinv->size[1];
  hcostabinv->size[0] = 1;
  hcostabinv->size[1] = nd2;
  emxEnsureCapacity_real_T(hcostabinv, minHnrowsNxBy2);
  hcostabinv_data = hcostabinv->data;
  emxInit_real_T(&hsintabinv, 2);
  minHnrowsNxBy2 = hsintabinv->size[0] * hsintabinv->size[1];
  hsintabinv->size[0] = 1;
  hsintabinv->size[1] = nd2;
  emxEnsureCapacity_real_T(hsintabinv, minHnrowsNxBy2);
  hsintabinv_data = hsintabinv->data;
  for (i = 0; i < nd2; i++) {
    minHnrowsNxBy2 = ((i + 1) << 1) - 2;
    costab1q_data[i] = costab_data[minHnrowsNxBy2];
    hsintab_data[i] = sintab_data[minHnrowsNxBy2];
    hcostabinv_data[i] = costabinv_data[minHnrowsNxBy2];
    hsintabinv_data[i] = sintabinv_data[minHnrowsNxBy2];
  }
  emxInit_creal_T(&reconVar1, 1);
  minHnrowsNxBy2 = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar1, minHnrowsNxBy2);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  minHnrowsNxBy2 = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar2, minHnrowsNxBy2);
  reconVar2_data = reconVar2->data;
  emxInit_int32_T(&wrapIndex, 2);
  minHnrowsNxBy2 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, minHnrowsNxBy2);
  wrapIndex_data = wrapIndex->data;
  for (i = 0; i < hnRows; i++) {
    minHnrowsNxBy2 = i << 1;
    e = b_sintab_data[minHnrowsNxBy2];
    temp_re = b_costab_data[minHnrowsNxBy2];
    reconVar1_data[i].re = e + 1.0;
    reconVar1_data[i].im = -temp_re;
    reconVar2_data[i].re = 1.0 - e;
    reconVar2_data[i].im = temp_re;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (hnRows - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxFree_real_T(&b_sintab);
  emxFree_real_T(&b_costab);
  if (j > nRows) {
    j = nRows;
  }
  minHnrowsNxBy2 = ((j + (j < 0)) >> 1) - 1;
  for (ju = 0; ju <= minHnrowsNxBy2; ju++) {
    temp_re_tmp = (hnRows + ju) - 1;
    temp_re = wwc_data[temp_re_tmp].re;
    temp_im = wwc_data[temp_re_tmp].im;
    nd2 = xoffInit + (ju << 1);
    twid_re = x_data[nd2];
    twid_im = x_data[nd2 + 1];
    ytmp_data[ju].re = temp_re * twid_re + temp_im * twid_im;
    ytmp_data[ju].im = temp_re * twid_im - temp_im * twid_re;
  }
  if (!tst) {
    temp_re_tmp = hnRows + minHnrowsNxBy2;
    temp_re = wwc_data[temp_re_tmp].re;
    temp_im = wwc_data[temp_re_tmp].im;
    if (minHnrowsNxBy2 < 0) {
      j = xoffInit;
    } else {
      j = xoffInit + ((minHnrowsNxBy2 + 1) << 1);
    }
    twid_re = x_data[j];
    ytmp_data[minHnrowsNxBy2 + 1].re = temp_re * twid_re + temp_im * 0.0;
    ytmp_data[minHnrowsNxBy2 + 1].im = temp_re * 0.0 - temp_im * twid_re;
    if (minHnrowsNxBy2 + 3 <= hnRows) {
      minHnrowsNxBy2 += 3;
      for (i = minHnrowsNxBy2; i <= hnRows; i++) {
        ytmp_data[i - 1].re = 0.0;
        ytmp_data[i - 1].im = 0.0;
      }
    }
  } else if (minHnrowsNxBy2 + 2 <= hnRows) {
    minHnrowsNxBy2 += 2;
    for (i = minHnrowsNxBy2; i <= hnRows; i++) {
      ytmp_data[i - 1].re = 0.0;
      ytmp_data[i - 1].im = 0.0;
    }
  }
  nfft_tmp = (nfft + (nfft < 0)) >> 1;
  emxInit_creal_T(&fy, 1);
  minHnrowsNxBy2 = fy->size[0];
  fy->size[0] = nfft_tmp;
  emxEnsureCapacity_creal_T(fy, minHnrowsNxBy2);
  fy_data = fy->data;
  if (nfft_tmp > ytmp->size[0]) {
    minHnrowsNxBy2 = fy->size[0];
    fy->size[0] = nfft_tmp;
    emxEnsureCapacity_creal_T(fy, minHnrowsNxBy2);
    fy_data = fy->data;
    for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < nfft_tmp; minHnrowsNxBy2++) {
      fy_data[minHnrowsNxBy2].re = 0.0;
      fy_data[minHnrowsNxBy2].im = 0.0;
    }
  }
  j = ytmp->size[0];
  if (j > nfft_tmp) {
    j = nfft_tmp;
  }
  minHnrowsNxBy2 = nfft_tmp - 2;
  nRowsD2 = (nfft_tmp + (nfft_tmp < 0)) >> 1;
  k = (nRowsD2 + (nRowsD2 < 0)) >> 1;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= j - 2; i++) {
    fy_data[nd2] = ytmp_data[i];
    istart = nfft_tmp;
    tst = true;
    while (tst) {
      istart >>= 1;
      ju ^= istart;
      tst = ((ju & istart) == 0);
    }
    nd2 = ju;
  }
  if (j - 2 < 0) {
    j = 0;
  } else {
    j--;
  }
  fy_data[nd2] = ytmp_data[j];
  if (nfft_tmp > 1) {
    for (i = 0; i <= minHnrowsNxBy2; i += 2) {
      b_temp_re_tmp = fy_data[i + 1].re;
      temp_im = fy_data[i + 1].im;
      twid_im = fy_data[i].re;
      e = fy_data[i].im;
      fy_data[i + 1].re = twid_im - b_temp_re_tmp;
      fy_data[i + 1].im = fy_data[i].im - fy_data[i + 1].im;
      e += temp_im;
      fy_data[i].re = twid_im + b_temp_re_tmp;
      fy_data[i].im = e;
    }
  }
  nd2 = 2;
  minHnrowsNxBy2 = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += minHnrowsNxBy2) {
      temp_re_tmp = i + nd2;
      temp_re = fy_data[temp_re_tmp].re;
      temp_im = fy_data[temp_re_tmp].im;
      fy_data[temp_re_tmp].re = fy_data[i].re - temp_re;
      fy_data[temp_re_tmp].im = fy_data[i].im - temp_im;
      fy_data[i].re += temp_re;
      fy_data[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      int ihi;
      twid_re = costab1q_data[j];
      twid_im = hsintab_data[j];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + nd2;
        b_temp_re_tmp = fy_data[temp_re_tmp].im;
        e = fy_data[temp_re_tmp].re;
        temp_re = twid_re * e - twid_im * b_temp_re_tmp;
        temp_im = twid_re * b_temp_re_tmp + twid_im * e;
        fy_data[temp_re_tmp].re = fy_data[i].re - temp_re;
        fy_data[temp_re_tmp].im = fy_data[i].im - temp_im;
        fy_data[i].re += temp_re;
        fy_data[i].im += temp_im;
        i += minHnrowsNxBy2;
      }
      istart++;
    }
    k >>= 1;
    nd2 = minHnrowsNxBy2;
    minHnrowsNxBy2 += minHnrowsNxBy2;
    ju -= nd2;
  }
  emxInit_creal_T(&fv, 1);
  d_FFTImplementationCallback_r2b(wwc, nfft_tmp, costab1q, hsintab, fv);
  fv_data = fv->data;
  emxFree_real_T(&costab1q);
  emxFree_real_T(&hsintab);
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < nfft_tmp; minHnrowsNxBy2++) {
    twid_im = fy_data[minHnrowsNxBy2].re;
    e = fv_data[minHnrowsNxBy2].im;
    temp_re = fy_data[minHnrowsNxBy2].im;
    twid_re = fv_data[minHnrowsNxBy2].re;
    fy_data[minHnrowsNxBy2].re = twid_im * twid_re - temp_re * e;
    fy_data[minHnrowsNxBy2].im = twid_im * e + temp_re * twid_re;
  }
  d_FFTImplementationCallback_r2b(fy, nfft_tmp, hcostabinv, hsintabinv, fv);
  fv_data = fv->data;
  emxFree_creal_T(&fy);
  emxFree_real_T(&hsintabinv);
  emxFree_real_T(&hcostabinv);
  if (fv->size[0] > 1) {
    e = 1.0 / (double)fv->size[0];
    nd2 = fv->size[0];
    for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < nd2; minHnrowsNxBy2++) {
      fv_data[minHnrowsNxBy2].re *= e;
      fv_data[minHnrowsNxBy2].im *= e;
    }
  }
  minHnrowsNxBy2 = wwc->size[0];
  for (k = hnRows; k <= minHnrowsNxBy2; k++) {
    e = wwc_data[k - 1].re;
    temp_re = fv_data[k - 1].im;
    twid_re = wwc_data[k - 1].im;
    twid_im = fv_data[k - 1].re;
    nd2 = k - hnRows;
    ytmp_data[nd2].re = e * twid_im + twid_re * temp_re;
    ytmp_data[nd2].im = e * temp_re - twid_re * twid_im;
  }
  emxFree_creal_T(&fv);
  for (i = 0; i < hnRows; i++) {
    double b_ytmp_re_tmp;
    double ytmp_re_tmp;
    minHnrowsNxBy2 = wrapIndex_data[i];
    e = ytmp_data[i].re;
    temp_re = reconVar1_data[i].im;
    twid_re = ytmp_data[i].im;
    twid_im = reconVar1_data[i].re;
    temp_im = ytmp_data[minHnrowsNxBy2 - 1].re;
    b_temp_re_tmp = -ytmp_data[minHnrowsNxBy2 - 1].im;
    ytmp_re_tmp = reconVar2_data[i].im;
    b_ytmp_re_tmp = reconVar2_data[i].re;
    y_data[i].re =
        0.5 * ((e * twid_im - twid_re * temp_re) +
               (temp_im * b_ytmp_re_tmp - b_temp_re_tmp * ytmp_re_tmp));
    y_data[i].im =
        0.5 * ((e * temp_re + twid_re * twid_im) +
               (temp_im * ytmp_re_tmp + b_temp_re_tmp * b_ytmp_re_tmp));
    minHnrowsNxBy2 = hnRows + i;
    y_data[minHnrowsNxBy2].re =
        0.5 * ((e * b_ytmp_re_tmp - twid_re * ytmp_re_tmp) +
               (temp_im * twid_im - b_temp_re_tmp * temp_re));
    y_data[minHnrowsNxBy2].im =
        0.5 * ((e * ytmp_re_tmp + twid_re * b_ytmp_re_tmp) +
               (temp_im * temp_re + b_temp_re_tmp * twid_im));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal_T(&ytmp);
}

static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  const creal_T *x_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double im;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  y_data = y->data;
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    y_data = y->data;
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }
  iDelta2 = x->size[0];
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = (unsigned_nRows + (unsigned_nRows < 0)) >> 1;
  k = (nRowsD2 + (nRowsD2 < 0)) >> 1;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    bool tst;
    y_data[iy] = x_data[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (iDelta2 - 2 < 0) {
    iDelta2 = 0;
  } else {
    iDelta2--;
  }
  y_data[iy] = x_data[iDelta2];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      im = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
      im += temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_im;
      double twid_re;
      int ihi;
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        im = y_data[b_temp_re_tmp].re;
        temp_re = twid_re * im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      ju++;
    }
    k >>= 1;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

void c_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *r1;
  emxArray_creal_T *wwc;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *r;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *x_data;
  double im;
  double nt_im;
  int b_k;
  int b_y;
  int chan;
  int i;
  int i1;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRows;
  int rt;
  int u0;
  int xoff;
  x_data = x->data;
  emxInit_creal_T(&wwc, 1);
  if ((nfft != 1) && (((unsigned int)nfft & 1U) == 0U)) {
    nRows = (nfft + (nfft < 0)) >> 1;
    nInt2m1 = (nRows + nRows) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nRows - 1].re = 1.0;
    wwc_data[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nRows;
      i = (nRows - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
      i = (nfft - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1] * x->size[2];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  b_y = x->size[1] * x->size[2];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, fv_data, b_fv_data, fv, b_fv, r1, xoff, i1, minNrowsNx, u0, b_k,    \
            im)
  {
    emxInit_creal_T(&fv, 1);
    emxInit_creal_T(&b_fv, 1);
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < b_y; chan++) {
      xoff = chan * nInt2m1;
      i1 = r1->size[0];
      r1->size[0] = nfft;
      emxEnsureCapacity_creal_T(r1, i1);
      r = r1->data;
      if (nfft > x->size[0]) {
        i1 = r1->size[0];
        r1->size[0] = nfft;
        emxEnsureCapacity_creal_T(r1, i1);
        r = r1->data;
        for (i1 = 0; i1 < nfft; i1++) {
          r[i1].re = 0.0;
          r[i1].im = 0.0;
        }
      }
      if ((n2blue != 1) && (((unsigned int)nfft & 1U) == 0U)) {
        d_FFTImplementationCallback_doH(x, xoff, r1, x->size[0], nfft, n2blue,
                                        wwc, costab, sintab, costab, sintabinv);
        r = r1->data;
      } else {
        minNrowsNx = x->size[0];
        if (nfft <= minNrowsNx) {
          minNrowsNx = nfft;
        }
        for (b_k = 0; b_k < minNrowsNx; b_k++) {
          i1 = (nfft + b_k) - 1;
          u0 = xoff + b_k;
          r[b_k].re = wwc_data[i1].re * x_data[u0];
          r[b_k].im = wwc_data[i1].im * -x_data[u0];
        }
        i1 = minNrowsNx + 1;
        for (b_k = i1; b_k <= nfft; b_k++) {
          r[b_k - 1].re = 0.0;
          r[b_k - 1].im = 0.0;
        }
        d_FFTImplementationCallback_r2b(r1, n2blue, costab, sintab, b_fv);
        fv_data = b_fv->data;
        d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
        i1 = fv->size[0];
        fv->size[0] = b_fv->size[0];
        emxEnsureCapacity_creal_T(fv, i1);
        b_fv_data = fv->data;
        u0 = b_fv->size[0];
        for (i1 = 0; i1 < u0; i1++) {
          im = fv_data[i1].re * b_fv_data[i1].im +
               fv_data[i1].im * b_fv_data[i1].re;
          b_fv_data[i1].re = fv_data[i1].re * b_fv_data[i1].re -
                             fv_data[i1].im * b_fv_data[i1].im;
          b_fv_data[i1].im = im;
        }
        d_FFTImplementationCallback_r2b(fv, n2blue, costab, sintabinv, b_fv);
        fv_data = b_fv->data;
        if (b_fv->size[0] > 1) {
          im = 1.0 / (double)b_fv->size[0];
          u0 = b_fv->size[0];
          for (i1 = 0; i1 < u0; i1++) {
            fv_data[i1].re *= im;
            fv_data[i1].im *= im;
          }
        }
        i1 = wwc->size[0];
        for (b_k = nfft; b_k <= i1; b_k++) {
          u0 = b_k - nfft;
          r[u0].re = wwc_data[b_k - 1].re * fv_data[b_k - 1].re +
                     wwc_data[b_k - 1].im * fv_data[b_k - 1].im;
          r[u0].im = wwc_data[b_k - 1].re * fv_data[b_k - 1].im -
                     wwc_data[b_k - 1].im * fv_data[b_k - 1].re;
        }
      }
      xoff = y->size[0];
      u0 = y->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        y_data[i1 + xoff * chan] = r[i1];
      }
    }
    emxFree_creal_T(&r1);
    emxFree_creal_T(&b_fv);
    emxFree_creal_T(&fv);
  }
  emxFree_creal_T(&wwc);
}

void c_FFTImplementationCallback_gen(int nRows, bool useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  nd2 = (nRows + (nRows < 0)) >> 1;
  n = (nd2 + (nd2 < 0)) >> 1;
  emxInit_real_T(&costab1q, 2);
  nd2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, nd2);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = (int)((unsigned int)n >> 1) - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  nd2 += 2;
  for (k = nd2; k < n; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    int n2;
    n = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(costab, nd2);
    costab_data = costab->data;
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintab, nd2);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintabinv, nd2);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    nd2 = costab1q->size[1];
    for (k = nd2; k <= n2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = nd2; k <= n2; k++) {
      costab_data[k] = -costab1q_data[n2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    int n2;
    n = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(costab, nd2);
    costab_data = costab->data;
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintab, nd2);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    nd2 = costab1q->size[1];
    for (k = nd2; k <= n2; k++) {
      costab_data[k] = -costab1q_data[n2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

int c_FFTImplementationCallback_get(int nfft, bool useRadix2, int *nRows)
{
  int n2blue;
  n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    if (nfft > 0) {
      int pmax;
      n2blue = (nfft + nfft) - 1;
      pmax = 31;
      if (n2blue <= 1) {
        pmax = 0;
      } else {
        int pmin;
        bool exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n2blue) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n2blue) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      n2blue = 1 << pmax;
    }
    *nRows = n2blue;
  }
  return n2blue;
}

void c_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r1;
  creal_T *r;
  creal_T *y_data;
  const double *x_data;
  int chan;
  int i;
  int i1;
  int loop_ub;
  int loop_ub_tmp;
  int nrows;
  int xoff;
  x_data = x->data;
  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub_tmp = n1_unsigned * x->size[1] * x->size[2];
    for (i = 0; i < loop_ub_tmp; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  loop_ub_tmp = x->size[1] * x->size[2];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, r1, xoff, i1, loop_ub)
  {
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < loop_ub_tmp; chan++) {
      xoff = chan * nrows;
      i1 = r1->size[0];
      r1->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(r1, i1);
      r = r1->data;
      if (n1_unsigned > x->size[0]) {
        i1 = r1->size[0];
        r1->size[0] = n1_unsigned;
        emxEnsureCapacity_creal_T(r1, i1);
        r = r1->data;
        for (i1 = 0; i1 < n1_unsigned; i1++) {
          r[i1].re = 0.0;
          r[i1].im = 0.0;
        }
      }
      if (n1_unsigned != 1) {
        c_FFTImplementationCallback_doH(x, xoff, r1, n1_unsigned, costab,
                                        sintab);
        r = r1->data;
      } else {
        r[0].re = x_data[xoff];
        r[0].im = 0.0;
      }
      xoff = y->size[0];
      loop_ub = y->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        y_data[i1 + xoff * chan] = r[i1];
      }
    }
    emxFree_creal_T(&r1);
  }
}

void d_FFTImplementationCallback_dob(const emxArray_creal_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *r1;
  emxArray_creal_T *wwc;
  const creal_T *x_data;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *r;
  creal_T *wwc_data;
  creal_T *y_data;
  double a_im;
  double a_re;
  double nt_im;
  int b_k;
  int b_y;
  int chan;
  int i;
  int i1;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  x_data = x->data;
  nInt2m1 = (nfft + nfft) - 1;
  emxInit_creal_T(&wwc, 1);
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, i);
  wwc_data = wwc->data;
  rt = 0;
  wwc_data[nfft - 1].re = 1.0;
  wwc_data[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
    i = (nfft - k) - 2;
    wwc_data[i].re = cos(nt_im);
    wwc_data[i].im = -sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1] * x->size[2];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  b_y = x->size[1] * x->size[2];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, fv_data, b_fv_data, fv, b_fv, r1, xoff, i1, minNrowsNx, b_k, u0,    \
            a_re, a_im)
  {
    emxInit_creal_T(&fv, 1);
    emxInit_creal_T(&b_fv, 1);
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < b_y; chan++) {
      xoff = chan * nInt2m1;
      i1 = r1->size[0];
      r1->size[0] = nfft;
      emxEnsureCapacity_creal_T(r1, i1);
      r = r1->data;
      if (nfft > x->size[0]) {
        i1 = r1->size[0];
        r1->size[0] = nfft;
        emxEnsureCapacity_creal_T(r1, i1);
        r = r1->data;
        for (i1 = 0; i1 < nfft; i1++) {
          r[i1].re = 0.0;
          r[i1].im = 0.0;
        }
      }
      minNrowsNx = x->size[0];
      if (nfft <= minNrowsNx) {
        minNrowsNx = nfft;
      }
      for (b_k = 0; b_k < minNrowsNx; b_k++) {
        u0 = (nfft + b_k) - 1;
        a_re = wwc_data[u0].re;
        a_im = wwc_data[u0].im;
        i1 = xoff + b_k;
        r[b_k].re = a_re * x_data[i1].re + a_im * x_data[i1].im;
        r[b_k].im = a_re * x_data[i1].im - a_im * x_data[i1].re;
      }
      i1 = minNrowsNx + 1;
      for (b_k = i1; b_k <= nfft; b_k++) {
        r[b_k - 1].re = 0.0;
        r[b_k - 1].im = 0.0;
      }
      d_FFTImplementationCallback_r2b(r1, n2blue, costab, sintab, b_fv);
      fv_data = b_fv->data;
      d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      i1 = fv->size[0];
      fv->size[0] = b_fv->size[0];
      emxEnsureCapacity_creal_T(fv, i1);
      b_fv_data = fv->data;
      u0 = b_fv->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        a_re = fv_data[i1].re * b_fv_data[i1].im +
               fv_data[i1].im * b_fv_data[i1].re;
        b_fv_data[i1].re = fv_data[i1].re * b_fv_data[i1].re -
                           fv_data[i1].im * b_fv_data[i1].im;
        b_fv_data[i1].im = a_re;
      }
      d_FFTImplementationCallback_r2b(fv, n2blue, costab, sintabinv, b_fv);
      fv_data = b_fv->data;
      if (b_fv->size[0] > 1) {
        a_re = 1.0 / (double)b_fv->size[0];
        u0 = b_fv->size[0];
        for (i1 = 0; i1 < u0; i1++) {
          fv_data[i1].re *= a_re;
          fv_data[i1].im *= a_re;
        }
      }
      i1 = wwc->size[0];
      for (b_k = nfft; b_k <= i1; b_k++) {
        u0 = b_k - nfft;
        r[u0].re = wwc_data[b_k - 1].re * fv_data[b_k - 1].re +
                   wwc_data[b_k - 1].im * fv_data[b_k - 1].im;
        r[u0].im = wwc_data[b_k - 1].re * fv_data[b_k - 1].im -
                   wwc_data[b_k - 1].im * fv_data[b_k - 1].re;
      }
      xoff = y->size[0];
      u0 = y->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        y_data[i1 + xoff * chan] = r[i1];
      }
    }
    emxFree_creal_T(&r1);
    emxFree_creal_T(&b_fv);
    emxFree_creal_T(&fv);
  }
  emxFree_creal_T(&wwc);
}

void d_FFTImplementationCallback_gen(int nRows, bool useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  nd2 = (nRows + (nRows < 0)) >> 1;
  n = (nd2 + (nd2 < 0)) >> 1;
  emxInit_real_T(&costab1q, 2);
  nd2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, nd2);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = (int)((unsigned int)n >> 1) - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  nd2 += 2;
  for (k = nd2; k < n; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    int n2;
    n = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(costab, nd2);
    costab_data = costab->data;
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintab, nd2);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintabinv, nd2);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    nd2 = costab1q->size[1];
    for (k = nd2; k <= n2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = nd2; k <= n2; k++) {
      costab_data[k] = -costab1q_data[n2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    int n2;
    n = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(costab, nd2);
    costab_data = costab->data;
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(sintab, nd2);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    nd2 = costab1q->size[1];
    for (k = nd2; k <= n2; k++) {
      costab_data[k] = -costab1q_data[n2 - k];
      sintab_data[k] = costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

void e_FFTImplementationCallback_dob(const emxArray_creal_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *r1;
  emxArray_creal_T *wwc;
  const creal_T *x_data;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *r;
  creal_T *wwc_data;
  creal_T *y_data;
  double a_im;
  double a_re;
  double nt_im;
  int b_k;
  int b_y;
  int chan;
  int i;
  int i1;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  x_data = x->data;
  nInt2m1 = (nfft + nfft) - 1;
  emxInit_creal_T(&wwc, 1);
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, i);
  wwc_data = wwc->data;
  rt = 0;
  wwc_data[nfft - 1].re = 1.0;
  wwc_data[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = 3.1415926535897931 * (double)rt / (double)nfft;
    i = (nfft - k) - 2;
    wwc_data[i].re = cos(nt_im);
    wwc_data[i].im = -sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  b_y = x->size[1];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, fv_data, b_fv_data, fv, b_fv, r1, xoff, i1, minNrowsNx, b_k, u0,    \
            a_re, a_im)
  {
    emxInit_creal_T(&fv, 1);
    emxInit_creal_T(&b_fv, 1);
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < b_y; chan++) {
      xoff = chan * nInt2m1;
      i1 = r1->size[0];
      r1->size[0] = nfft;
      emxEnsureCapacity_creal_T(r1, i1);
      r = r1->data;
      if (nfft > x->size[0]) {
        i1 = r1->size[0];
        r1->size[0] = nfft;
        emxEnsureCapacity_creal_T(r1, i1);
        r = r1->data;
        for (i1 = 0; i1 < nfft; i1++) {
          r[i1].re = 0.0;
          r[i1].im = 0.0;
        }
      }
      minNrowsNx = x->size[0];
      if (nfft <= minNrowsNx) {
        minNrowsNx = nfft;
      }
      for (b_k = 0; b_k < minNrowsNx; b_k++) {
        u0 = (nfft + b_k) - 1;
        a_re = wwc_data[u0].re;
        a_im = wwc_data[u0].im;
        i1 = xoff + b_k;
        r[b_k].re = a_re * x_data[i1].re + a_im * x_data[i1].im;
        r[b_k].im = a_re * x_data[i1].im - a_im * x_data[i1].re;
      }
      i1 = minNrowsNx + 1;
      for (b_k = i1; b_k <= nfft; b_k++) {
        r[b_k - 1].re = 0.0;
        r[b_k - 1].im = 0.0;
      }
      d_FFTImplementationCallback_r2b(r1, n2blue, costab, sintab, b_fv);
      fv_data = b_fv->data;
      d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      i1 = fv->size[0];
      fv->size[0] = b_fv->size[0];
      emxEnsureCapacity_creal_T(fv, i1);
      b_fv_data = fv->data;
      u0 = b_fv->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        a_re = fv_data[i1].re * b_fv_data[i1].im +
               fv_data[i1].im * b_fv_data[i1].re;
        b_fv_data[i1].re = fv_data[i1].re * b_fv_data[i1].re -
                           fv_data[i1].im * b_fv_data[i1].im;
        b_fv_data[i1].im = a_re;
      }
      d_FFTImplementationCallback_r2b(fv, n2blue, costab, sintabinv, b_fv);
      fv_data = b_fv->data;
      if (b_fv->size[0] > 1) {
        a_re = 1.0 / (double)b_fv->size[0];
        u0 = b_fv->size[0];
        for (i1 = 0; i1 < u0; i1++) {
          fv_data[i1].re *= a_re;
          fv_data[i1].im *= a_re;
        }
      }
      i1 = wwc->size[0];
      for (b_k = nfft; b_k <= i1; b_k++) {
        a_re = wwc_data[b_k - 1].re * fv_data[b_k - 1].re +
               wwc_data[b_k - 1].im * fv_data[b_k - 1].im;
        a_im = wwc_data[b_k - 1].re * fv_data[b_k - 1].im -
               wwc_data[b_k - 1].im * fv_data[b_k - 1].re;
        if (a_im == 0.0) {
          u0 = b_k - nfft;
          r[u0].re = a_re / (double)nfft;
          r[u0].im = 0.0;
        } else if (a_re == 0.0) {
          u0 = b_k - nfft;
          r[u0].re = 0.0;
          r[u0].im = a_im / (double)nfft;
        } else {
          u0 = b_k - nfft;
          r[u0].re = a_re / (double)nfft;
          r[u0].im = a_im / (double)nfft;
        }
      }
      u0 = y->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        y_data[i1 + y->size[0] * chan] = r[i1];
      }
    }
    emxFree_creal_T(&r1);
    emxFree_creal_T(&b_fv);
    emxFree_creal_T(&fv);
  }
  emxFree_creal_T(&wwc);
}

void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r1;
  const creal_T *x_data;
  creal_T *r;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int b_i;
  int chan;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int j;
  int ju;
  int k;
  int loop_ub_tmp;
  int nRowsD2;
  int nrows;
  int temp_re_tmp;
  int xoff;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub_tmp = n1_unsigned * x->size[1] * x->size[2];
    for (i = 0; i < loop_ub_tmp; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  loop_ub_tmp = x->size[1] * x->size[2];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, r1, xoff, ju, iy, j, iheight, nRowsD2, k, b_i, iDelta2, tst,        \
            temp_re, temp_im, twid_re, twid_im, temp_re_tmp)
  {
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < loop_ub_tmp; chan++) {
      xoff = chan * nrows;
      ju = r1->size[0];
      r1->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(r1, ju);
      r = r1->data;
      if (n1_unsigned > x->size[0]) {
        ju = r1->size[0];
        r1->size[0] = n1_unsigned;
        emxEnsureCapacity_creal_T(r1, ju);
        r = r1->data;
        for (ju = 0; ju < n1_unsigned; ju++) {
          r[ju].re = 0.0;
          r[ju].im = 0.0;
        }
      }
      iy = x->size[0];
      j = n1_unsigned;
      if (iy <= n1_unsigned) {
        j = iy;
      }
      iheight = n1_unsigned - 2;
      nRowsD2 = (n1_unsigned + (n1_unsigned < 0)) >> 1;
      k = (nRowsD2 + (nRowsD2 < 0)) >> 1;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= j - 2; b_i++) {
        r[iy] = x_data[xoff + b_i];
        iDelta2 = n1_unsigned;
        tst = true;
        while (tst) {
          iDelta2 >>= 1;
          ju ^= iDelta2;
          tst = ((ju & iDelta2) == 0);
        }
        iy = ju;
      }
      if (j - 2 >= 0) {
        xoff = (xoff + j) - 1;
      }
      r[iy] = x_data[xoff];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= iheight; b_i += 2) {
          temp_re = r[b_i + 1].re;
          temp_im = r[b_i + 1].im;
          twid_re = r[b_i].re;
          twid_im = r[b_i].im;
          r[b_i + 1].re = r[b_i].re - r[b_i + 1].re;
          r[b_i + 1].im = r[b_i].im - r[b_i + 1].im;
          twid_re += temp_re;
          twid_im += temp_im;
          r[b_i].re = twid_re;
          r[b_i].im = twid_im;
        }
      }
      iy = 2;
      iDelta2 = 4;
      iheight = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (b_i = 0; b_i < iheight; b_i += iDelta2) {
          temp_re_tmp = b_i + iy;
          temp_re = r[temp_re_tmp].re;
          temp_im = r[temp_re_tmp].im;
          r[temp_re_tmp].re = r[b_i].re - temp_re;
          r[temp_re_tmp].im = r[b_i].im - temp_im;
          r[b_i].re += temp_re;
          r[b_i].im += temp_im;
        }
        ju = 1;
        for (j = k; j < nRowsD2; j += k) {
          twid_re = costab_data[j];
          twid_im = sintab_data[j];
          b_i = ju;
          xoff = ju + iheight;
          while (b_i < xoff) {
            temp_re_tmp = b_i + iy;
            temp_re = twid_re * r[temp_re_tmp].re - twid_im * r[temp_re_tmp].im;
            temp_im = twid_re * r[temp_re_tmp].im + twid_im * r[temp_re_tmp].re;
            r[temp_re_tmp].re = r[b_i].re - temp_re;
            r[temp_re_tmp].im = r[b_i].im - temp_im;
            r[b_i].re += temp_re;
            r[b_i].im += temp_im;
            b_i += iDelta2;
          }
          ju++;
        }
        k >>= 1;
        iy = iDelta2;
        iDelta2 += iDelta2;
        iheight -= iy;
      }
      iy = y->size[0];
      iDelta2 = y->size[0];
      for (ju = 0; ju < iDelta2; ju++) {
        y_data[ju + iy * chan] = r[ju];
      }
    }
    emxFree_creal_T(&r1);
  }
}

void f_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r1;
  const creal_T *x_data;
  creal_T *r;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double b;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int b_i;
  int chan;
  int i;
  int iDelta2;
  int ihi;
  int istart;
  int iy;
  int ju;
  int k;
  int loop_ub_tmp;
  int nRowsD2;
  int nrows;
  int temp_re_tmp;
  int xoff;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  nrows = x->size[0];
  i = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub_tmp = n1_unsigned * x->size[1];
    for (i = 0; i < loop_ub_tmp; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  loop_ub_tmp = x->size[1];
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
        r, r1, xoff, ju, iy, istart, iDelta2, nRowsD2, k, b_i, tst, temp_re,   \
            temp_im, twid_re, twid_im, temp_re_tmp, ihi)
  {
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan < loop_ub_tmp; chan++) {
      xoff = chan * nrows;
      ju = r1->size[0];
      r1->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(r1, ju);
      r = r1->data;
      if (n1_unsigned > x->size[0]) {
        ju = r1->size[0];
        r1->size[0] = n1_unsigned;
        emxEnsureCapacity_creal_T(r1, ju);
        r = r1->data;
        for (ju = 0; ju < n1_unsigned; ju++) {
          r[ju].re = 0.0;
          r[ju].im = 0.0;
        }
      }
      iy = x->size[0];
      istart = n1_unsigned;
      if (iy <= n1_unsigned) {
        istart = iy;
      }
      iDelta2 = n1_unsigned - 2;
      nRowsD2 = (n1_unsigned + (n1_unsigned < 0)) >> 1;
      k = (nRowsD2 + (nRowsD2 < 0)) >> 1;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= istart - 2; b_i++) {
        r[iy] = x_data[xoff + b_i];
        iy = n1_unsigned;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }
        iy = ju;
      }
      if (istart - 2 >= 0) {
        xoff = (xoff + istart) - 1;
      }
      r[iy] = x_data[xoff];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= iDelta2; b_i += 2) {
          temp_re = r[b_i + 1].re;
          temp_im = r[b_i + 1].im;
          twid_re = r[b_i].re;
          twid_im = r[b_i].im;
          r[b_i + 1].re = r[b_i].re - r[b_i + 1].re;
          r[b_i + 1].im = r[b_i].im - r[b_i + 1].im;
          twid_re += temp_re;
          twid_im += temp_im;
          r[b_i].re = twid_re;
          r[b_i].im = twid_im;
        }
      }
      iy = 2;
      iDelta2 = 4;
      ju = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (b_i = 0; b_i < ju; b_i += iDelta2) {
          temp_re_tmp = b_i + iy;
          temp_re = r[temp_re_tmp].re;
          temp_im = r[temp_re_tmp].im;
          r[temp_re_tmp].re = r[b_i].re - temp_re;
          r[temp_re_tmp].im = r[b_i].im - temp_im;
          r[b_i].re += temp_re;
          r[b_i].im += temp_im;
        }
        istart = 1;
        for (xoff = k; xoff < nRowsD2; xoff += k) {
          twid_re = costab_data[xoff];
          twid_im = sintab_data[xoff];
          b_i = istart;
          ihi = istart + ju;
          while (b_i < ihi) {
            temp_re_tmp = b_i + iy;
            temp_re = twid_re * r[temp_re_tmp].re - twid_im * r[temp_re_tmp].im;
            temp_im = twid_re * r[temp_re_tmp].im + twid_im * r[temp_re_tmp].re;
            r[temp_re_tmp].re = r[b_i].re - temp_re;
            r[temp_re_tmp].im = r[b_i].im - temp_im;
            r[b_i].re += temp_re;
            r[b_i].im += temp_im;
            b_i += iDelta2;
          }
          istart++;
        }
        k >>= 1;
        iy = iDelta2;
        iDelta2 += iDelta2;
        ju -= iy;
      }
      iy = y->size[0];
      for (ju = 0; ju < iy; ju++) {
        y_data[ju + y->size[0] * chan] = r[ju];
      }
    }
    emxFree_creal_T(&r1);
  }
  if (y->size[0] > 1) {
    b = 1.0 / (double)y->size[0];
    loop_ub_tmp = y->size[0] * y->size[1];
    for (i = 0; i < loop_ub_tmp; i++) {
      y_data[i].re *= b;
      y_data[i].im *= b;
    }
  }
}

/* End of code generation (FFTImplementationCallback.c) */
