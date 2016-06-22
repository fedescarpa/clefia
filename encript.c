#include <stdio.h>
#include <stdlib.h>

#define ROUNDS128 18

#define W0_4   0xf0000000
#define W4_8   0x0f000000
#define W8_12  0x00f00000
#define W12_16 0x000f0000
#define W16_20 0x0000f000
#define W20_24 0x00000f00
#define W24_28 0x000000f0
#define W28_32 0x0000000f
#define W0_8   0xff000000
#define W8_16  0x00ff0000
#define W16_24 0x0000ff00
#define W24_32 0x000000ff

#define W0_6   0xfe000000
#define W0_24  0xffffff80
#define W7_31  0x01ffffff
#define W25_31 0x0000007f

#define B0_4   0xf0
#define B4_8   0x0f

char s0[16][16] = {
  0x57, 0x49, 0xd1, 0xc6, 0x2f, 0x33, 0x74, 0xfb, 0x95, 0x6d, 0x82, 0xea, 0x0e, 0xb0, 0xa8, 0x1c,
  0x28, 0xd0, 0x4b, 0x92, 0x5c, 0xee, 0x85, 0xb1, 0xc4, 0x0a, 0x76, 0x3d, 0x63, 0xf9, 0x17, 0xaf,
  0xbf, 0xa1, 0x19, 0x65, 0xf7, 0x7a, 0x32, 0x20, 0x06, 0xce, 0xe4, 0x83, 0x9d, 0x5b, 0x4c, 0xd8,
  0x42, 0x5d, 0x2e, 0xe8, 0xd4, 0x9b, 0x0f, 0x13, 0x3c, 0x89, 0x67, 0xc0, 0x71, 0xaa, 0xb6, 0xf5,
  0xa4, 0xbe, 0xfd, 0x8c, 0x12, 0x00, 0x97, 0xda, 0x78, 0xe1, 0xcf, 0x6b, 0x39, 0x43, 0x55, 0x26,
  0x30, 0x98, 0xcc, 0xdd, 0xeb, 0x54, 0xb3, 0x8f, 0x4e, 0x16, 0xfa, 0x22, 0xa5, 0x77, 0x09, 0x61,
  0xd6, 0x2a, 0x53, 0x37, 0x45, 0xc1, 0x6c, 0xae, 0xef, 0x70, 0x08, 0x99, 0x8b, 0x1d, 0xf2, 0xb4,
  0xe9, 0xc7, 0x9f, 0x4a, 0x31, 0x25, 0xfe, 0x7c, 0xd3, 0xa2, 0xbd, 0x56, 0x14, 0x88, 0x60, 0x0b,
  0xcd, 0xe2, 0x34, 0x50, 0x9e, 0xdc, 0x11, 0x05, 0x2b, 0xb7, 0xa9, 0x48, 0xff, 0x66, 0x8a, 0x73,
  0x03, 0x75, 0x86, 0xf1, 0x6a, 0xa7, 0x40, 0xc2, 0xb9, 0x2c, 0xdb, 0x1f, 0x58, 0x94, 0x3e, 0xed,
  0xfc, 0x1b, 0xa0, 0x04, 0xb8, 0x8d, 0xe6, 0x59, 0x62, 0x93, 0x35, 0x7e, 0xca, 0x21, 0xdf, 0x47,
  0x15, 0xf3, 0xba, 0x7f, 0xa6, 0x69, 0xc8, 0x4d, 0x87, 0x3b, 0x9c, 0x01, 0xe0, 0xde, 0x24, 0x52,
  0x7b, 0x0c, 0x68, 0x1e, 0x80, 0xb2, 0x5a, 0xe7, 0xad, 0xd5, 0x23, 0xf4, 0x46, 0x3f, 0x91, 0xc9,
  0x6e, 0x84, 0x72, 0xbb, 0x0d, 0x18, 0xd9, 0x96, 0xf0, 0x5f, 0x41, 0xac, 0x27, 0xc5, 0xe3, 0x3a,
  0x81, 0x6f, 0x07, 0xa3, 0x79, 0xf6, 0x2d, 0x38, 0x1a, 0x44, 0x5e, 0xb5, 0xd2, 0xec, 0xcb, 0x90,
  0x9a, 0x36, 0xe5, 0x29, 0xc3, 0x4f, 0xab, 0x64, 0x51, 0xf8, 0x10, 0xd7, 0xbc, 0x02, 0x7d, 0x8e};

