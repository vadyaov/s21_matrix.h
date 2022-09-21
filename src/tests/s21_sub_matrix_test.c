#include "test.h"

START_TEST(sub_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  m = get_random_matrix(rows, cols);
  mtx = get_random_matrix(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};
  int status = s21_sub_matrix(&m, &mtx, &res);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(calcul_err) {
  matrix_t a = get_random_matrix(3, 3);
  matrix_t b = get_random_matrix(2, 3);
  matrix_t result;
  int status = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(status, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(incorrect_matr) {
  matrix_t a;
  matrix_t b;
  a.rows = -1;
  b.columns = 0;
  matrix_t result;
  int status = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_sub_matrix() {
  Suite *s = suite_create("[s21_sub_matrix] Unit Test");
  TCase *tc = tcase_create("s21_sub_matrix");
  TCase *tc1 = tcase_create("s21_sub_er1");
  TCase *tc2 = tcase_create("s21_sub_er2");

  tcase_add_loop_test(tc, sub_matrix, 0, 20);
  tcase_add_test(tc1, calcul_err);
  tcase_add_test(tc1, incorrect_matr);

  suite_add_tcase(s, tc);
  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  return s;
}
