#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <check.h>

#define MAX_UNSIGNED_INT 4294967295
#define MaxUint 4294967295
#define MaxINT 2147483647
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// SUPPORTS FUNCTION

void init_ziro_result(s21_decimal *result);
int get_sign(s21_decimal value);
int get_bit(unsigned long value, int num);
void set_1_bit(unsigned int *value, int num);
int get_Bit(s21_decimal my_number, int index);
void set_0_bit(unsigned int *value, int num);
int set_bit(s21_decimal *my_number, int index, int sym);
void correct_decimal(s21_decimal *dst);
int equalize_scale(s21_decimal *value_1, s21_decimal *value_2);
int get_scale(s21_decimal value);
int set_scale(unsigned int *value, unsigned int num);
int mult_by_ten(s21_decimal *value, unsigned int scale);
void take_1_bit(unsigned int *value, int index);
void zero_check(s21_decimal *decimal);
int take_value_of_bits(s21_decimal value);
int shift_left(s21_decimal *value, int num);
int bits_is_greater(const s21_decimal dst, const s21_decimal src, int num_bit);
void copy_decimal(s21_decimal value, s21_decimal *result);
void from_decimal_to_long_double(s21_decimal value, long double *num);
void from_long_double_to_decimal(s21_decimal *result, long double num);

#endif  // S21_DECIMAL_H