char s1[16][16] = {
  0x6c, 0xda, 0xc3, 0xe9, 0x4e, 0x9d, 0x0a, 0x3d, 0xb8, 0x36, 0xb4, 0x38, 0x13, 0x34, 0x0c, 0xd9,
  0xbf, 0x74, 0x94, 0x8f, 0xb7, 0x9c, 0xe5, 0xdc, 0x9e, 0x07, 0x49, 0x4f, 0x98, 0x2c, 0xb0, 0x93,
  0x12, 0xeb, 0xcd, 0xb3, 0x92, 0xe7, 0x41, 0x60, 0xe3, 0x21, 0x27, 0x3b, 0xe6, 0x19, 0xd2, 0x0e,
  0x91, 0x11, 0xc7, 0x3f, 0x2a, 0x8e, 0xa1, 0xbc, 0x2b, 0xc8, 0xc5, 0x0f, 0x5b, 0xf3, 0x87, 0x8b,
  0xfb, 0xf5, 0xde, 0x20, 0xc6, 0xa7, 0x84, 0xce, 0xd8, 0x65, 0x51, 0xc9, 0xa4, 0xef, 0x43, 0x53,
  0x25, 0x5d, 0x9b, 0x31, 0xe8, 0x3e, 0x0d, 0xd7, 0x80, 0xff, 0x69, 0x8a, 0xba, 0x0b, 0x73, 0x5c,
  0x6e, 0x54, 0x15, 0x62, 0xf6, 0x35, 0x30, 0x52, 0xa3, 0x16, 0xd3, 0x28, 0x32, 0xfa, 0xaa, 0x5e,
  0xcf, 0xea, 0xed, 0x78, 0x33, 0x58, 0x09, 0x7b, 0x63, 0xc0, 0xc1, 0x46, 0x1e, 0xdf, 0xa9, 0x99,
  0x55, 0x04, 0xc4, 0x86, 0x39, 0x77, 0x82, 0xec, 0x40, 0x18, 0x90, 0x97, 0x59, 0xdd, 0x83, 0x1f,
  0x9a, 0x37, 0x06, 0x24, 0x64, 0x7c, 0xa5, 0x56, 0x48, 0x08, 0x85, 0xd0, 0x61, 0x26, 0xca, 0x6f,
  0x7e, 0x6a, 0xb6, 0x71, 0xa0, 0x70, 0x05, 0xd1, 0x45, 0x8c, 0x23, 0x1c, 0xf0, 0xee, 0x89, 0xad,
  0x7a, 0x4b, 0xc2, 0x2f, 0xdb, 0x5a, 0x4d, 0x76, 0x67, 0x17, 0x2d, 0xf4, 0xcb, 0xb1, 0x4a, 0xa8,
  0xb5, 0x22, 0x47, 0x3a, 0xd5, 0x10, 0x4c, 0x72, 0xcc, 0x00, 0xf9, 0xe0, 0xfd, 0xe2, 0xfe, 0xae,
  0xf8, 0x5f, 0xab, 0xf1, 0x1b, 0x42, 0x81, 0xd6, 0xbe, 0x44, 0x29, 0xa6, 0x57, 0xb9, 0xaf, 0xf2,
  0xd4, 0x75, 0x66, 0xbb, 0x68, 0x9f, 0x50, 0x02, 0x01, 0x3c, 0x7f, 0x8d, 0x1a, 0x88, 0xbd, 0xac,
  0xf7, 0xe4, 0x79, 0x96, 0xa2, 0xfc, 0x6d, 0xb2, 0x6b, 0x03, 0xe1, 0x2e, 0x7d, 0x14, 0x95, 0x1d};

