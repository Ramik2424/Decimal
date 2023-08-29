#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  if (((src > 0.0) && (fabs(src) < 1e-28)) || (fabs(src) == S21_INF)) {
    flag = 1;
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
  } else {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    int sign = (src > 0) ? 0 : 1;
    float abs_src = fabs(src);

    char str[999] = "";
    char float_str[999] = "";
    sprintf(str, "%E", abs_src);
    puts(str);
    for (int i = 0; i < 8; i++) {
      float_str[i] = str[i];
    }
    double float_val = atof(float_str);

    int val = (int)(float_val * 1000000);

    s21_from_int_to_decimal(val, dst);
    char exponent_str[1] = "";
    int exponent = 0;
    exponent_str[0] = str[10];
    exponent_str[1] = str[11];
    exponent = (int)atof(exponent_str);

    if (exponent == 0) {
      // for (int i = 111; i <= 118; i++) {
      //   set_bit(dst, i, (exponent % 2));
      //   exponent /= 2;
      // }

      for (size_t i = 0; i < strlen(float_str); i++) {
        if (float_str[i] == '.') {
          dst->bits[3] = (((int)strlen(float_str) - 1) - i) << 16;
          break;
        }
      }
      if (sign == 1) dst->bits[3] |= 1 << 31;
    }
  }
  return (flag);
}
