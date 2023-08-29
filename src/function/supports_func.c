#include "../s21_decimal.h"

void init_ziro_result(s21_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = 0;
  }
}

int get_sign(s21_decimal value) { return value.bits[3] >> 31; }

int get_bit(unsigned long value, int num) {
  unsigned long check = 0;
  int result = 0;
  check = 1u << num;
  value &= check;
  result = value >> num;
  return result;
}

int get_Bit(s21_decimal my_number, int index) {
  int sym;
  int mask;
  if (index < 32) {
    mask = (1U << index);
    sym = ((my_number.bits[0] & mask) ? 1 : 0);
  } else if ((31 < index) && (index < 64)) {
    mask = (1U << (index - 32));
    sym = ((my_number.bits[1] & mask) ? 1 : 0);
  } else if ((63 < index) && (index < 96)) {
    mask = (1U << (index - 64));
    sym = ((my_number.bits[2] & mask) ? 1 : 0);
  } else if ((95 < index) && (index < 128)) {
    mask = (1U << (index - 96));
    sym = ((my_number.bits[3] & mask) ? 1 : 0);
  }
  return sym;
}

int set_bit(s21_decimal *my_number, int index, int sym) {
  int flag;
  if (index < 128 && index >= 0) {
    int mask;
    if (index < 32) {
      if (sym == 1) {
        mask = (1 << (index));
        my_number->bits[0] |= mask;
      } else {
        mask = (1 << (index));
        my_number->bits[0] &= ~mask;
      }
    }
    if ((31 < index) && (index < 64)) {
      if (sym == 1) {
        mask = (1 << (index - 32));
        my_number->bits[1] |= mask;
      } else {
        mask = (1 << (index - 32));
        my_number->bits[1] &= ~mask;
      }
    }
    if ((63 < index) && (index < 96)) {
      if (sym == 1) {
        mask = (1 << (index - 64));
        my_number->bits[2] |= mask;
      } else {
        mask = (1 << (index - 64));
        my_number->bits[2] &= ~mask;
      }
    }
    if ((95 < index) && (index < 128)) {
      if (sym == 1) {
        mask = (1 << (index - 96));
        my_number->bits[3] |= mask;
      } else {
        mask = (1 << (index - 96));
        my_number->bits[3] &= ~mask;
      }
    }
    flag = 0;
  } else {
    flag = 2;
  }
  return (flag);
}

void set_1_bit(unsigned int *value, int num) {
  unsigned int set = 0;
  set = 1 << num;
  *value |= set;
}

void set_0_bit(unsigned int *value, int num) {
  unsigned int set = 0;
  set = 1 << num;
  *value &= ~set;
}

void correct_decimal(s21_decimal *dst) {
  for (int i = 0; i < 15; i++) {
    set_0_bit(&dst->bits[3], i);
  }
  for (int i = 22; i < 31; i++) {
    set_0_bit(&dst->bits[3], i);
  }
}

int equalize_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_value1 = get_scale(*value_1);
  int scale_value2 = get_scale(*value_2);

  int check = 0;

  unsigned res_scale;

  s21_decimal temp = {0};

  if (scale_value1 > scale_value2) {
    res_scale = scale_value1 - scale_value2;
    temp = *value_2;
    check = mult_by_ten(&temp, res_scale);
    if (!check) {
      *value_2 = temp;
    }
  } else {
    res_scale = scale_value2 - scale_value1;
    temp = *value_1;
    check = mult_by_ten(&temp, res_scale);
    if (!check) {
      *value_1 = temp;
    }
  }

  return check;
}

int get_scale(s21_decimal value) {
  unsigned int res = 0;
  for (int i = 0; i < 8; i++) {
    if (get_bit(value.bits[3], 16 + i)) set_1_bit(&res, i);
  }
  return res;
}

int set_scale(unsigned int *value, unsigned int num) {
  if (num < 29) {
    for (int i = 0; i < 8; i++) {
      get_bit(num, i) ? set_1_bit(value, 16 + i) : set_0_bit(value, 16 + i);
    }
  }
  return 0;
}

