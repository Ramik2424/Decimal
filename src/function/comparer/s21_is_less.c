#include "../../s21_decimal.h"

int s21_is_less(s21_decimal left_value, s21_decimal right_value) {
  int sign_left = 0;
  int sign_right = 0;
  int left_bit = 0;
  int right_bit = 0;
  zero_check(&left_value);
  zero_check(&right_value);
  sign_left = get_sign(left_value);
  sign_right = get_sign(right_value);
  int result = 0;
  correct_decimal(&left_value);
  correct_decimal(&right_value);
  if (sign_left != sign_right) {
    if (sign_left)
      result = 1;
    else
      result = 0;
  } else {
    equalize_scale(&left_value, &right_value);
    for (int j = 2; j >= 0; j--) {
      for (int i = 31; i >= 0; i--) {
        left_bit = get_bit(left_value.bits[j], i);
        right_bit = get_bit(right_value.bits[j], i);
        if (right_bit && (right_bit != left_bit)) {
          result = 1;
          j = -1;
          break;
        } else if (left_bit && (right_bit != left_bit)) {
          result = 0;
          j = -1;
          break;
        } else
          result = 0;
      }
    }
  }
  return result;
}