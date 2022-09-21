#include "test.h"

START_TEST(matrix_remove_test1) {
  int rows = rand() % 100;
  int columns = rand() % 100;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);
  if (code == OK) {
    s21_remove_matrix(&matrix);
    ck_assert_ptr_null(matrix.matrix);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
  }
}
END_TEST

Suite *s21_remove_matrix_test() {
  Suite *s = suite_create("[s21_remove_matrix] Unit Test");
  TCase *tc1_s21_create_matrix = tcase_create("remove_matrix_t1");

  tcase_add_loop_test(tc1_s21_create_matrix, matrix_remove_test1, 0, 10);

  suite_add_tcase(s, tc1_s21_create_matrix);
  return s;
}