unsigned int con_128[60] = {
  0xf56b7aeb, 0x994a8a42, 0x96a4bd75, 0xfa854521,
  0x735b768a, 0x1f7abac4, 0xd5bc3b45, 0xb99d5d62,
  0x52d73592, 0x3ef636e5, 0xc57a1ac9, 0xa95b9b72,
  0x5ab42554, 0x369555ed, 0x1553ba9a, 0x7972b2a2,
  0xe6b85d4d, 0x8a995951, 0x4b550696, 0x2774b4fc,
  0xc9bb034b, 0xa59a5a7e, 0x88cc81a5, 0xe4ed2d3f,
  0x7c6f68e2, 0x104e8ecb, 0xd2263471, 0xbe07c765,
  0x511a3208, 0x3d3bfbe6, 0x1084b134, 0x7ca565a7,
  0x304bf0aa, 0x5c6aaa87, 0xf4347855, 0x9815d543,
  0x4213141a, 0x2e32f2f5, 0xcd180a0d, 0xa139f97a,
  0x5e852d36, 0x32a464e9, 0xc353169b, 0xaf72b274,
  0x8db88b4d, 0xe199593a, 0x7ed56d96, 0x12f434c9,
  0xd37b36cb, 0xbf5a9a64, 0x85ac9b65, 0xe98d4d32,
  0x7adf6582, 0x16fe3ecd, 0xd17e32c1, 0xbd5f9f66,
  0x50b63150, 0x3c9757e7, 0x1052b098, 0x7c73b3a7
};

unsigned int con_192[84] = {
  0xc6d61d91, 0xaaf73771, 0x5b6226f8, 0x374383ec,
  0x15b8bb4c, 0x799959a2, 0x32d5f596, 0x5ef43485,
  0xf57b7acb, 0x995a9a42, 0x96acbd65, 0xfa8d4d21,
  0x735f7682, 0x1f7ebec4, 0xd5be3b41, 0xb99f5f62,
  0x52d63590, 0x3ef737e5, 0x1162b2f8, 0x7d4383a6,
  0x30b8f14c, 0x5c995987, 0x2055d096, 0x4c74b497,
  0xfc3b684b, 0x901ada4b, 0x920cb425, 0xfe2ded25,
  0x710f7222, 0x1d2eeec6, 0xd4963911, 0xb8b77763,
  0x524234b8, 0x3e63a3e5, 0x1128b26c, 0x7d09c9a6,
  0x309df106, 0x5cbc7c87, 0xf45f7883, 0x987ebe43,
  0x963ebc41, 0xfa1fdf21, 0x73167610, 0x1f37f7c4,
  0x01829338, 0x6da363b6, 0x38c8e1ac, 0x54e9298f,
  0x246dd8e6, 0x484c8c93, 0xfe276c73, 0x9206c649,
  0x9302b639, 0xff23e324, 0x7188732c, 0x1da969c6,
  0x00cd91a6, 0x6cec2cb7, 0xec7748d3, 0x8056965b,
  0x9a2aa469, 0xf60bcb2d, 0x751c7a04, 0x193dfdc2,
  0x02879532, 0x6ea666b5, 0xed524a99, 0x8173b35a,
  0x4ea00d7c, 0x228141f9, 0x1f59ae8e, 0x7378b8a8,
  0xe3bd5747, 0x8f9c5c54, 0x9dcfaba3, 0xf1ee2e2a,
  0xa2f6d5d1, 0xced71715, 0x697242d8, 0x055393de,
  0x0cb0895c, 0x609151bb, 0x3e51ec9e, 0x5270b089
};

#define WORD_FROM_BYTES(_a,_b,_c,_d) (unsigned int)(((_a << 24) | 0x00ffffff) & ((_b << 16) | 0xff00ffff ) & ((_c << 8) | 0xffff00ff) & (_d | 0xffffff00));

unsigned int word_from_bytes(char a, char b, char c, char d) {
  unsigned int res = 0;
  res = ((a << 24) | 0x00ffffff) & ((b << 16) | 0xff00ffff ) & ((c << 8) | 0xffff00ff) & (d | 0xffffff00);
  return res;
}

