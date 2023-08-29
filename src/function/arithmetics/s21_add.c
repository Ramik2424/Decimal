#include "../../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  init_ziro_result(result);
  correct_decimal(&value_1);
  correct_decimal(&value_2);

  int sign_value1 = get_sign(value_1);
  int sign_value2 = get_sign(value_2);

  int sum_bits = 0;

  unsigned int res_sum = 0;

  equalize_scale(&value_1, &value_2);
  set_scale(&(result->bits[3]), get_scale(value_1));

  if (sign_value1 == sign_value2) {
    get_sign(value_1) ? set_1_bit(&(result->bits[3]), 31)
                      : set_0_bit(&(result->bits[3]), 31);
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        sum_bits += get_bit(value_1.bits[j], i) + get_bit(value_2.bits[j], i);
        if (sum_bits == 1) {
          set_1_bit(&res_sum, i);
          sum_bits = 0;
        } else if (sum_bits == 2) {
          sum_bits = 1;
        } else if (sum_bits == 3) {
          set_1_bit(&res_sum, i);
          sum_bits = 1;
        }
      }
      if (j != 2) {
        result->bits[j] = res_sum;
      } else if ((sum_bits > 0) && (!get_sign(*result))) {
        return 1;
      } else if ((sum_bits > 0) && (get_sign(*result))) {
        return 2;
      } else {
        result->bits[j] = res_sum;
      }
      res_sum = 0;
    }
  } else if (!sign_value1) {
    set_0_bit(&(value_2.bits[3]), 31);
    s21_sub(value_1, value_2, result);
  } else {
    set_0_bit(&(value_1.bits[3]), 31);
    s21_sub(value_2, value_1, result);
  }
  return 0;
}
