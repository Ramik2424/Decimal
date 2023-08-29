#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_decimal.h"

//--------------------------s21_add---------------------------------

START_TEST(test_s21_add_1) {
  s21_decimal value_1 = {{1566667, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{1, 0, 0, 0b10000000000000000000000000000000}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 1566668);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal value_1 = {
      {0, 4294967295, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{1, 0, 0, 0b10000000000000000000000000000000}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 4294967295);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal value_1 = {
      {0, 4294967294, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{1, 1, 0, 0b00000000000000000000000000000000}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 4294967295);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0b00000000000000000000000000000000);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal value1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value2 = {{1, 0, 1, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(1, s21_add(value1, value2, &result));
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal value_1 = {{2147483646, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 2147483648);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_6) {
  s21_decimal value_1 = {{2147483646, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{2, 0, 0, 0x80000000}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 2147483648);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_add_7) {
  s21_decimal value_1 = {{2147483646, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 2147483646);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_8) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 100);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_add_9) {
  s21_decimal value_1 = {{2147483646, 0, 0, 0}};
  s21_decimal value_2 = {{40, 0, 0, 0x80000000}};

  s21_decimal result = {0};

  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);

  ck_assert_uint_eq(result.bits[0], 2147483606);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_10) {
  s21_decimal value1 = {
      {4294967295, 4294967295, 4294967295, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{1, 0, 1, 0b10000000000000000000000000000000}};
  s21_decimal result = {0};
  ck_assert_int_eq(2, s21_add(value1, value2, &result));
}
END_TEST

//--------------------------s21_sub---------------------------------

START_TEST(test_s21_sub_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_2) {
  s21_decimal value_1 = {{2, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_sub_3) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_4) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_5) {
  s21_decimal value_1 = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_mul---------------------------------

START_TEST(test_s21_mul_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal value_1 = {{8, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 80);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 40);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_div---------------------------------

START_TEST(test_s21_div_1) {
  s21_decimal value1 = {{0, 0, 0, 1}};
  s21_decimal value2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(3, s21_div(value1, value2, &result));  // 3
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_div_6) {
  s21_decimal value_1 = {{27, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 9);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_div_7) {
  s21_decimal value1 = {{123, 0, 0, 0}};
  s21_decimal value2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_div(value1, value2, &result));
}
END_TEST

START_TEST(test_s21_div_8) {
  s21_decimal value1 = {{0b10011101010101111010101000110100,
                         0b00101110110000101010010010111100,
                         0b00000000000100110110011000111010, 0}};
  s21_decimal value2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_div(value1, value2, &result));
  ck_assert_int_eq(result.bits[0], 0b01001110101010111101010100011010);
  ck_assert_int_eq(result.bits[1], 0b00010111011000010101001001011110);
  ck_assert_int_eq(result.bits[2], 0b00000000000010011011001100011101);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_is_less---------------------------------

START_TEST(test_s21_is_less_1) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};

  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};

  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};

  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b00000000000000110000000000000000}};
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_8) {
  s21_decimal value_1 = {{50000000, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {{50000, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

//--------------------------s21_is_less_or_equal---------------------------------

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};

  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};

  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};

  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{0, 1, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};

  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};

  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_9) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_10) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b00000000000000110000000000000000}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_less_or_equal_11) {
  s21_decimal value_1 = {{50000000, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal value_2 = {{50000, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

//--------------------------s21_is_greater---------------------------------

START_TEST(test_s21_is_greater_1) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_6) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000010000000000000000}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_7) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000010000000000000000}};
  ck_assert_int_eq(1, s21_is_greater(value_2, value_1));
}
END_TEST

//--------------------------s21_is_greater_or_equal---------------------------------
START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000010000000000000000}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000010000000000000000}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_2, value_1));
}
END_TEST

//--------------------------s21_is_equal---------------------------------
START_TEST(test_s21_is_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_6) {
  s21_decimal value_1 = {{50000, 0, 0, 0}};
  s21_decimal value_2 = {{50000000, 0, 0, 0}};
  set_scale(&(value_1.bits[3]), 1);
  set_scale(&(value_2.bits[3]), 4);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_7) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000010000000000000000}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

