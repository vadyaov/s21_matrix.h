#include "test.h"

double get_random_double(double min, double max) {
  //  max always bigger than min
  double rand1 = (double)rand() / (double)RAND_MAX;
  double range = max - min;
  return rand1 * range + min;
}

matrix_t get_random_matrix(int rows, int columns) {
  matrix_t result_matrix;
  s21_create_matrix(rows, columns, &result_matrix);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result_matrix.matrix[i][j] = get_random_double(DBL_SIZE);
    }
  }
  return result_matrix;
}

void copy_matrix(matrix_t src, matrix_t *dst) {
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.columns; j++) {
      dst->matrix[i][j] = src.matrix[i][j];
    }
  }
}
