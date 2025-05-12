/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fftshift.c
 *
 * Code generation for function 'fftshift'
 *
 */

/* Include files */
#include "fftshift.h"
#include "initialize_main_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_fftshift(emxArray_creal_T *x)
{
  creal_T *x_data;
  int b_i;
  int b_k;
  int dim;
  int j;
  int k;
  x_data = x->data;
  k = 3;
  if (x->size[2] == 1) {
    k = 2;
  }
  for (dim = 0; dim < k; dim++) {
    b_k = 3;
    if (x->size[2] == 1) {
      b_k = 2;
    }
    if (dim + 1 <= b_k) {
      int i;
      i = x->size[dim];
      if (i > 1) {
        int lowerDim;
        int midoffset;
        int npages;
        int vlend2;
        int vspread;
        int vstride;
        vlend2 = (int)((unsigned int)i >> 1);
        vstride = 1;
        for (b_k = 0; b_k < dim; b_k++) {
          vstride *= x->size[b_k];
        }
        npages = 1;
        lowerDim = dim + 2;
        for (b_k = lowerDim; b_k < 4; b_k++) {
          npages *= x->size[b_k - 1];
        }
        vspread = (i - 1) * vstride;
        midoffset = vlend2 * vstride - 1;
        if (vlend2 << 1 == i) {
          int i2;
          i2 = 0;
          for (b_i = 0; b_i < npages; b_i++) {
            int i1;
            i1 = i2;
            i2 += vspread;
            for (j = 0; j < vstride; j++) {
              int ib;
              i1++;
              i2++;
              ib = i1 + midoffset;
              for (b_k = 0; b_k < vlend2; b_k++) {
                double xtmp_im;
                double xtmp_re;
                int xtmp_re_tmp;
                lowerDim = b_k * vstride;
                xtmp_re_tmp = (i1 + lowerDim) - 1;
                xtmp_re = x_data[xtmp_re_tmp].re;
                xtmp_im = x_data[xtmp_re_tmp].im;
                i = ib + lowerDim;
                x_data[xtmp_re_tmp] = x_data[i];
                x_data[i].re = xtmp_re;
                x_data[i].im = xtmp_im;
              }
            }
          }
        } else {
          int i2;
          i2 = 0;
          for (b_i = 0; b_i < npages; b_i++) {
            int i1;
            i1 = i2;
            i2 += vspread;
            for (j = 0; j < vstride; j++) {
              double xtmp_im;
              double xtmp_re;
              int ib;
              i1++;
              i2++;
              ib = i1 + midoffset;
              xtmp_re = x_data[ib].re;
              xtmp_im = x_data[ib].im;
              for (b_k = 0; b_k < vlend2; b_k++) {
                lowerDim = ib + vstride;
                i = (i1 + b_k * vstride) - 1;
                x_data[ib] = x_data[i];
                x_data[i] = x_data[lowerDim];
                ib = lowerDim;
              }
              x_data[ib].re = xtmp_re;
              x_data[ib].im = xtmp_im;
            }
          }
        }
      }
    }
  }
}

