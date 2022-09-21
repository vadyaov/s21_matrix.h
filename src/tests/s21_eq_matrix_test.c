#include "test.h"

// доделать тесты с разными строками-столбцами и с отрицательными строками
// столбцами для полного покрытия

START_TEST(matrix_eq_test1) {
  matrix_t m1 = get_random_matrix(3, 3);
  matrix_t m2;
  s21_create_matrix(m1.rows, m1.columns, &m2);
  copy_matrix(m1, &m2);
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(matrix_eq_test2) {
  matrix_t *m1 = NULL;
  ;
  matrix_t m2;
  ck_assert_int_eq(s21_eq_matrix(m1, &m2), FAILURE);
}
END_TEST

START_TEST(matrix_eq_test3) {
  matrix_t m1;
  ;
  matrix_t *m2 = NULL;
  ck_assert_int_eq(s21_eq_matrix(&m1, m2), FAILURE);
}
END_TEST

START_TEST(matrix_eq_test4) {
  matrix_t m1 = get_random_matrix(3, 3);
  matrix_t m2 = get_random_matrix(3, 3);
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(matrix_eq_test5) {
  matrix_t m1 = get_random_matrix(3, 3);
  matrix_t m2 = get_random_matrix(4, 4);
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

Suite *s21_eq_matrix_test() {
  Suite *s = suite_create("[s21_eq_matrix] Unit Test");

  TCase *tc1_s21_eq_matrix = tcase_create("eq_matrix_t1");
  TCase *tc2_s21_eq_matrix = tcase_create("eq_matrix_t2");
  TCase *tc3_s21_eq_matrix = tcase_create("eq_matrix_t3");
  TCase *tc4_s21_eq_matrix = tcase_create("eq_matrix_t4");
  TCase *tc5_s21_eq_matrix = tcase_create("eq_matrix_t5");

  tcase_add_loop_test(tc1_s21_eq_matrix, matrix_eq_test1, 0, 10);
  tcase_add_test(tc2_s21_eq_matrix, matrix_eq_test2);
  tcase_add_test(tc3_s21_eq_matrix, matrix_eq_test3);
  tcase_add_test(tc4_s21_eq_matrix, matrix_eq_test4);
  tcase_add_test(tc5_s21_eq_matrix, matrix_eq_test5);

  suite_add_tcase(s, tc1_s21_eq_matrix);
  suite_add_tcase(s, tc2_s21_eq_matrix);
  suite_add_tcase(s, tc3_s21_eq_matrix);
  suite_add_tcase(s, tc4_s21_eq_matrix);
  suite_add_tcase(s, tc5_s21_eq_matrix);

  return s;
}