char byte_from_word(unsigned int x, int off) {
  if (off == 3) {
    return x & W24_32;
  }
  if (off == 2) {
    return (x & W16_24)	>> 8;
  }
  if (off == 1) {
    return (x & W8_16) >> 16;
  }
  return (x & W0_8) >> 24;
}

unsigned char mul2(unsigned char x) {
  /* multiplicacao em GF(2^8) (p(x) = '11d') */
  if(x & 0x80U){
    x ^= 0x0eU;
  }
  return ((x << 1) | (x >> 7));
}

#define mul4(_x) (mul2(mul2((_x))))
#define mul6(_x) (mul2((_x)) ^ mul4((_x)))
#define mul8(_x) (mul2(mul4((_x))))
#define mulA(_x) (mul2((_x)) ^ mul8((_x)))

unsigned int f0(unsigned int rk, unsigned int x) {
  /* Step 1 */
  unsigned int t = rk ^ x;
  /* Step 2 */
  char t0 = (t & W0_8) >> 24;
  char t1 = (t & W8_16) >> 16;
  char t2 = (t & W16_24) >> 8;
  char t3 = t & W24_32;
  t0 = s0[(t0 & B0_4) >> 4][t0 & B4_8];
  t1 = s1[(t1 & B0_4) >> 4][t1 & B4_8];
  t2 = s0[(t2 & B0_4) >> 4][t2 & B4_8];
  t3 = s1[(t3 & B0_4) >> 4][t3 & B4_8];
  /* Step 3 */
  char y0 =      t0  ^ mul2(t1) ^ mul4(t2) ^ mul6(t3);
  char y1 = mul2(t0) ^      t1  ^ mul6(t2) ^ mul4(t3);
  char y2 = mul4(t0) ^ mul6(t1) ^      t2  ^ mul2(t3);
  char y3 = mul6(t0) ^ mul4(t1) ^ mul2(t2) ^       t3;
  unsigned int y = WORD_FROM_BYTES(y0, y1, y2, y3);
  return y;
}

unsigned int f1(unsigned int rk, unsigned int x) {
  /* Step 1 */
  unsigned int t = rk ^ x;
  /* Step 2 */
  char t0 = (t & W0_8) >> 24;
  char t1 = (t & W8_16) >> 16;
  char t2 = (t & W16_24) >> 8;
  char t3 = t & W24_32;
  t0 = s1[(t0 & B0_4) >> 4][t0 & B4_8];
  t1 = s0[(t1 & B0_4) >> 4][t1 & B4_8];
  t2 = s1[(t2 & B0_4) >> 4][t2 & B4_8];
  t3 = s0[(t3 & B0_4) >> 4][t3 & B4_8];
  /* Step 3 */
  char y0 =      t0  ^ mul8(t1) ^ mul2(t2) ^ mulA(t3);
  char y1 = mul8(t0) ^      t1  ^ mulA(t2) ^ mul2(t3);
  char y2 = mul2(t0) ^ mulA(t1) ^      t2  ^ mul8(t3);
  char y3 = mulA(t0) ^ mul2(t1) ^ mul8(t2) ^       t3;
  return WORD_FROM_BYTES(y0, y1, y2, y3);
}

void gfn4(int r, unsigned int* rk, unsigned int *x, unsigned int *y) {
  int i;
  unsigned int temp;
  /* Step 1 */
  unsigned int t0 = x[0];
  unsigned int t1 = x[1];
  unsigned int t2 = x[2];
  unsigned int t3 = x[3];
  /* Step 2 */
  for (i = 0; i < r; i++) {
    /* Step 2.1 */
    t1 ^= f0(rk[2*i], t0);
    t3 ^= f1(rk[2*i + 1], t2);
    /* Step 2.2 */
    temp = t0;
    t0 = t1;
    t1 = t2;
    t2 = t3;
    t3 = temp;
  }
  /* Step 3 */
  y[0] = t3;
  y[1] = t0;
  y[2] = t1;
  y[3] = t2;
}

