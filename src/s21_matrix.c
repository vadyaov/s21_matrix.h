#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int create_status = OK;
  init_matrix(result);
  if (rows <= 0 || columns <= 0) {
    create_status = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(result->rows, sizeof(double *));
    if (result->matrix) {
      for (int i = 0, stop = 0; i < rows && !stop; i++) {
        result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = i - 1; j >= 0; j--) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          stop = 1;
          create_status = MEM_ALLOC_ERROR;
        }
      }
    } else {
      create_status = MEM_ALLOC_ERROR;
    }
  }
  if (create_status) {
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
  }
  return create_status;
}
void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    init_matrix(A);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int compare_result = SUCCESS;
  if (A && B) {
    if (A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0 &&
        A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows && compare_result; i++)
        for (int j = 0; j < A->columns && compare_result; j++) {
          double a_int = 0.0, b_int = 0.0,
                 a_point = modf(A->matrix[i][j], &a_int) * pow(10.0, 7.0),
                 b_point = modf(B->matrix[i][j], &b_int) * pow(10.0, 7.0);
          long long int A_int = a_int, B_int = b_int, A_point = a_point,
                        B_point = b_point;
          if (A_int != B_int || A_point != B_point) compare_result = FAILURE;
        }
    } else {
      compare_result = FAILURE;
    }
  } else {
    compare_result = FAILURE;
  }
  return compare_result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int sum_status = OK;
  init_matrix(result);
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      } else {
        sum_status = MEM_ALLOC_ERROR;
      }
    } else {
      sum_status = CALC_ERROR;
    }
  } else {
    sum_status = INCORRECT_MATRIX;
  }
  return sum_status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int sub_status = OK;
  init_matrix(result);
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      } else {
        sub_status = MEM_ALLOC_ERROR;
      }
    } else {
      sub_status = CALC_ERROR;
    }
  } else {
    sub_status = INCORRECT_MATRIX;
  }
  return sub_status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int mult_status = OK;
  init_matrix(result);
  if (A && A->rows > 0 && A->columns > 0) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
    } else {
      mult_status = MEM_ALLOC_ERROR;
    }
  } else {
    mult_status = INCORRECT_MATRIX;
  }
  return mult_status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int mult_status = OK;
  init_matrix(result);
  if (A && A->rows > 0 && A->columns > 0 && B && B->rows > 0 &&
      B->columns > 0) {
    if (A->columns == B->rows) {
      if (!s21_create_matrix(A->rows, B->columns, result)) {
        for (int i = 0; i < result->rows; i++)
          for (int j = 0; j < result->columns; j++)
            result->matrix[i][j] = row_col_mult(i, j, A, B);
      } else {
        mult_status = MEM_ALLOC_ERROR;
      }
    } else {
      mult_status = CALC_ERROR;
    }
  } else {
    mult_status = INCORRECT_MATRIX;
  }
  return mult_status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int transpose_status = OK;
  init_matrix(result);
  if (A && A->rows > 0 && A->columns > 0) {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
          result->matrix[i][j] = A->matrix[j][i];
    } else {
      transpose_status = MEM_ALLOC_ERROR;
    }
  } else {
    transpose_status = INCORRECT_MATRIX;
  }
  return transpose_status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int calc_complements_status = OK;
  init_matrix(result);
  if (A && A->rows > 0) {
    if (A->rows == A->columns && A->rows != 1) {
      int n = A->rows;
      if (!s21_create_matrix(n, n, result)) {
        if (n == 2) {
          simple_minor(A, result);
        } else {
          for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
              result->matrix[i][j] = minor_calc(A, i, j) * pow(-1.0, i + j);
        }
      } else {
        calc_complements_status = MEM_ALLOC_ERROR;
      }
    } else {
      calc_complements_status = CALC_ERROR;
    }
  } else {
    calc_complements_status = INCORRECT_MATRIX;
  }
  return calc_complements_status;
}

int s21_determinant(matrix_t *A, double *result) {
  int determinant_status = OK;
  *result = 0.0;
  if (A && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      if (A->rows == 1)
        *result = A->matrix[0][0];
      else
        *result = determinant(*A);
    } else {
      determinant_status = CALC_ERROR;
    }
  } else {
    determinant_status = INCORRECT_MATRIX;
  }
  return determinant_status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det = 0.0;
  init_matrix(result);
  int inverse_status = s21_determinant(A, &det);
  if (fabs(det) < 1e-7) inverse_status = CALC_ERROR;
  if (inverse_status == OK) {
    if (A->rows == 1) {
      if (!s21_create_matrix(1, 1, result))
        result->matrix[0][0] = (double)1 / det;
    } else {
      matrix_t calc_components, transpose;
      if (!s21_transpose(A, &transpose)) {
        if (!s21_calc_complements(&transpose, &calc_components)) {
          if (s21_mult_number(&calc_components, (double)1 / det, result))
            inverse_status = MEM_ALLOC_ERROR;
          s21_remove_matrix(&transpose);
          s21_remove_matrix(&calc_components);
        } else {
          inverse_status = MEM_ALLOC_ERROR;
          s21_remove_matrix(&transpose);
        }
      } else {
        inverse_status = MEM_ALLOC_ERROR;
      }
    }
  }
  return inverse_status;
}
