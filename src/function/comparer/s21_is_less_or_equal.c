#include "../../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal left_value, s21_decimal right_value) {
  int result = 0;
  result = s21_is_equal(left_value, right_value);
  if (!result) result = s21_is_less(left_value, right_value);
  return result;
}
