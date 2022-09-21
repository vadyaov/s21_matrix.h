#include "s21_matrix.h"

/*
void print_matrix(matrix_t matrix) {
    printf("rows = %d\tcolumns = %d\n", matrix.rows, matrix.columns);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            if (j ==  matrix.columns - 1 && i != matrix.rows - 1)
                printf("%.7lf\n", matrix.matrix[i][j]);
            else
                printf("%.7lf ", matrix.matrix[i][j]);
        }
    }
}
*/
/*
void scan_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            scanf("%lf", &matrix->matrix[i][j]);
        }
    }
}
*/

double row_col_mult(int i, int j, matrix_t *A, matrix_t *B) {
  double ij_element = 0.0;
  for (int k = 0; k < A->columns; k++)
    ij_element += A->matrix[i][k] * B->matrix[k][j];
  return ij_element;
}

void simple_minor(matrix_t *A, matrix_t *result) {
  result->matrix[0][0] = A->matrix[1][1];
  result->matrix[0][1] = -A->matrix[1][0];
  result->matrix[1][0] = -A->matrix[0][1];
  result->matrix[1][1] = A->matrix[0][0];
}

double minor_calc(matrix_t *A, int i, int j) {
  matrix_t smaller;
  double minor = 0.0;
  smaller = create_smaller(A, i, j);
  minor = determinant(smaller);
  s21_remove_matrix(&smaller);
  return minor;
}

matrix_t create_smaller(matrix_t *A, int i, int j) {
  matrix_t smaller;
  int sz = A->rows;
  s21_create_matrix(sz - 1, sz - 1, &smaller);
  for (int k = 0, n = 0; k < sz; k++) {
    if (k == i) continue;
    for (int l = 0, m = 0; l < sz; l++) {
      if (l == j) continue;
      smaller.matrix[n][m] = A->matrix[k][l];
      m++;
    }
    n++;
  }
  return smaller;
}

double determinant(matrix_t A) {
  double result = 0.0;
  if (A.rows == 2) {
    result = A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];
    return result;
  }
  for (int j = 0; j < A.columns; j++) {
    matrix_t smaller = create_smaller(&A, 0, j);
    result += pow(-1.0, j) * determinant(smaller) * A.matrix[0][j];
    s21_remove_matrix(&smaller);
  }
  return result;
}

void init_matrix(matrix_t *A) {
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
