#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  correct_decimal(&value_1);
  correct_decimal(&value_2);

  init_ziro_result(result);

  int sign_value1 = get_sign(value_1);
  int sign_value2 = get_sign(value_2);

  unsigned int sub_bits = 0;
  int bit_2 = 0;
  unsigned int res_sub = 0;

  equalize_scale(&value_1, &value_2);
  set_scale(&(result->bits[3]), get_scale(value_1));

  get_sign(value_1) ? set_1_bit(&(result->bits[3]), 31)
                    : set_0_bit(&(result->bits[3]), 31);

  if (sign_value1 == sign_value2) {
    if (s21_is_less(value_1, value_2)) {
      s21_decimal tmp = value_1;
      tmp = value_2;
      value_2 = value_1;
      value_1 = tmp;
      s21_negate(*result, result);
    }
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        sub_bits = get_bit(value_1.bits[j], i);
        bit_2 = get_bit(value_2.bits[j], i);

        if (sub_bits && bit_2) {
          set_0_bit(&res_sub, i);
        } else if (sub_bits && !bit_2) {
          set_1_bit(&res_sub, i);
        } else if (!sub_bits && !bit_2) {
          set_0_bit(&res_sub, i);
        } else {
          if (i != 31 && j != 2) {
            take_1_bit(&(value_1.bits[j]), i);
          } else if ((i != 31) && (j == 2)) {
            take_1_bit(&(value_1.bits[j]), i);
          } else if ((i == 31) && (j != 2)) {
            take_1_bit(&(value_1.bits[j + 1]), -1);
          }
          set_1_bit(&res_sub, i);
        }
      }
      if (j != 2)
        result->bits[j] = res_sub;
      else
        result->bits[j] = res_sub;

      res_sub = 0;
    }
  } else if (!sign_value1) {
    set_0_bit(&(value_2.bits[3]), 31);
    s21_add(value_1, value_2, result);
  } else {
    set_0_bit(&(value_1.bits[3]), 31);
    s21_add(value_1, value_2, result);
  }
  if ((result->bits[0] == 0) && (result->bits[1] == 0) &&
      (result->bits[2] == 0)) {
    set_0_bit(&(result->bits[3]), 31);
  }

  return 0;
}