void gfn8(int r, unsigned int* rk, unsigned int *x, unsigned int *y) {
  int i;
  unsigned int temp;
  /* Step 1 */
  unsigned int t0 = x[0];
  unsigned int t1 = x[1];
  unsigned int t2 = x[2];
  unsigned int t3 = x[3];
  unsigned int t4 = x[4];
  unsigned int t5 = x[5];
  unsigned int t6 = x[6];
  unsigned int t7 = x[7];
  /* Step 2 */
  for (i = 0; i < r; i++) {
    /* Step 2.1 */
    t1 ^= f0(rk[4*i], t0);
    t3 ^= f1(rk[4*i + 1], t2);
    t5 ^= f0(rk[4*1 + 2], t4);
    t7 ^= f1(rk[4*i + 3], t6);
    /* Step 2.2 */
    temp = t0;
    t0 = t1;
    t1 = t2;
    t2 = t3;
    t3 = t4;
    t4 = t5;
    t5 = t6;
    t6 = t7;
    t7 = temp;
  }
  /* Step 3 */
  y[0] = t7;
  y[1] = t0;
  y[2] = t1;
  y[3] = t2;
  y[4] = t3;
  y[5] = t4;
  y[6] = t5;
  y[7] = t6;
}

void gfn_inv4(int r, unsigned int* rk, unsigned int *x, unsigned int *y) {
  int i;
  unsigned int temp0;
  unsigned int temp1;
  unsigned int temp2;
  unsigned int temp3;
  /* Step 1 */
  unsigned int t0 = x[0];
  unsigned int t1 = x[1];
  unsigned int t2 = x[2];
  unsigned int t3 = x[3];
  /* Step 2 */
  for (i = 0; i < r; i++) {
    /* Step 2.1 */
    t1 ^= f0(rk[2*(r-i) - 2], t0);
    t3 ^= f1(rk[2*(r-i) - 1], t2);
    /* Step 2.2 */
    temp0 = t0;
    temp1 = t1;
    temp2 = t2;
    temp3 = t3;
    t0 = temp3;
    t1 = temp0;
    t2 = temp1;
    t3 = temp2;
  }
  /* Step 3 */
  y[0] = t1;
  y[1] = t2;
  y[2] = t3;
  y[3] = t0;
}

void sigma(unsigned int *x, unsigned int* y) {

  y[0] = ((x[0] & W7_31) << 7)   | ((x[1] & W0_6) >> 25);
  y[1] = ((x[1] & W7_31) << 7)   | (x[3]  & W25_31);
  y[2] = (x[0]  & W0_6)          | ((x[2] & W0_24) >> 7);
  y[3] = ((x[2] & W25_31) << 25) | ((x[3] & W0_24) >> 7);
}

