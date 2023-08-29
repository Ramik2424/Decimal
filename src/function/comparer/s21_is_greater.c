#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal left_value, s21_decimal right_value) {
  return !s21_is_less_or_equal(left_value, right_value);
}