void c_fftshift(emxArray_real_T *x)
{
  double *x_data;
  int b_i;
  int dim;
  int j;
  int k;
  x_data = x->data;
  for (dim = 0; dim < 2; dim++) {
    int i;
    i = x->size[dim];
    if (i > 1) {
      int lowerDim;
      int midoffset;
      int npages;
      int vlend2;
      int vspread;
      int vstride;
      vlend2 = (int)((unsigned int)i >> 1);
      vstride = 1;
      for (k = 0; k < dim; k++) {
        vstride *= x->size[0];
      }
      npages = 1;
      lowerDim = dim + 2;
      for (k = lowerDim; k < 3; k++) {
        npages *= x->size[1];
      }
      vspread = (i - 1) * vstride;
      midoffset = vlend2 * vstride - 1;
      if (vlend2 << 1 == i) {
        int i2;
        i2 = 0;
        for (b_i = 0; b_i < npages; b_i++) {
          int i1;
          i1 = i2;
          i2 += vspread;
          for (j = 0; j < vstride; j++) {
            int ib;
            i1++;
            i2++;
            ib = i1 + midoffset;
            for (k = 0; k < vlend2; k++) {
              double xtmp;
              int tmp_tmp;
              lowerDim = k * vstride;
              tmp_tmp = (i1 + lowerDim) - 1;
              xtmp = x_data[tmp_tmp];
              i = ib + lowerDim;
              x_data[tmp_tmp] = x_data[i];
              x_data[i] = xtmp;
            }
          }
        }
      } else {
        int i2;
        i2 = 0;
        for (b_i = 0; b_i < npages; b_i++) {
          int i1;
          i1 = i2;
          i2 += vspread;
          for (j = 0; j < vstride; j++) {
            double xtmp;
            int ib;
            i1++;
            i2++;
            ib = i1 + midoffset;
            xtmp = x_data[ib];
            for (k = 0; k < vlend2; k++) {
              lowerDim = ib + vstride;
              i = (i1 + k * vstride) - 1;
              x_data[ib] = x_data[i];
              x_data[i] = x_data[lowerDim];
              ib = lowerDim;
            }
            x_data[ib] = xtmp;
          }
        }
      }
    }
  }
}

void fftshift(emxArray_real_T *x)
{
  double *x_data;
  int b_i;
  int b_k;
  int dim;
  int j;
  int k;
  x_data = x->data;
  k = 3;
  if (x->size[2] == 1) {
    k = 2;
  }
  for (dim = 0; dim < k; dim++) {
    b_k = 3;
    if (x->size[2] == 1) {
      b_k = 2;
    }
    if (dim + 1 <= b_k) {
      int i;
      i = x->size[dim];
      if (i > 1) {
        int lowerDim;
        int midoffset;
        int npages;
        int vlend2;
        int vspread;
        int vstride;
        vlend2 = (int)((unsigned int)i >> 1);
        vstride = 1;
        for (b_k = 0; b_k < dim; b_k++) {
          vstride *= x->size[b_k];
        }
        npages = 1;
        lowerDim = dim + 2;
        for (b_k = lowerDim; b_k < 4; b_k++) {
          npages *= x->size[b_k - 1];
        }
        vspread = (i - 1) * vstride;
        midoffset = vlend2 * vstride - 1;
        if (vlend2 << 1 == i) {
          int i2;
          i2 = 0;
          for (b_i = 0; b_i < npages; b_i++) {
            int i1;
            i1 = i2;
            i2 += vspread;
            for (j = 0; j < vstride; j++) {
              int ib;
              i1++;
              i2++;
              ib = i1 + midoffset;
              for (b_k = 0; b_k < vlend2; b_k++) {
                double xtmp;
                int tmp_tmp;
                lowerDim = b_k * vstride;
                tmp_tmp = (i1 + lowerDim) - 1;
                xtmp = x_data[tmp_tmp];
                i = ib + lowerDim;
                x_data[tmp_tmp] = x_data[i];
                x_data[i] = xtmp;
              }
            }
          }
        } else {
          int i2;
          i2 = 0;
          for (b_i = 0; b_i < npages; b_i++) {
            int i1;
            i1 = i2;
            i2 += vspread;
            for (j = 0; j < vstride; j++) {
              double xtmp;
              int ib;
              i1++;
              i2++;
              ib = i1 + midoffset;
              xtmp = x_data[ib];
              for (b_k = 0; b_k < vlend2; b_k++) {
                lowerDim = ib + vstride;
                i = (i1 + b_k * vstride) - 1;
                x_data[ib] = x_data[i];
                x_data[i] = x_data[lowerDim];
                ib = lowerDim;
              }
              x_data[ib] = xtmp;
            }
          }
        }
      }
    }
  }
}

/* End of code generation (fftshift.c) */
