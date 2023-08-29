#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  unsigned int result_int = 0;
  float result = 0;
  int bit = 0;
  for (int j = 0; j < 95; j++) {
    bit = get_Bit(src, j);
    result_int |= (bit << j);
  }
  int exponent;
  for (int j = 111; j < 118; j++) {
    bit = get_Bit(src, j);
    exponent |= (bit << j);
  }
  if (exponent < 28) {
    result = ((float)result_int) * (pow(10, exponent));
    int sign_bit = get_Bit(src, 127);
    int sign = (sign_bit == 0) ? 1 : -1;
    printf("%f\n", result);
    *dst = (result)*sign;
  }
  return 0;
}
