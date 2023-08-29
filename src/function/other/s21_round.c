#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  init_ziro_result(result);

  int res = 0;

  long double number = 0.0;
  from_decimal_to_long_double(value, &number);
  number = roundl(number);
  from_long_double_to_decimal(result, number);
  if (get_sign(value) == 1) set_1_bit(&result->bits[3], 32);

  return res;
}