int mult_by_ten(s21_decimal *value, unsigned int scale) {
  int scale_value = get_scale(*value);
  unsigned long int num = 0, remainder = 0, bits = 0, max = MAX_UNSIGNED_INT;
  int check = 0;
  unsigned int tmp = 0;

  while ((scale > 0) && (scale_value < 29)) {
    for (int i = 0; i < 3; i++) {
      bits += value->bits[i];
      bits *= 10;
      bits += num;
      remainder += (bits >> 32);
      bits &= max;
      value->bits[i] = bits;
      bits = 0;
      num = remainder;
      remainder = 0;
    }
    if (remainder != 0) {
      check = 1;
      break;
    } else {
      scale_value++;
      tmp = value->bits[3];
      set_scale(&tmp, scale_value);
      value->bits[3] = tmp;
      scale--;
    }
  }

  return check;
}

void take_1_bit(unsigned int *value, int index) {
  int tmp = 0;
  tmp = index + 1;
  if (get_bit(*value, tmp))
    set_0_bit(value, tmp);
  else {
    take_1_bit(value, tmp);
    set_1_bit(value, tmp);
  }
}

void zero_check(s21_decimal *decimal) {
  if ((decimal->bits[0] == 0) && (decimal->bits[1] == 0) &&
      (decimal->bits[2] == 0)) {
    decimal->bits[3] = 0;
  }
}

int take_value_of_bits(s21_decimal value) {
  int value_bits = 0;
  for (int j = 2; j >= 0; j--) {
    for (int i = 31; i >= 0; i--) {
      if (get_bit(value.bits[j], i)) {
        value_bits = j * 32 + i + 1;
        break;
      }
    }
    if (value_bits != 0) break;
  }
  return value_bits;
}
int shift_left(s21_decimal *value, int num) {
  int bit_from_previous = 0;
  for (int k = 0; k < num; k++) {
    if (get_bit(value->bits[2], 31)) return 1;
    bit_from_previous = get_bit(value->bits[1], 31);
    value->bits[2] = value->bits[2] << 1;
    if (bit_from_previous) {
      set_1_bit(&(value->bits[2]), 0);
    }
    bit_from_previous = get_bit(value->bits[0], 31);
    value->bits[1] = value->bits[1] << 1;
    if (bit_from_previous) {
      set_1_bit(&(value->bits[1]), 0);
    }
    value->bits[0] = value->bits[0] << 1;
  }
  return 0;
}

int bits_is_greater(const s21_decimal dst, const s21_decimal src, int num_bit) {
  int result = 0;
  if (dst.bits[num_bit] > src.bits[num_bit]) {
    result = 1;
  } else if (dst.bits[num_bit] == src.bits[num_bit]) {
    result = 2;
  }

  return result;
}

void copy_decimal(s21_decimal value, s21_decimal *result) {
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];
}

void from_decimal_to_long_double(s21_decimal value, long double *num) {
  long double temp = *num;
  for (int i = 0; i < 96; i++) {
    temp += get_bit(value.bits[i / 32], i) * pow(2, i);
  }
  temp = temp / pow(10, get_scale(value));
  *num = temp;
}

void from_long_double_to_decimal(s21_decimal *result, long double num) {
  int bits_number = 0;
  long double remainder = 0.0;
  for (int i = 0; num > 0.0 && i < 96; i++) {
    num = floor((double)num) / 2;
    remainder = num - floor((double)num);
    if (i < 32) {
      bits_number = i;
    } else if (i >= 32 && i < 64) {
      bits_number = i - 32;
    } else {
      bits_number = i - 64;
    }
    if (remainder == 0.5) {
      set_1_bit(&result->bits[i / 32], bits_number);
    } else {
      set_0_bit(&result->bits[i / 32], bits_number);
    }
  }
  set_scale(&result->bits[3], 0);
}