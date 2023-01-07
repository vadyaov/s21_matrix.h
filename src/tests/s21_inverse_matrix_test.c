#include "test.h"

START_TEST(inverse_matrix1) {
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
  int status = s21_inverse_matrix(&a, &b);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(b.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], -0.1, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][2], 0.2, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], -0.25, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], 0.35, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][2], 0.05, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][0], 0.5, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][1], -0.2, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][2], -0.1, 1e-7);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(inverse_matrix2) {
  matrix_t a, b;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 5;
  a.matrix[0][2] = 0;
  a.matrix[1][0] = -3;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 11;
  a.matrix[2][0] = 6;
  a.matrix[2][1] = 4;
  a.matrix[2][2] = 8;
  int status = s21_inverse_matrix(&a, &b);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(b.matrix[0][0], -2.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][1], -20.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[0][2], 55.0 / 446.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][0], 45.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][1], 4.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[1][2], -11.0 / 446.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][0], -21.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][1], 13.0 / 223.0, 1e-7);
  ck_assert_double_eq_tol(b.matrix[2][2], 10.0 / 223.0, 1e-7);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(inverse_matrix3) {
  matrix_t a, b, c, one;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &one);

  one.matrix[0][0] = 1.0;
  one.matrix[0][1] = 0.0;
  one.matrix[1][0] = 0.0;
  one.matrix[1][1] = 1.0;

  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = -1.0;
  a.matrix[1][0] = 2.0;
  a.matrix[1][1] = 4.0;

  int status = s21_inverse_matrix(&a, &b);
  ck_assert_int_eq(status, OK);
  int status1 = s21_mult_matrix(&a, &b, &c);
  ck_assert_int_eq(status1, OK);

  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++)
      ck_assert_double_eq_tol(c.matrix[i][j], one.matrix[i][j], 1e-7);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&one);
}
END_TEST

START_TEST(inverse_matrix4) {
  matrix_t a, b, c, one;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &one);

  one.matrix[0][0] = 1.0;
  one.matrix[0][1] = 0.0;
  one.matrix[0][2] = 0.0;
  one.matrix[1][0] = 0.0;
  one.matrix[1][1] = 1.0;
  one.matrix[1][2] = 0.0;
  one.matrix[2][0] = 0.0;
  one.matrix[2][1] = 0.0;
  one.matrix[2][2] = 1.0;

  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = -2.0;
  a.matrix[0][2] = 3.0;
  a.matrix[1][0] = 0.0;
  a.matrix[1][1] = 4.0;
  a.matrix[1][2] = -1.0;
  a.matrix[2][0] = 5.0;
  a.matrix[2][1] = 0.0;
  a.matrix[2][2] = 0.0;

  int status = s21_inverse_matrix(&a, &b);
  ck_assert_int_eq(status, OK);
  int status1 = s21_mult_matrix(&a, &b, &c);
  ck_assert_int_eq(status1, OK);

  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      ck_assert_double_eq_tol(c.matrix[i][j], one.matrix[i][j], 1e-7);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&one);
}
END_TEST

START_TEST(one_mtr) {
  matrix_t src;
  s21_create_matrix(1, 1, &src);
  src.matrix[0][0] = 2.0;
  matrix_t inv;
  int status = s21_inverse_matrix(&src, &inv);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(inv.matrix[0][0], 0.5, 1e-7);
  s21_remove_matrix(&src);
  s21_remove_matrix(&inv);
}
END_TEST

START_TEST(zero_det) {
  matrix_t src;
  s21_create_matrix(2, 2, &src);
  src.matrix[0][0] = 2.0;
  src.matrix[0][1] = 3.0;
  src.matrix[1][0] = -5.0;
  src.matrix[1][1] = -7.5;
  matrix_t inv;
  int status = s21_inverse_matrix(&src, &inv);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&src);
}
END_TEST

Suite *suite_s21_inverse_matrix() {
  Suite *s = suite_create("[s21_inverse_matrix] Unit Test");

  TCase *tc1 = tcase_create("s21_inverse_matrix1");
  TCase *tc2 = tcase_create("s21_inverse_matrix2");
  TCase *tc3 = tcase_create("s21_inverse_matrix3");
  TCase *tc4 = tcase_create("s21_inverse_matrix4");
  TCase *tc5 = tcase_create("s21_inverse_matrix_er1");
  TCase *tc6 = tcase_create("s21_inverse_matrix_er2");

  tcase_add_test(tc1, inverse_matrix1);
  tcase_add_test(tc2, inverse_matrix2);
  tcase_add_test(tc3, inverse_matrix3);
  tcase_add_test(tc4, inverse_matrix4);
  tcase_add_test(tc5, one_mtr);
  tcase_add_test(tc6, zero_det);

  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  suite_add_tcase(s, tc4);
  suite_add_tcase(s, tc5);
  suite_add_tcase(s, tc6);

  return s;
}