void key_scheduling_192(unsigned int *k, unsigned int *wk, unsigned int* rk) {
  unsigned int kl[4], kr[4], ll[4], lr[4], t[4];
  unsigned int y[8], x[8];
  int i;

  /*step 2*/
  kl[0] = k[0];
  kl[1] = k[1];
  kl[2] = k[2];
  kl[3] = k[3];

  kr[0] = k[4];
  kr[1] = k[5];
  kr[2] = ~k[0];
  kr[3] = ~k[1];

  /*step 3*/
  x[0] = kl[0];
  x[1] = kl[1];
  x[2] = kl[2];
  x[3] = kl[3];
  x[4] = kr[0];
  x[5] = kr[1];
  x[6] = kr[2];
  x[7] = kr[3];

  gfn8(10, con_192, x, y);

  ll[0] = y[0];
  ll[1] = y[1];
  ll[2] = y[2];
  ll[3] = y[3];

  lr[0] = y[4];
  lr[1] = y[5];
  lr[2] = y[6];
  lr[3] = y[7];

  printf("LL: \n");
  for (i = 0; i < 4; i++) {
    printf("%08x ", ll[i]);
  }
  printf("\n");

  printf("LR: \n");
  for (i = 0; i < 4; i++) {
    printf("%08x ", lr[i]);
  }
  printf("\n");

  /* step 4 */
  wk[0] = kl[0] ^ kr[0];
  wk[1] = kl[1] ^ kr[1];
  wk[2] = kl[2] ^ kr[2];
  wk[3] = kl[3] ^ kr[3];

  /* step 5 */
  for (i = 0; i <= 10; i++) {
    if (i % 4 == 0 || i % 4 == 1) {
      t[0] = ll[0] ^ con_192[40 + 4*i];
      t[1] = ll[1] ^ con_192[40 + 4*i + 1];
      t[2] = ll[2] ^ con_192[40 + 4*i + 2];
      t[3] = ll[3] ^ con_192[40 + 4*i + 3];
      sigma(ll, y);
      ll[0] = y[0];
      ll[1] = y[1];
      ll[2] = y[2];
      ll[3] = y[3];
      if (i % 2 == 1) {
        t[0] = t[0] ^ kr[0];
        t[1] = t[1] ^ kr[1];
        t[2] = t[2] ^ kr[2];
        t[3] = t[3] ^ kr[3];
      }
    }
    else {
      t[0] = lr[0] ^ con_192[40 + 4*i];
      t[1] = lr[1] ^ con_192[40 + 4*i + 1];
      t[2] = lr[2] ^ con_192[40 + 4*i + 2];
      t[3] = lr[3] ^ con_192[40 + 4*i + 3];
      sigma(lr, y);
      lr[0] = y[0];
      lr[1] = y[1];
      lr[2] = y[2];
      lr[3] = y[3];
      if (i % 2 == 1) {
        t[0] = t[0] ^ kl[0];
        t[1] = t[1] ^ kl[1];
        t[2] = t[2] ^ kl[2];
        t[3] = t[3] ^ kl[3];
      }
    }
    rk[4*i] = t[0];
    rk[4*i+1] = t[1];
    rk[4*i+2] = t[2];
    rk[4*i+3] = t[3];
  }
}


void encryption_192(unsigned int *p, unsigned int *c, unsigned int *k) {

  unsigned int t[4];
  unsigned int wk[4];
  unsigned int rk[44];
  unsigned int y[4];

  key_scheduling_192(k, wk, rk);

  /* step 1 */
  t[0] = p[0];
  t[1] = p[1] ^ wk[0];
  t[2] = p[2];
  t[3] = p[3] ^ wk[1];



  /* step 2 */
  gfn4(22, rk, t, y);
  t[0] = y[0];
  t[1] = y[1];
  t[2] = y[2];
  t[3] = y[3];

  /* step 3 */
  c[0] = t[0];
  c[1] = t[1] ^ wk[2];
  c[2] = t[2];
  c[3] = t[3] ^ wk[3];
}

void decryption_192(unsigned int *p, unsigned int *c, unsigned int * k) {

  unsigned int t[4];
  unsigned int wk[4];
  unsigned int rk[44];
  unsigned int y[4];

  key_scheduling_192(k, wk, rk);

  /* step 1 */
  t[0] = c[0];
  t[1] = c[1] ^ wk[2];
  t[2] = c[2];
  t[3] = c[3] ^ wk[3];

  /* step 2 */
  gfn_inv4(22, rk, t, y);
  t[0] = y[0];
  t[1] = y[1];
  t[2] = y[2];
  t[3] = y[3];

  /* step 3 */
  p[0] = t[0];
  p[1] = t[1] ^ wk[0];
  p[2] = t[2];
  p[3] = t[3] ^ wk[1];
}

