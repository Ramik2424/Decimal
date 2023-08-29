#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  correct_decimal(&value_1);
  correct_decimal(&value_2);

  init_ziro_result(result);

  int sign_value1 = get_sign(value_1);
  int sign_value2 = get_sign(value_2);

  int v1_bits = take_value_of_bits(value_1);
  int v2_bits = take_value_of_bits(value_2);
  int sum_bits = v1_bits + v2_bits;

  s21_decimal prel_res = {0};

  if (sum_bits > 96 && sign_value1 == sign_value2) return 1;
  if (sum_bits > 96 && sign_value1 != sign_value2) return 2;

  if (s21_is_less(value_1, value_2)) {
    s21_decimal temp = {0};
    int tmp_bits = 0;
    temp = value_2;
    value_2 = value_1;
    value_1 = temp;
    tmp_bits = v2_bits;
    v2_bits = v1_bits;
    v1_bits = tmp_bits;
  }

  sign_value1 == sign_value2 ? set_0_bit(&(result->bits[3]), 31)
                             : set_1_bit(&(result->bits[3]), 31);

  for (int i = 0; i < v2_bits; i++) {
    int j = 0;
    if (i > 31) j = 1;
    if (get_bit(value_2.bits[j], i - (j * 32))) {
      s21_decimal buff = {0};
      buff = value_1;
      shift_left(&buff, i);
      s21_add(prel_res, buff, &prel_res);
    }
  }

  int result_scale = 0;
  result_scale = get_scale(value_1) + get_scale(value_2);
  result->bits[0] = prel_res.bits[0];
  result->bits[1] = prel_res.bits[1];
  result->bits[2] = prel_res.bits[2];
  if ((result->bits[0] == 0) && (result->bits[1] == 0) &&
      (result->bits[2] == 0)) {
    result_scale = 0;
    set_0_bit(&(result->bits[3]), 31);
  }
  set_scale(&(result->bits[3]), result_scale);
  return 0;
}