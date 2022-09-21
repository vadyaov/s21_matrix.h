#include "test.h"

START_TEST(mult_number) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  double number = get_random_double(DBL_SIZE);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  m = get_random_matrix(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      check.matrix[i][j] = m.matrix[i][j] * number;
    }
  }
  matrix_t res = {0};
  s21_mult_number(&m, number, &res);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(incorrect_matr) {
  matrix_t a;
  a.rows = -1;
  matrix_t result;
  int status = s21_mult_number(&a, 4.56, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_mult_number() {
  Suite *s = suite_create("[s21_mult_number] Unit Test");
  TCase *tc = tcase_create("s21_mult_number");
  TCase *tc1 = tcase_create("s21_incorr_matr");

  tcase_add_loop_test(tc, mult_number, 0, 20);
  tcase_add_test(tc1, incorrect_matr);

  suite_add_tcase(s, tc);
  suite_add_tcase(s, tc1);
  return s;
}
