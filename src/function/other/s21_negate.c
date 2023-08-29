#include "../../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  init_ziro_result(result);
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];
  if (get_sign(value) == 1) {
    set_0_bit(&result->bits[3], 31);
  } else {
    set_1_bit(&result->bits[3], 31);
  }
  return res;
}
