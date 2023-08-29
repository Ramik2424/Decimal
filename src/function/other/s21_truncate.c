#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  init_ziro_result(result);
  if (get_scale(value) == 0) {
    copy_decimal(value, result);
  } else {
    s21_decimal tmp_res = {0};
    s21_decimal ten = {0};
    ten.bits[0] = 10;
    int scale = get_scale(value);
    while (scale != 0) {
      scale--;
      s21_div(value, ten, &tmp_res);
      copy_decimal(tmp_res, &value);
    }
    copy_decimal(tmp_res, result);
    init_ziro_result(&tmp_res);
    init_ziro_result(&ten);
  }
  return 0;
}