#ifndef _SRC_S21_MATRIX_H
#define _SRC_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
#define MEM_ALLOC_ERROR 3

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helpers
void print_matrix(matrix_t matrix);
void scan_matrix(matrix_t *matrix);

double row_col_mult(int i, int j, matrix_t *A, matrix_t *B);
double minor_calc(matrix_t *A, int i, int j);
void simple_minor(matrix_t *A, matrix_t *result);
matrix_t create_smaller(matrix_t *A, int i, int j);
double determinant(matrix_t A);
void init_matrix(matrix_t *A);

#endif  // _SRC_S21_MATRIX_H
