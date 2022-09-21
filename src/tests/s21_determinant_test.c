#include "test.h"

START_TEST(determinant_matrix1) {
  matrix_t a;
  double b;
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
  int status = s21_determinant(&a, &b);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(b, -40.0, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant_matrix2) {
  matrix_t a;
  double b;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1.3;
  a.matrix[0][1] = 5.2;
  a.matrix[0][2] = 0.3;
  a.matrix[1][0] = -3;
  a.matrix[1][1] = 5.4;
  a.matrix[1][2] = 11;
  a.matrix[2][0] = 6.1;
  a.matrix[2][1] = 4;
  a.matrix[2][2] = 8;
  int status = s21_determinant(&a, &b);
  ck_assert_double_eq_tol(b, 459.198, 1e-7);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant_matrix3) {
  matrix_t a;
  double b;
  s21_create_matrix(3, 2, &a);
  a.matrix[0][0] = 1.3;
  a.matrix[0][1] = 5.2;
  a.matrix[1][0] = -3;
  a.matrix[1][1] = 5.4;
  a.matrix[2][0] = 6.1;
  a.matrix[2][1] = 4;
  int status = s21_determinant(&a, &b);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant_matrix4) {
  matrix_t a;
  double b;
  a.rows = -1;
  int status = s21_determinant(&a, &b);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_determinant_matrix() {
  Suite *s = suite_create("[s21_determinant_matrix] Unit Test");

  TCase *tc1 = tcase_create("s21_determinant_matrix1");
  TCase *tc2 = tcase_create("s21_determinant_matrix2");
  TCase *tc3 = tcase_create("s21_determinant_matrix3");
  TCase *tc4 = tcase_create("s21_determinant_matrix4");

  tcase_add_test(tc1, determinant_matrix1);
  tcase_add_test(tc2, determinant_matrix2);
  tcase_add_test(tc3, determinant_matrix3);
  tcase_add_test(tc4, determinant_matrix4);

  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  suite_add_tcase(s, tc4);

  return s;
}
