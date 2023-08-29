#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal dst, s21_decimal src) {
  int cmp_count = 0;
  correct_decimal(&src);
  correct_decimal(&dst);
  if (get_sign(dst) != get_sign(src)) {
    return 0;
  }
  equalize_scale(&dst, &src);
  for (int i = 0; i < 4; i++) {
    if (bits_is_greater(dst, src, i) == 2) {
      cmp_count++;
    }
  }
  return cmp_count == 4 ? 1 : 0;
}
