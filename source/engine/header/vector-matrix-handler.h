#ifndef VECTOR_MATRIX_HANDLER_H
#define VECTOR_MATRIX_HANDLER_H

float create_random_float(float minimum, float maximum);

float* create_float_vector(int length);

float** create_float_matrix(int height, int width);

float*** create_fmatrix_array(int amount, int height, int width);

void free_float_vector(float* vector, int length);

void free_float_matrix(float** matrix, int height, int width);

void free_fmatrix_array(float*** matrixArray, int amount, int height, int width);

float*** fill_fmatarr_random(float*** matrixArray, int amount, int height, int width, float minimum, float maximum);

float** fill_fmatrix_random(float** matrix, int height, int width, float minimum, float maximum);

float* fill_fvector_random(float* vector, int length, float minimum, float maximum);

float** transp_float_matrix(float** transp, float** matrix, int height, int width);

float** multi_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor);

float* multi_scale_fvector(float* result, float* vector, int length, float scalor);

float*** multi_scale_fmatarr(float*** result, float*** matarr, int amount, int height, int width, float scalor);

float** addit_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor);

float** multi_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width);

float* multi_elem_fvector(float* result, float* vector1, float* vector2, int length);

float** addit_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width);

float* addit_elem_fvector(float* result, float* vector1, float* vector2, int length);

float*** addit_elem_fmatarr(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width);

float** addit_fmatrix_rvect(float** result, float** matrix, float* vector, int height, int width);

bool dotprod_float_matrix(float** result, float** matrix1, int height1, int width1, float** matrix2, int height2, int width2);

float** dotprod_float_vector(float** result, float* vector1, int length1, float* vector2, int length2);

bool dotprod_fmatrix_vector(float* result, float** matrix, int height, int width, float* vector, int length);

float** cnvrt_fvector_fmatrix(float** matrix, float* vector, int length);

float** cnvrt_fmatrix_fvector(float* vector, float** matrix, int height, int width);

float** fmatrix_elem_action(float** result, float** matrix, int height, int width, float (*float_action_funct)(float));

float* fvector_elem_action(float* result, float* vector, int length, float (*float_action_funct)(float));

float** copy_float_matrix(float** destin, float** matrix, int height, int width);

float* copy_float_vector(float* destin, float* vector, int length);

float** duplic_float_matrix(float** matrix, int height, int width);

float* duplic_float_vector(float* vector, int length);

float vector_maximum_float(float* vector, int length);

float float_vector_total(float* vector, int length);

void print_fmatrix_array(float*** matrixArray, int amount, int height, int width);

void print_float_matrix(float** matrix, int height, int width);

void print_float_vector(float* vector, int length);

#endif