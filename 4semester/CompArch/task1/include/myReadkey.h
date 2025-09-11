#ifndef _MY_READKEY_H
#define _MY_READKEY_H

#include "common.h"

enum keys
{
  KEY_NULL = 0,
  KEY_ENTER = 0xa,
  KEY_ESC = 0x1b,
  KEY_PLUS = 0x2b,
  KEY_MINUS = 0x2d,
  KEY_0 = 0x30,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A = 0x41,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_a = 0x61,
  KEY_b,
  KEY_c,
  KEY_d,
  KEY_e,
  KEY_f,
  KEY_g,
  KEY_h,
  KEY_i = 0x69,
  KEY_j,
  KEY_k,
  KEY_l = 0x6C,
  KEY_m,
  KEY_n,
  KEY_o,
  KEY_p,
  KEY_q,
  KEY_r = 0x72,
  KEY_s = 0x73,
  KEY_t = 0x74,
  KEY_u,
  KEY_w,
  KEY_x,
  KEY_y,
  KEY_z,
  KEY_UP = 0x415b1b,
  KEY_DOWN = 0x425b1b,
  KEY_RIGHT = 0x435b1b,
  KEY_LEFT = 0x445b1b,
  KEY_F5 = 0x7e35315b1b,
  KEY_F6 = 0x7e37315b1b,
};

int rk_readkey (enum keys *);

int rk_mytermsave ();

int rk_mytermrestore ();

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);

int rk_readvalue (int *value, int timeout);

#endif // _MY_READKEY_H