//--------------------------s21_is_not_equal---------------------------------
START_TEST(test_s21_is_not_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_6) {
  s21_decimal value_1 = {{0, 0, 1, 1}};
  s21_decimal value_2 = {{0, 0, 1, 1}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_7) {
  s21_decimal value_1 = {{0, 0, 1, 1}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_8) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 1}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_9) {
  s21_decimal value_1 = {{0, 0, 1, 1}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_10) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000001000000000000000}};
  s21_decimal value_2 = {{50000000, 0, 0, 0b000000000000011000000000000000}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_11) {
  s21_decimal value_1 = {{50000, 0, 0, 0}};
  s21_decimal value_2 = {{50000000, 0, 0, 0}};
  set_scale(&(value_1.bits[3]), 1);
  set_scale(&(value_2.bits[3]), 4);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

//--------------------------s21_negate---------------------------------
START_TEST(test_s21_negate_1) {
  s21_decimal value_1 = {{256, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value_1, &result);

  ck_assert_uint_eq(result.bits[0], 256);
  ck_assert_uint_eq(result.bits[1], 1);
  ck_assert_uint_eq(result.bits[2], 1);
  ck_assert_uint_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal value_1 = {{256, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};

  s21_negate(value_1, &result);

  ck_assert_uint_eq(result.bits[0], 256);
  ck_assert_uint_eq(result.bits[1], 1);
  ck_assert_uint_eq(result.bits[2], 1);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_truncate---------------------------------

START_TEST(test_s21_truncate_1) {
  s21_decimal val = {{2347, 3457, 3457, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_truncate(val, &result));
  ck_assert_int_eq(result.bits[0], 2347);
  ck_assert_int_eq(result.bits[1], 3457);
  ck_assert_int_eq(result.bits[2], 3457);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(123456789, &value_1);
  s21_truncate(value_1, &result);
  ck_assert_int_eq(result.bits[0], 123456789);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(15008, &value_1);
  s21_truncate(value_1, &result);
  ck_assert_int_eq(result.bits[0], 15008);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_4) {
  s21_decimal value_1 = {{50000, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(value_1, &result);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_round---------------------------------

START_TEST(test_s21_round_1) {
  s21_decimal value_1 = {{12345678, 0, 0, 0b00000000000000100000000000000000}};
  //        set_scale(value_1.bits, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_int_eq(result.bits[0], 123457);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal value_1 = {{555555, 0, 0, 0}};
  //    set_scale(value_1.bits, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_int_eq(result.bits[0], 555555);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal value_1 = {{12345678, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_int_eq(result.bits[0], 12345678);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal value_1 = {{5000000, 0, 0, 0}};

  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(value_1, &result);
  ck_assert_int_eq(result.bits[0], 5000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_floor---------------------------------

START_TEST(test_s21_floor_1) {
  s21_decimal value = {{10, 0, 0, MaxINT}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_floor(value, &result));
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal value = {{256, 0, 0, 0}};
  s21_decimal result = {0};
  set_scale(&(value.bits[3]), 2);
  ck_assert_int_eq(0, s21_floor(value, &result));
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal value = {{28, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_floor(value, &result));
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal value = {{10, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_floor(value, &result));
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal value = {{256, 0, 0, 0b10000000000000010000000000000000}};
  value.bits[3] |= 1 << 31;
  s21_decimal result = {0};
  ck_assert_int_eq(0, s21_floor(value, &result));
  ck_assert_int_eq(result.bits[0], 26);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

//--------------------------s21_from_int_to_decimal---------------------------------
START_TEST(test_s21_from_int_to_decimal_1) {
  s21_decimal result;
  s21_from_int_to_decimal(123456, &result);
  ck_assert_int_eq(result.bits[0], 123456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-1234567, &result);
  ck_assert_int_eq(result.bits[0], 1234567);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  s21_decimal result;
  s21_from_int_to_decimal(3425456, &result);
  ck_assert_int_eq(result.bits[0], 3425456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-42949675, &result);
  ck_assert_int_eq(result.bits[0], 42949675);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  s21_decimal result;
  s21_from_int_to_decimal(MaxINT, &result);
  ck_assert_int_eq(result.bits[0], MaxINT);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_6) {
  s21_decimal result;
  s21_from_int_to_decimal(45637492, &result);
  ck_assert_int_eq(result.bits[0], 45637492);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//--------------------------s21_from_float_to_decimal---------------------------------

START_TEST(test_s21_from_float_to_decimal_1) {
  s21_decimal result;
  s21_from_float_to_decimal(1234567.0, &result);
  ck_assert_int_eq(result.bits[0], 1234567);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  s21_decimal result;
  s21_from_float_to_decimal(1.234567, &result);
  ck_assert_int_eq(result.bits[0], 1234567);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 6 << 16);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  s21_decimal result = {0};
  s21_from_float_to_decimal(1e-29, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  s21_decimal result;
  s21_from_float_to_decimal(-1.234567, &result);
  ck_assert_int_eq(result.bits[0], 1234567);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0b10000000000001100000000000000000);
}
END_TEST

//--------------------------s21_from_decimal_to_int---------------------------------

START_TEST(test_s21_from_decimal_to_int_1) {
  s21_decimal value = {{123456789, 123456789, 123456789, 0}};
  int result = 0;
  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_2) {
  s21_decimal value = {{123, 0, 0, 0}};
  int result = 0;
  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, 123);
}
END_TEST

//--------------------------s21_from_decimal_to_float---------------------------------

START_TEST(test_s21_from_decimal_to_float_1) {
  s21_decimal src = {{100000, 0, 0, 0}};
  float dst = 0.0;

  s21_from_decimal_to_float(src, &dst);

  ck_assert_float_eq(dst, 1000.000);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_2) {
  s21_decimal src = {{42967295, 0, 0, 0}};
  float dst = 0.0;

  s21_from_decimal_to_float(src, &dst);

  ck_assert_float_eq(dst, 42967295.0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_3) {
  s21_decimal src = {{123456789, 0, 0, 0}};
  float dst = 0.0;
  s21_from_decimal_to_float(src, &dst);

  ck_assert_float_eq(dst, 123456789.0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_4) {
  s21_decimal src = {{1000000000, 0, 0, 0x80000000}};
  float dst = 0.0;

  s21_from_decimal_to_float(src, &dst);

  ck_assert_float_eq(dst, -1000000000.0);
}
END_TEST

//-----------------------------------------------------------------------------------

// Создание набора тестов
Suite *s21_decimalSuite(void) {
  Suite *suite = suite_create("s21_decimal");

  // Создание тестового набора для функции s21_add
  TCase *tc_add = tcase_create("add");
  tcase_add_test(tc_add, test_s21_add_1);
  tcase_add_test(tc_add, test_s21_add_2);
  tcase_add_test(tc_add, test_s21_add_3);
  tcase_add_test(tc_add, test_s21_add_4);
  tcase_add_test(tc_add, test_s21_add_5);
  tcase_add_test(tc_add, test_s21_add_6);
  tcase_add_test(tc_add, test_s21_add_7);
  tcase_add_test(tc_add, test_s21_add_8);
  tcase_add_test(tc_add, test_s21_add_9);
  tcase_add_test(tc_add, test_s21_add_10);
  suite_add_tcase(suite, tc_add);

  // Создание тестового набора для функции s21_sub
  TCase *tc_sub = tcase_create("sub");
  tcase_add_test(tc_sub, test_s21_sub_1);
  tcase_add_test(tc_sub, test_s21_sub_2);
  tcase_add_test(tc_sub, test_s21_sub_3);
  tcase_add_test(tc_sub, test_s21_sub_4);
  tcase_add_test(tc_sub, test_s21_sub_5);
  suite_add_tcase(suite, tc_sub);

  // Создание тестового набора для функции s21_mul
  TCase *tc_mul = tcase_create("mul");
  tcase_add_test(tc_mul, test_s21_mul_1);
  tcase_add_test(tc_mul, test_s21_mul_2);
  tcase_add_test(tc_mul, test_s21_mul_3);
  tcase_add_test(tc_mul, test_s21_mul_4);
  tcase_add_test(tc_mul, test_s21_mul_5);
  tcase_add_test(tc_mul, test_s21_mul_6);
  tcase_add_test(tc_mul, test_s21_mul_7);
  suite_add_tcase(suite, tc_mul);

  // Создание тестового набора для функции s21_div
  TCase *tc_div = tcase_create("div");
  tcase_add_test(tc_div, test_s21_div_1);
  tcase_add_test(tc_div, test_s21_div_2);
  tcase_add_test(tc_div, test_s21_div_3);
  tcase_add_test(tc_div, test_s21_div_4);
  tcase_add_test(tc_div, test_s21_div_5);
  tcase_add_test(tc_div, test_s21_div_6);
  tcase_add_test(tc_div, test_s21_div_7);
  tcase_add_test(tc_div, test_s21_div_8);
  suite_add_tcase(suite, tc_div);

  // Создание тестового набора для функции s21_is_less
  TCase *tc_is_less = tcase_create("is_less");
  tcase_add_test(tc_is_less, test_s21_is_less_1);
  tcase_add_test(tc_is_less, test_s21_is_less_2);
  tcase_add_test(tc_is_less, test_s21_is_less_3);
  tcase_add_test(tc_is_less, test_s21_is_less_4);
  tcase_add_test(tc_is_less, test_s21_is_less_5);
  tcase_add_test(tc_is_less, test_s21_is_less_6);
  tcase_add_test(tc_is_less, test_s21_is_less_7);
  tcase_add_test(tc_is_less, test_s21_is_less_8);
  suite_add_tcase(suite, tc_is_less);

  // Создание тестового набора для функции s21_is_less_or_equal
  TCase *tc_is_less_or_equal = tcase_create("is_less_or_equal");
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_1);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_2);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_3);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_4);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_5);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_6);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_7);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_8);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_9);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_10);
  tcase_add_test(tc_is_less_or_equal, test_s21_is_less_or_equal_11);
  suite_add_tcase(suite, tc_is_less_or_equal);

  // Создание тестового набора для функции s21_is_greater
  TCase *tc_is_greater = tcase_create("is_greater");
  tcase_add_test(tc_is_greater, test_s21_is_greater_1);
  tcase_add_test(tc_is_greater, test_s21_is_greater_2);
  tcase_add_test(tc_is_greater, test_s21_is_greater_3);
  tcase_add_test(tc_is_greater, test_s21_is_greater_4);
  tcase_add_test(tc_is_greater, test_s21_is_greater_5);
  tcase_add_test(tc_is_greater, test_s21_is_greater_6);
  tcase_add_test(tc_is_greater, test_s21_is_greater_7);

  suite_add_tcase(suite, tc_is_greater);

  // Создание тестового набора для функции s21_is_greater_or_equal
  TCase *tc_is_greater_or_equal = tcase_create("is_greater_or_equal");
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_5);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_6);
  tcase_add_test(tc_is_greater_or_equal, test_s21_is_greater_or_equal_7);
  suite_add_tcase(suite, tc_is_greater_or_equal);

  // Создание тестового набора для функции s21_is_equal
  TCase *tc_is_equal = tcase_create("is_equal");
  tcase_add_test(tc_is_equal, test_s21_is_equal_1);
  tcase_add_test(tc_is_equal, test_s21_is_equal_2);
  tcase_add_test(tc_is_equal, test_s21_is_equal_3);
  tcase_add_test(tc_is_equal, test_s21_is_equal_4);
  tcase_add_test(tc_is_equal, test_s21_is_equal_5);
  tcase_add_test(tc_is_equal, test_s21_is_equal_6);
  tcase_add_test(tc_is_equal, test_s21_is_equal_7);
  suite_add_tcase(suite, tc_is_equal);

  // Создание тестового набора для функции s21_is_not_equal
  TCase *tc_is_not_equal = tcase_create("is_not_equal");
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_1);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_2);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_3);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_4);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_5);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_6);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_7);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_8);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_9);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_10);
  tcase_add_test(tc_is_not_equal, test_s21_is_not_equal_11);
  suite_add_tcase(suite, tc_is_not_equal);

  // Создание тестового набора для функции s21_negate
  TCase *tc_negate = tcase_create("negate");
  tcase_add_test(tc_negate, test_s21_negate_1);
  tcase_add_test(tc_negate, test_s21_negate_2);
  tcase_add_test(tc_negate, test_s21_negate_3);
  suite_add_tcase(suite, tc_negate);

  // Создание тестового набора для функции s21_truncate
  TCase *tc_truncate = tcase_create("truncate");
  tcase_add_test(tc_truncate, test_s21_truncate_1);
  tcase_add_test(tc_truncate, test_s21_truncate_2);
  tcase_add_test(tc_truncate, test_s21_truncate_3);
  tcase_add_test(tc_truncate, test_s21_truncate_4);
  suite_add_tcase(suite, tc_truncate);

  // Создание тестового набора для функции s21_round
  TCase *tc_round = tcase_create("round");
  tcase_add_test(tc_round, test_s21_round_1);
  tcase_add_test(tc_round, test_s21_round_2);
  tcase_add_test(tc_round, test_s21_round_3);
  tcase_add_test(tc_round, test_s21_round_4);
  suite_add_tcase(suite, tc_round);

  // Создание тестового набора для функции s21_floor
  TCase *tc_floor = tcase_create("floor");
  tcase_add_test(tc_floor, test_s21_floor_1);
  tcase_add_test(tc_floor, test_s21_floor_2);
  tcase_add_test(tc_floor, test_s21_floor_3);
  tcase_add_test(tc_floor, test_s21_floor_4);
  tcase_add_test(tc_floor, test_s21_floor_5);
  suite_add_tcase(suite, tc_floor);

  // Создание тестового набора для функции s21_from_int_to_decimal
  TCase *tc_from_int_to_decimal = tcase_create("from_int_to_decimal");
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_1);
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_2);
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_3);
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_4);
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_5);
  tcase_add_test(tc_from_int_to_decimal, test_s21_from_int_to_decimal_6);
  suite_add_tcase(suite, tc_from_int_to_decimal);

  // Создание тестового набора для функции s21_from_float_to_decimal
  TCase *tc_from_float_to_decimal = tcase_create("from_float_to_decimal");
  tcase_add_test(tc_from_float_to_decimal, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc_from_float_to_decimal, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc_from_float_to_decimal, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc_from_float_to_decimal, test_s21_from_float_to_decimal_4);
  suite_add_tcase(suite, tc_from_float_to_decimal);

  // Создание тестового набора для функции s21_from_decimal_to_int
  TCase *tc_from_decimal_to_int = tcase_create("from_decimal_to_int");
  tcase_add_test(tc_from_decimal_to_int, test_s21_from_decimal_to_int_1);
  tcase_add_test(tc_from_decimal_to_int, test_s21_from_decimal_to_int_2);
  suite_add_tcase(suite, tc_from_decimal_to_int);

  // // Создание тестового набора для функции s21_from_decimal_to_float
  TCase *tc_from_decimal_to_float = tcase_create("from_decimal_to_float");
  tcase_add_test(tc_from_decimal_to_float, test_s21_from_decimal_to_float_1);
  tcase_add_test(tc_from_decimal_to_float, test_s21_from_decimal_to_float_2);
  tcase_add_test(tc_from_decimal_to_float, test_s21_from_decimal_to_float_3);
  tcase_add_test(tc_from_decimal_to_float, test_s21_from_decimal_to_float_4);
  suite_add_tcase(suite, tc_from_decimal_to_float);

  return suite;
}

int main(void) {
  int counted_errors = 0;
  Suite *suite = s21_decimalSuite();
  SRunner *runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  counted_errors = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (counted_errors == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}