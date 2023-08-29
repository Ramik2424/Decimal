#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  int bit = 0;

  if (src.bits[1] != 0 || src.bits[2] != 0) return 1;

  for (int i = 0; i != 2; i++) {
    for (int j = 0; j < 31; j++) {
      bit = get_Bit(src, j);
      result |= (bit << j);
    }
  }

  int sign_bit = get_Bit(src, 127);
  int sign = (sign_bit == 0) ? 1 : -1;

  *dst = result * sign;
  return 0;
}
