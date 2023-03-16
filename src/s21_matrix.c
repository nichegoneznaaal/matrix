#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int state = GOOD;
  if (rows > 0 && columns > 0 && result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = allocate_matrix(result->rows, result->columns, &state);
    if (state == GOOD) {
      state = check_param(result);
    }
  } else {
    state = ERROR;
  }
  return state;
}

int check_param(matrix_t *result) {
  int res = GOOD;
  if (result != NULL && result->matrix != NULL) {
    if (result->rows > 0 && result->columns > 0) {
      int count = 0;
      for (int i = 0; i < result->rows; i++) {
        if (result->matrix[i]) {
          for (int j = 0; j < result->columns; j++) {
            count++;
          }
        }
      }
      if (count != (result->columns * result->rows)) {
        res = ERROR;
      }
    } else {
      res = ERROR;
    }
  } else {
    res = ERROR;
  }
  return res;
}

double **allocate_matrix(int rows, int columns, int *status) {
  double **matrix = NULL;
  matrix = (double **)malloc(sizeof(double *) * rows);
  *status = GOOD;
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      matrix[i] = (double *)malloc(sizeof(double) * columns);
      if (!matrix[i]) {
        *status = ERROR;
        if (i != 0) {
          for (; i <= 0; i--) {
            free(matrix[i]);
          }
        }
      } else {
        for (int j = 0; j < columns; j++) {
          matrix[i][j] = 0.0;
        }
      }
    }
  } else {
    matrix = NULL;
    *status = ERROR;
  }
  return (matrix);
}

void s21_remove_matrix(matrix_t *A) {
  if (!check_param(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
            result = FAILURE;
            break;
          }
        }
        if (result == 0) {
          break;
        }
      }
    } else {
      result = FAILURE;
    }
  } else {
    result = FAILURE;
  }
  return (result);
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = GOOD;
  if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      int r_buf = s21_create_matrix(A->rows, A->columns, result);
      if (!r_buf) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        res = ERROR;
      }
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = ERROR;
  }
  return (res);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = GOOD;
  if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      int r_buf = s21_create_matrix(A->rows, A->columns, result);
      if (!r_buf) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        res = ERROR;
      }
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = ERROR;
  }
  return (res);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = GOOD;
  if (A != NULL && A->matrix != NULL) {
    int r_buf = s21_create_matrix(A->rows, A->columns, result);
    if (!r_buf) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      res = ERROR;
    }
  } else {
    res = ERROR;
  }
  return (res);
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = GOOD;
  if ((A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL) &&
      (A->columns == B->rows)) {
    int r_buf = s21_create_matrix(A->rows, B->columns, result);
    if (!r_buf) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      res = ERROR;
    }
  } else {
    if (A->columns != B->rows) {
      res = CALCULATION_ERROR;
    } else {
      res = ERROR;
    }
  }
  return (res);
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = GOOD;
  if (A != NULL && A->matrix != NULL) {
    int r_buf = s21_create_matrix(A->columns, A->rows, result);
    if (!r_buf) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    } else {
      res = ERROR;
    }
  } else {
    res = ERROR;
  }
  return (res);
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int state = GOOD;
  if (A != NULL && A->matrix != NULL) {
    if (A->rows == A->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        matrix_t minor_buf = {0};
        int row = A->rows;
        if (A->rows == 1) {
          result->matrix[0][0] = A->matrix[0][0];
          row--;
        }
        for (int i = 0; i < row; i++) {
          for (int j = 0; j < result->columns; j++) {
            det_matrix(A, &minor_buf, i, j);
            double det = 0;
            s21_determinant(&minor_buf, &det);
            result->matrix[i][j] = pow(-1, i + j) * det;
            s21_remove_matrix(&minor_buf);
          }
        }
      } else {
        state = ERROR;
      }
    } else {
      state = CALCULATION_ERROR;
    }
  } else {
    state = ERROR;
  }
  return state;
}

int s21_determinant(matrix_t *A, double *result) {
  int state = GOOD;
  if (A != NULL && A->matrix != NULL) {
    if (A->rows == A->columns && result) {
      if (A->columns > 1) {
        *result = s21_get_determinant(A, A->columns);
      } else if (A->columns == 1) {
        *result = A->matrix[0][0];
      }
    } else {
      state = CALCULATION_ERROR;
    }
  } else {
    state = ERROR;
  }
  return state;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det = 0;
  int state = GOOD;
  if ((A != NULL && A->matrix != NULL)) {
    if (A->rows == A->columns) {
      s21_determinant(A, &det);
      if (det != 0) {
        if (A->rows == 1) {
          s21_create_matrix(A->rows, A->columns, result);
          result->matrix[0][0] = 1 / A->matrix[0][0];
        } else if (A->rows > 1) {
          s21_calc_complements(A, result);
          matrix_t comp = {0};
          s21_transpose(result, &comp);
          s21_remove_matrix(result);
          s21_mult_number(&comp, 1.0 / det, result);
          s21_remove_matrix(&comp);
        } else {
          state = ERROR;
        }
      } else {
        state = CALCULATION_ERROR;
      }
    } else {
      state = CALCULATION_ERROR;
    }
  } else {
    state = ERROR;
  }
  return state;
}

void det_matrix(matrix_t *A, matrix_t *minor, int rows, int columns) {
  if (!s21_create_matrix(A->rows - 1, A->rows - 1, minor)) {
    int r = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == rows) {
        continue;
      }
      for (int j = 0, col = 0; j < A->columns; j++) {
        if (j == columns) {
          continue;
        }
        minor->matrix[r][col++] = A->matrix[i][j];
      }
      r++;
    }
  }
}

double s21_get_determinant(matrix_t *A, int size) {
  double result = 0;
  if (size == 2) {
    result +=
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    for (int i = 0, sign = 1; i < size; i++, sign *= -1) {
      matrix_t buf = {0};
      det_matrix(A, &buf, i, 0);
      result += A->matrix[i][0] * sign * s21_get_determinant(&buf, size - 1);
      s21_remove_matrix(&buf);
    }
  }
  return result;
}

void fill_matrix(matrix_t *A, double start, double step) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = start;
      start += step;
    }
  }
}
