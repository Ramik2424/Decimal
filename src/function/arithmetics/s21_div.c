#include "../../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  correct_decimal(&value_1);
  correct_decimal(&value_2);
  init_ziro_result(result);

  int sign_value1 = get_sign(value_1);
  int sign_value2 = get_sign(value_2);

  int v1_bits = take_value_of_bits(value_1);

  if ((value_2.bits[2] == 0) && (value_2.bits[1] == 0) &&
      (value_2.bits[0] == 0))
    return 3;

  sign_value1 == sign_value2 ? set_0_bit(&(result->bits[3]), 31)
                             : set_1_bit(&(result->bits[3]), 31);

  set_0_bit(&(value_1.bits[3]), 31);
  set_0_bit(&(value_2.bits[3]), 31);

  s21_decimal buff = {0};
  s21_decimal prel_res = {0};

  for (int i = v1_bits - 1; i >= 0; i--) {
    int j = 0;
    if (i > 63)
      j = 2;
    else if (i > 31)
      j = 1;

    s21_decimal temp = {0};
    if (get_bit(value_1.bits[j], i - (j * 32))) {
      if (buff.bits[0] != 0) {
        shift_left(&buff, 1);
      }
      set_1_bit(&(buff.bits[0]), 0);
      if (s21_is_less_or_equal(value_2, buff)) {
        s21_sub(buff, value_2, &temp);
        buff = temp;
        if (prel_res.bits[0] != 0) shift_left(&prel_res, 1);
        set_1_bit(&(prel_res.bits[0]), 0);
      } else if (prel_res.bits[0] != 0 || prel_res.bits[1] != 0 ||
                 prel_res.bits[2] != 0) {
        shift_left(&prel_res, 1);
      }
    } else {
      shift_left(&buff, 1);
      if (s21_is_less_or_equal(value_2, buff)) {
        s21_sub(buff, value_2, &temp);
        buff = temp;
        if (prel_res.bits[0] != 0) shift_left(&prel_res, 1);
        set_1_bit(&(prel_res.bits[0]), 0);
      } else if (prel_res.bits[0] != 0 || prel_res.bits[1] != 0 ||
                 prel_res.bits[2] != 0) {
        shift_left(&prel_res, 1);
      }
    }
  }

  result->bits[0] = prel_res.bits[0];
  result->bits[1] = prel_res.bits[1];
  result->bits[2] = prel_res.bits[2];

  return 0;
}