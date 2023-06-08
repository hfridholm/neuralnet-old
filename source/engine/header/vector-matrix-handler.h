#ifndef VECTOR_MATRIX_HANDLER_H
#define VECTOR_MATRIX_HANDLER_H

extern bool float_vector_minmax(float* minValue, float* maxValue, float* vector, int length);

extern float create_random_float(float minimum, float maximum);

extern float* create_float_vector(int length);

extern float** create_float_matrix(int height, int width);

extern float*** create_fmatrix_array(int amount, int height, int width);

extern void free_float_vector(float** vector, int length);

extern void free_float_matrix(float*** matrix, int height, int width);

extern void free_fmatrix_array(float**** matarr, int amount, int height, int width);

extern float*** fill_fmatarr_random(float*** matarr, int amount, int height, int width, float minimum, float maximum);

extern float** fill_fmatrix_random(float** matrix, int height, int width, float minimum, float maximum);

extern float* fill_fvector_random(float* vector, int length, float minimum, float maximum);

extern float** transp_float_matrix(float** transp, float** matrix, int height, int width);

extern float** multi_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor);

extern float* multi_scale_fvector(float* result, float* vector, int length, float scalor);

extern float*** multi_scale_fmatarr(float*** result, float*** matarr, int amount, int height, int width, float scalor);

extern float** addit_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor);

extern float** multi_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width);

extern float* multi_elem_fvector(float* result, float* vector1, float* vector2, int length);

extern float** addit_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width);

extern float* addit_elem_fvector(float* result, float* vector1, float* vector2, int length);

extern float*** addit_elem_fmatarr(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width);

extern float** addit_fmatrix_rvect(float** result, float** matrix, float* vector, int height, int width);

extern bool dotprod_float_matrix(float** result, float** matrix1, int height1, int width1, float** matrix2, int height2, int width2);

extern float** dotprod_float_vector(float** result, float* vector1, int length1, float* vector2, int length2);

extern bool dotprod_fmatrix_vector(float* result, float** matrix, int height, int width, float* vector, int length);

extern float** cnvrt_fvector_fmatrix(float** matrix, float* vector, int length);

extern float** cnvrt_fmatrix_fvector(float* vector, float** matrix, int height, int width);

extern float** fmatrix_elem_action(float** result, float** matrix, int height, int width, float (*float_action_funct)(float));

extern float* fvector_elem_action(float* result, float* vector, int length, float (*float_action_funct)(float));

extern float*** copy_fmatrix_array(float*** destin, float*** matarr, int amount, int height, int width);

extern float** copy_float_matrix(float** destin, float** matrix, int height, int width);

extern float* copy_float_vector(float* destin, float* vector, int length);

extern float** duplic_float_matrix(float** matrix, int height, int width);

extern float* duplic_float_vector(float* vector, int length);

extern float vector_maximum_float(float* vector, int length);

extern float float_vector_total(float* vector, int length);

extern void print_fmatrix_array(float*** matarr, int amount, int height, int width);

extern void print_float_matrix(float** matrix, int height, int width);

extern void print_float_vector(float* vector, int length);

extern int* create_integ_array(int length);

extern void free_integ_array(int** array, int length);

extern int* random_indexes_array(int* array, int length);

extern int* shuffle_integ_array(int* array, int length);

extern int* switch_array_ints(int* array, int index1, int index2);

#endif
