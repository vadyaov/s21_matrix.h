#include "test.h"

START_TEST(mult_matrix1) {
  matrix_t a, b, c;
  s21_create_matrix(2, 3, &a);
  s21_create_matrix(3, 3, &b);
  a.matrix[0][0] = 1.25;
  a.matrix[0][1] = 1.35;
  a.matrix[0][2] = -5.05;
  a.matrix[1][0] = 9;
  a.matrix[1][1] = 7;
  a.matrix[1][2] = 2;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix[0][2] = 3;
  b.matrix[1][0] = 3;
  b.matrix[1][1] = 2;
  b.matrix[1][2] = 1;
  b.matrix[2][0] = 10;
  b.matrix[2][1] = 11.5;
  b.matrix[2][2] = 12;
  int status = s21_mult_matrix(&a, &b, &c);
  ck_assert_double_eq_tol(c.matrix[0][0], -45.2, 1e-7);
  ck_assert_double_eq_tol(c.matrix[0][1], -52.875, 1e-7);
  ck_assert_double_eq_tol(c.matrix[0][2], -55.5, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][0], 50, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][1], 55, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][2], 58, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(mult_matrix2) {
  matrix_t a, b, c;
  s21_create_matrix(3, 2, &a);
  s21_create_matrix(2, 3, &b);
  a.matrix[0][0] = 11.1;
  a.matrix[0][1] = 1.11;
  a.matrix[1][0] = -11.1;
  a.matrix[1][1] = -1.11;
  a.matrix[2][0] = 0.023;
  a.matrix[2][1] = -0.023;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix[0][2] = 3;
  b.matrix[1][0] = 3;
  b.matrix[1][1] = 2;
  b.matrix[1][2] = 1;
  int status = s21_mult_matrix(&a, &b, &c);
  ck_assert_double_eq_tol(c.matrix[0][0], 14.43, 1e-7);
  ck_assert_double_eq_tol(c.matrix[0][1], 24.42, 1e-7);
  ck_assert_double_eq_tol(c.matrix[0][2], 34.41, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][0], -14.43, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][1], -24.42, 1e-7);
  ck_assert_double_eq_tol(c.matrix[1][2], -34.41, 1e-7);
  ck_assert_double_eq_tol(c.matrix[2][0], -0.046, 1e-7);
  ck_assert_double_eq_tol(c.matrix[2][1], 0, 1e-7);
  ck_assert_double_eq_tol(c.matrix[2][2], 0.046, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(calcul_err) {
  matrix_t a, b;
  s21_create_matrix(2, 3, &a);
  s21_create_matrix(2, 3, &b);
  matrix_t result;
  int status = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(incorr_mtr1) {
  matrix_t a, b;
  s21_create_matrix(2, 3, &b);
  matrix_t result;
  a.rows = -1;
  int status = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(incorr_mtr2) {
  matrix_t a, b;
  s21_create_matrix(2, 3, &a);
  matrix_t result;
  b.columns = 0;
  int status = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

Suite *suite_s21_mult_matrix() {
  Suite *s = suite_create("[s21_mult_matrix] Unit Test");
  TCase *tc1 = tcase_create("s21_mult_matrix1");
  TCase *tc2 = tcase_create("s21_mult_matrix2");
  TCase *tc3 = tcase_create("s21_mult_matrix3");
  TCase *tc4 = tcase_create("s21_mult_matrix4");
  TCase *tc5 = tcase_create("s21_mult_matrix5");

  tcase_add_test(tc1, mult_matrix1);
  tcase_add_test(tc2, mult_matrix2);
  tcase_add_test(tc2, calcul_err);
  tcase_add_test(tc2, incorr_mtr1);
  tcase_add_test(tc2, incorr_mtr2);

  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  suite_add_tcase(s, tc4);
  suite_add_tcase(s, tc5);
  return s;
}
