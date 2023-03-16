#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define EPS 1e-7

#define CALCULATION_ERROR 2
#define ERROR 1
#define GOOD 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/**
 * @brief Функция для инициализации матриц.
 * @param rows Количество строк матрицы.
 * @param columns Количество столбцов матриц.
 * @param result Указатель на область памяти, где хранится матрица.
 * @author sallieam
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief Функция для удаления матрицы.
 * @param A Указатель на область памяти, где хранится матрица.
 * @author sallieam
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief Функция для сравнения матриц.
 * @param A Первая матрица.
 * @param B Вторая матрица.
 * @author sallieam
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/**
 * @brief Функция для сложения матриц.
 * @param A Первая матрица.
 * @param B Вторая матрица.
 * @param result Результат сложения матриц.
 * @author sallieam
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Функция для вычитания матриц.
 * @param A Первая матрица.
 * @param B Вторая матрица.
 * @param result Результат вычитания матриц.
 * @author sallieam
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Функция для умножения матрицы на константу.
 * @param A матрица, которую необходимо умножить на константу.
 * @param number - Константа, на которую умножается матрица.
 * @param result Результат умножения матрицы на константу.
 * @author sallieam
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief Функция для умножения двух матриц.
 * @param A Множимая матрица.
 * @param B Множитель матрица.
 * @param result Результат умножения матриц.
 * @author sallieam
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Функция для транспонирования матрицы.
 * @param A Матрица, которую необходимо транспонировать.
 * @param result Транспонированная матрица.
 * @author sallieam
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * @brief Функция для инициализации матриц.
 * @param rows Количество строк матрицы.
 * @param columns Количество столбцов матриц.
 * @param result Указатель на область памяти, где хранится матрица.
 * @author sallieam
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/**
 * @brief Функция для поиска определителя матрицы.
 * @param A Матрица, определитель которой необходимо посчитать.
 * @param result Определитель.
 * @author sallieam
 */
int s21_determinant(matrix_t *A, double *result);

/**
 * @brief Функция для инверсии матрицы..
 * @param A Матрица, которую необходимо инвертировать.
 * @param result Результат инверсии матрицы.
 * @author sallieam
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// HELP FUNC
int s21_create_matrix(int rows, int columns, matrix_t *result);

int check_param(matrix_t *result);

double **allocate_matrix(int rows, int columns, int *status);

void output_matrix(matrix_t *A);

void det_matrix(matrix_t *A, matrix_t *minor, int rows, int columns);

double s21_get_determinant(matrix_t *A, int size);

void minor_mtrx(matrix_t *A, matrix_t *result);

void fill_matrix(matrix_t *A, double start, double step);

#endif  // SRC_S21_MATRIX_