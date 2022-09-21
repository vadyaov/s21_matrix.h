#include "test.h"

START_TEST(matrix_create_test1) {
  matrix_t a;
  int rows = 0, columns = 3;
  int status = s21_create_matrix(rows, columns, &a);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  ck_assert_ptr_null(a.matrix);
  ck_assert_int_eq(a.rows, 0);
  ck_assert_int_eq(a.columns, 0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(matrix_create_test2) {
  matrix_t a;
  int rows = 3, columns = 0;
  int status = s21_create_matrix(rows, columns, &a);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  ck_assert_ptr_null(a.matrix);
  ck_assert_int_eq(a.rows, 0);
  ck_assert_int_eq(a.columns, 0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(matrix_create_test3) {
  matrix_t a;
  int rows = rand() % (10 - 1) + 1, columns = rand() % (10 - 1) + 1;
  int status = s21_create_matrix(rows, columns, &a);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(a.matrix);
  ck_assert_int_eq(a.rows, rows);
  ck_assert_int_eq(a.columns, columns);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
      ck_assert_double_eq_tol(a.matrix[i][j], 0, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(matrix_create_test4) {
  matrix_t a;
  int rows = 100, columns = 100;
  int status = s21_create_matrix(rows, columns, &a);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(a.matrix);
  ck_assert_int_eq(a.rows, 100);
  ck_assert_int_eq(a.columns, 100);
  s21_remove_matrix(&a);
}
END_TEST
/*
START_TEST(matrix_create_test4) {
} END_TEST

START_TEST(matrix_create_test5) {
} END_TEST
*/
Suite *s21_create_matrix_test() {
  Suite *s = suite_create("[s21_create_matrix] Unit Test");

  TCase *tc1_s21_create_matrix = tcase_create("create_matrix_t1");
  TCase *tc2_s21_create_matrix = tcase_create("create_matrix_t2");
  TCase *tc3_s21_create_matrix = tcase_create("create_matrix_t3");
  TCase *tc4_s21_create_matrix = tcase_create("create_matrix_t4");
  //  TCase *tc5_s21_create_matrix = tcase_create("create_matrix_t5");

  tcase_add_test(tc1_s21_create_matrix, matrix_create_test1);
  tcase_add_test(tc2_s21_create_matrix, matrix_create_test2);
  tcase_add_loop_test(tc3_s21_create_matrix, matrix_create_test3, 0, 20);
  tcase_add_test(tc4_s21_create_matrix, matrix_create_test4);
  // tcase_add_test(tc5_s21_create_matrix, matrix_create_test5);

  suite_add_tcase(s, tc1_s21_create_matrix);
  suite_add_tcase(s, tc2_s21_create_matrix);
  suite_add_tcase(s, tc3_s21_create_matrix);
  suite_add_tcase(s, tc4_s21_create_matrix);

  return s;
}
