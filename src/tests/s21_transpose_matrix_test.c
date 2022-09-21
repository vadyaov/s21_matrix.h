#include "test.h"

START_TEST(transpose_matrix1) {
  matrix_t a, b;
  s21_create_matrix(2, 3, &a);
  a.matrix[0][0] = 1.25;
  a.matrix[0][1] = 1.35;
  a.matrix[0][2] = -5.05;
  a.matrix[1][0] = 9;
  a.matrix[1][1] = 7;
  a.matrix[1][2] = 2;
  int status = s21_transpose(&a, &b);
  ck_assert_double_eq_tol(b.matrix[0][0], 1.25, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], 9, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], 1.35, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], 7, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][0], -5.05, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][1], 2, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(transpose_matrix2) {
  matrix_t a, b;
  s21_create_matrix(3, 2, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 3;
  a.matrix[1][1] = 4;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 6;
  int status = s21_transpose(&a, &b);
  ck_assert_double_eq_tol(b.matrix[0][0], 1, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], 3, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][2], 5, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], 2, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], 4, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][2], 6, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(incorr_mtr) {
  matrix_t a;
  a.rows = 0;
  matrix_t res;
  int status = s21_transpose(&a, &res);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_transpose_matrix() {
  Suite *s = suite_create("[s21_transpose_matrix] Unit Test");
  TCase *tc1 = tcase_create("s21_transpose_matrix");
  TCase *tc2 = tcase_create("s21_transpose_matrix");
  TCase *tc3 = tcase_create("s21_transpose_matrix");

  tcase_add_test(tc1, transpose_matrix1);
  tcase_add_test(tc2, transpose_matrix2);
  tcase_add_test(tc3, incorr_mtr);

  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  return s;
}