void key_scheduling_128(unsigned int *k, unsigned int *wk, unsigned int *rk) {

  unsigned int y[4];
  unsigned int l[4];
  unsigned int t[4];
  int i;

  /* step 1 */
  gfn4(12, con_128, k, y);
  l[0] = y[0];
  l[1] = y[1];
  l[2] = y[2];
  l[3] = y[3];

  /* step 2 */
  wk[0] = k[0];
  wk[1] = k[1];
  wk[2] = k[2];
  wk[3] = k[3];

  /* step 3 */
  for (i = 0; i < 9; i++) {
    t[0] = l[0] ^ con_128[24 + 4 * i];
    t[1] = l[1] ^ con_128[24 + 4 * i + 1];
    t[2] = l[2] ^ con_128[24 + 4 * i + 2];
    t[3] = l[3] ^ con_128[24 + 4 * i + 3];

    sigma(l, y);
    l[0] = y[0];
    l[1] = y[1];
    l[2] = y[2];
    l[3] = y[3];

    if (i % 2 == 1) {
      t[0] = t[0] ^ k[0];
      t[1] = t[1] ^ k[1];
      t[2] = t[2] ^ k[2];
      t[3] = t[3] ^ k[3];
    }

    rk[4*i] = t[0];
    rk[4*i+1] = t[1];
    rk[4*i+2] = t[2];
    rk[4*i+3] = t[3];
  }
}

void encryption_128(unsigned int *p, unsigned int *c, unsigned int *wk, unsigned int* rk) {

  unsigned int t[4];
  unsigned int y[4];


  /* step 1 */
  t[0] = p[0];
  t[1] = p[1] ^ wk[0];
  t[2] = p[2];
  t[3] = p[3] ^ wk[1];



  /* step 2 */
  gfn4(18, rk, t, y);
  t[0] = y[0];
  t[1] = y[1];
  t[2] = y[2];
  t[3] = y[3];

  /* step 3 */
  c[0] = t[0];
  c[1] = t[1] ^ wk[2];
  c[2] = t[2];
  c[3] = t[3] ^ wk[3];
}

void decryption_128(unsigned int *p, unsigned int *c, unsigned int *wk, unsigned int* rk) {

  unsigned int t[4];
  unsigned int y[4];


  /* step 1 */
  t[0] = c[0];
  t[1] = c[1] ^ wk[2];
  t[2] = c[2];
  t[3] = c[3] ^ wk[3];

  /* step 2 */
  gfn_inv4(18, rk, t, y);
  t[0] = y[0];
  t[1] = y[1];
  t[2] = y[2];
  t[3] = y[3];

  /* step 3 */
  p[0] = t[0];
  p[1] = t[1] ^ wk[0];
  p[2] = t[2];
  p[3] = t[3] ^ wk[1];
}

void clefia_cbc_128_dec(char * plain, char * cipher, int length, unsigned int* iv, unsigned int *k) {

  unsigned int p[4];
  unsigned int c[4];
  unsigned int aux[4];

  unsigned int wk[4];
  unsigned int rk[36];


  int j;
  int i = 0;

  int tam = length;

  if (tam % 16 != 0) {
    for (j = tam % 16; j < 16; j++) {
      cipher[tam++] = 0;
    }
  }

  for (j = 0; j < 4; j++) {
    aux[j] = iv[j];
  }

  key_scheduling_128(k, wk, rk);

  while (i < tam) {
    for (j = 0; j < 4; j++) {
      c[j] = WORD_FROM_BYTES(cipher[i+4*j], cipher[i+4*j+1], cipher[i+4*j+2], cipher[i+4*j+3]);
    }
    decryption_128(p, c, wk, rk);

    for (j = 0; j < 16; j++) {
      plain[i+j] = byte_from_word(p[j/4], j%4) ^ byte_from_word(aux[j/4], j%4);
    }

    for (j = 0; j < 4; j++) {
      aux[j] = c[j];
    }

    i = i + 16;
  }
}

