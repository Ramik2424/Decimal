#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  init_ziro_result(result);

  int res = 0;

  int scale = get_scale(value);

  if (scale == 0)
    copy_decimal(value, result);
  else {
    s21_decimal one = {0};
    s21_decimal ten = {0};
    s21_decimal res_tmp = {0};

    ten.bits[0] = 10;
    one.bits[0] = 1;
    one.bits[3] |= 1 << 31;
    while (scale != 0) {
      scale--;
      s21_div(value, ten, &res_tmp);
      copy_decimal(res_tmp, &value);
    }

    get_sign(value) == 1 ? s21_add(res_tmp, one, result)
                         : copy_decimal(res_tmp, result);

    init_ziro_result(&res_tmp);
    init_ziro_result(&one);
    init_ziro_result(&ten);
  }

  return res;
}