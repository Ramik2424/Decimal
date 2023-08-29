#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }

  int sign = (src >= 0) ? 1 : -1;
  int bin = 0;
  if (src < 0) {
    bin = src * (-1);
  } else {
    bin = src;
  }

  for (int i = 0; i < 95; i++) {
    set_bit(dst, i, (bin % 2));
    bin = bin / 2;
  }
  if (sign == -1) {
    set_bit(dst, 127, 1);
  }
  return 0;
}