void clefia_cbc_128_enc(char* plain, char * cipher, int length, unsigned int* iv, unsigned int *k) {

  unsigned int p[4];
  unsigned int c[4];
  unsigned int wk[4];
  unsigned int rk[36];

  int j;
  int i = 0;

  int tam = length;

  if (tam % 16 != 0) {
    for (j = tam % 16; j < 16; j++) {
      plain[tam++] = 0;
    }
  }

  c[0] = iv[0];
  c[1] = iv[1];
  c[2] = iv[2];
  c[3] = iv[3];

  key_scheduling_128(k, wk, rk);

  while (i < tam) {

    unsigned int bla0 = WORD_FROM_BYTES(plain[i+4*0],plain[i+4*0+1],plain[i+4*0+2],plain[i+4*0+3]);
    unsigned int bla1 = WORD_FROM_BYTES(plain[i+4*1],plain[i+4*1+1],plain[i+4*1+2],plain[i+4*1+3]);
    unsigned int bla2 = WORD_FROM_BYTES(plain[i+4*2],plain[i+4*2+1],plain[i+4*2+2],plain[i+4*2+3]);
    unsigned int bla3 = WORD_FROM_BYTES(plain[i+4*3],plain[i+4*3+1],plain[i+4*3+2],plain[i+4*3+3]);

    p[0] = bla0 ^ c[0];
    p[1] = bla1 ^ c[1];
    p[2] = bla2 ^ c[2];
    p[3] = bla3 ^ c[3];


    encryption_128(p, c, wk, rk);

    cipher[i+0] = byte_from_word(c[0/4], 0 % 4);
    cipher[i+1] = byte_from_word(c[1/4], 1 % 4);
    cipher[i+2] = byte_from_word(c[2/4], 2 % 4);
    cipher[i+3] = byte_from_word(c[3/4], 3 % 4);
    cipher[i+4] = byte_from_word(c[4/4], 4 % 4);
    cipher[i+5] = byte_from_word(c[5/4], 5 % 4);
    cipher[i+6] = byte_from_word(c[6/4], 6 % 4);
    cipher[i+7] = byte_from_word(c[7/4], 7 % 4);
    cipher[i+8] = byte_from_word(c[8/4], 8 % 4);
    cipher[i+9] = byte_from_word(c[9/4], 9 % 4);
    cipher[i+10] = byte_from_word(c[10/4], 10 % 4);
    cipher[i+11] = byte_from_word(c[11/4], 11 % 4);
    cipher[i+12] = byte_from_word(c[12/4], 12 % 4);
    cipher[i+13] = byte_from_word(c[13/4], 13 % 4);
    cipher[i+14] = byte_from_word(c[14/4], 14 % 4);
    cipher[i+15] = byte_from_word(c[15/4], 15 % 4);
    i = i + 16;
  }
}

/* Retorna 1 se vetores são iguais, 0 c.c. */
int equal(unsigned int* a, unsigned int* b, unsigned int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (a[i] != b[i])
      return 0;
  }
  return 1;
}

int main(int argc, char **argv) {

  if (argc < 3) {
    printf("Usage: %s <entrada> <cifrado>", argv[0]);
    exit(1);
  }

  char* program = argv[0];
  char* origin = argv[1];
  char* destiny = argv[2];
  
  unsigned int key_128[4] = {0x01234567,
                             0x89abcdef,
                             0x01234567,
                             0x89abcdef};

  unsigned int iv_128[4] = {0x01234567,
                            0x89abcdef,
                            0x01234567,
                            0x89abcdef};

  int tamanio = 300*1024*1024;
  int blockSize = 16;

  char *data = (char*)malloc(sizeof(char) * tamanio);

  FILE *f;
  int nread;

  printf("Leyendo entrada %s...\n", origin);
  f = fopen(origin, "r");
  nread = fread(data, sizeof(char), tamanio, f);
  fclose(f);
  printf("Bytes read: %d\n", nread);
  

  int realSize = nread + blockSize - (nread % blockSize);
  printf("Bytes read: %d\n", realSize);
  for (int i = nread; i < realSize; i++) data[i] = 0;



  char *cipher = (char*)malloc(sizeof(char) * tamanio);

  printf("Cifrando...\n");
  clefia_cbc_128_enc(data, cipher, realSize, iv_128, key_128);
  printf("Cifrado completo\n");

  printf("Guardando archivo cifrado %s...\n", destiny);
  f = fopen(destiny, "w");
  fwrite(cipher, sizeof(char), nread, f);
  fclose(f);
  printf("Archivo cifrado satisfactoriamente\n");

  free(cipher);
  free(data);

  return 0;
}
