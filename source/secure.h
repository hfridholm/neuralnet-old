#ifndef SECURE_H
#define SECURE_H

#include <math.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

// Float Vector

extern float    float_random_create(float minimum, float maximum);

extern float*   float_vector_create(int length);

extern bool     float_vector_minmax(float* minimum, float* maximum, float* vector, int length);

extern void     float_vector_free(float** vector, int length);

extern float*   float_vector_random_fill(float* vector, int length, float minimum, float maximum);

extern float*   float_vector_scale_multi(float* result, float* vector, int length, float scalor);

extern float*   float_vector_elem_multi(float* result, float* vector1, float* vector2, int length);

extern float*   float_vector_elem_addit(float* result, float* vector1, float* vector2, int length);

extern float**  float_vector_dotprod(float** result, float* vector1, int length1, float* vector2, int length2);

extern float*   float_vector_copy(float* destin, float* vector, int length);

extern float*   float_vector_duplic(float* vector, int length);

extern float    float_vector_maximum(float* vector, int length);

extern float    float_vector_total(float* vector, int length);

extern bool     float_vector_print(float* vector, int length);

// Float Matrix

extern bool     float_matrix_filter_index(float** result, float** matrix, int height, int width, const int indexes[], int amount);

extern bool     float_matrix_column_vector(float* vector, float** matrix, int height, int width, int column);

extern float**  float_matrix_create(int height, int width);

extern void     float_matrix_free(float*** matrix, int height, int width);

extern float**  float_matrix_random_create(int height, int width, float minimum, float maximum);

extern float**  float_matrix_random_fill(float** matrix, int height, int width, float minimum, float maximum);

extern float**  float_matrix_transp(float** transp, float** matrix, int height, int width);

extern float**  float_matrix_scale_multi(float** result, float** matrix, int height, int width, float scalor);

extern float**  float_matrix_scale_addit(float** result, float** matrix, int height, int width, float scalor);

extern float**  float_matrix_elem_multi(float** result, float** matrix1, float** matrix2, int height, int width);

extern float**  float_matrix_elem_addit(float** result, float** matrix1, float** matrix2, int height, int width);

extern float**  float_matrix_vector_addit(float** result, float** matrix, float* vector, int height, int width);

extern bool     float_matrix_dotprod(float** result, float** matrix1, int height1, int width1, float** matrix2, int height2, int width2);

extern bool     float_matrix_vector_dotprod(float* result, float** matrix, int height, int width, float* vector, int length);

extern float**  float_vector_cnvrt_matrix(float** matrix, float* vector, int length);

extern float**  float_matrix_cnvrt_vector(float* vector, float** matrix, int height, int width);

extern float**  float_matrix_copy(float** destin, float** matrix, int height, int width);

extern float**  float_matrix_duplic(float** matrix, int height, int width);

extern bool     float_matrix_print(float** matrix, int height, int width);

// Float Matarr

extern float*** float_matarr_create(int amount, int height, int width);

extern void     float_matarr_free(float**** matarr, int amount, int height, int width);

extern float*** float_matarr_random_create(int amount, int height, int width, float minimum, float maximum);

extern float*** float_matarr_random_fill(float*** matarr, int amount, int height, int width, float minimum, float maximum);

extern float*** float_matarr_scale_multi(float*** result, float*** matarr, int amount, int height, int width, float scalor);

extern float*** float_matarr_elem_addit(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width);

extern float*** float_matarr_copy(float*** destin, float*** matarr, int amount, int height, int width);

extern bool     float_matarr_print(float*** matarr, int amount, int height, int width);

// Index Array

extern int  index_random_create(int minimum, int maximum);

extern int* index_array_create(int amount);

extern void index_array_free(int** array, int amount);

extern int* index_array_shuffle(int* array, int amount);

#endif // SECURE_H
