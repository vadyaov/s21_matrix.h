#include "test.h"

START_TEST(calc_complements_matrix1) {
  matrix_t a, b;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  int status = s21_calc_complements(&a, &b);
  ck_assert_double_eq_tol(b.matrix[0][0], 0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], 10, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][2], -20, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], 4, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], -14, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][2], 8, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][0], -8, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][1], -2, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][2], 4, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(calc_complements_matrix2) {
  matrix_t a, b;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1.34;
  a.matrix[0][1] = 5.23;
  a.matrix[0][2] = 0.33;
  a.matrix[1][0] = -3.67;
  a.matrix[1][1] = 5.44;
  a.matrix[1][2] = 11;
  a.matrix[2][0] = 6.15;
  a.matrix[2][1] = 4.3;
  a.matrix[2][2] = 8;
  int status = s21_calc_complements(&a, &b);
  ck_assert_double_eq_tol(b.matrix[0][0], -3.78, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], 97.01, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][2], -49.237, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], -40.421, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], 8.6905, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][2], 26.4025, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][0], 55.7348, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][1], -15.9511, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][2], 26.4837, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(simple_minor_test) {
  matrix_t two;
  s21_create_matrix(2, 2, &two);
  two.matrix[0][0] = 1.25;
  two.matrix[0][1] = 2.1;
  two.matrix[1][0] = 3.76;
  two.matrix[1][1] = 4.2;
  matrix_t minor;
  int status = s21_calc_complements(&two, &minor);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(minor.matrix[0][0], 4.2, 1e-7);
  ck_assert_double_eq_tol(minor.matrix[0][1], -3.76, 1e-7);
  ck_assert_double_eq_tol(minor.matrix[1][0], -2.1, 1e-7);
  ck_assert_double_eq_tol(minor.matrix[1][1], 1.25, 1e-7);
  s21_remove_matrix(&two);
  s21_remove_matrix(&minor);
}
END_TEST

START_TEST(incorr_mtr) {
  matrix_t two;
  matrix_t minor;
  two.rows = 0;
  int status = s21_calc_complements(&two, &minor);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calcul_error) {
  matrix_t two;
  s21_create_matrix(1, 2, &two);
  two.matrix[0][0] = 1.25;
  two.matrix[0][1] = 2.1;
  matrix_t minor;
  int status = s21_calc_complements(&two, &minor);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&two);
}
END_TEST

Suite *suite_s21_calc_complements_matrix() {
  Suite *s = suite_create("[s21_calc_complements_matrix] Unit Test");
  TCase *tc1 = tcase_create("s21_calc_complements_matrix1");
  TCase *tc2 = tcase_create("s21_calc_complements_matrix2");
  TCase *tc3 = tcase_create("s21_calc_complements_matrix3");
  TCase *tc4 = tcase_create("s21_calc_complements_matrix4");
  TCase *tc5 = tcase_create("s21_calc_complements_matrix5");

  tcase_add_test(tc1, calc_complements_matrix1);
  tcase_add_test(tc2, calc_complements_matrix2);
  tcase_add_test(tc3, simple_minor_test);
  tcase_add_test(tc4, incorr_mtr);
  tcase_add_test(tc5, calcul_error);

  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  suite_add_tcase(s, tc4);
  suite_add_tcase(s, tc5);

  return s;
}
