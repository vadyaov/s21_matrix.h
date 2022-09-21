#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "../s21_matrix.h"

#define DBL_SIZE -1234.2282334, 1234.228234

// helpers
double get_random_double(double min, double max);
matrix_t get_random_matrix(int rows, int columns);
void copy_matrix(matrix_t src, matrix_t *dst);

// Suite
Suite *s21_create_matrix_test();
Suite *s21_remove_matrix_test();
Suite *s21_eq_matrix_test();
Suite *suite_s21_sum_matrix();
Suite *suite_s21_sub_matrix();
Suite *suite_s21_mult_number();
Suite *suite_s21_mult_matrix();
Suite *suite_s21_transpose_matrix();
Suite *suite_s21_calc_complements_matrix();
Suite *suite_s21_determinant_matrix();
Suite *suite_s21_inverse_matrix();

#endif  // SRC_TESTS_TEST_H_
