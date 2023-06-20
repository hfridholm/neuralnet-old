#ifndef ADJUST_H
#define ADJUST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// String

extern int trim_string_spaces(char* result, const char string[], int length);

extern char* copy_char_string(char* destin, char* string, int length);

extern char* create_char_string(int length);

extern void free_char_string(char** string, int length);

extern int split_string_tokens(char** tokens, int* length, const char string[], const char delim[]);

// String Array

extern char** create_string_array(int amount, int length);

extern void free_string_array(char*** strarr, int amount, int length);

extern char** copy_string_array(char** destin, char** strarr, int amount, int length);

extern bool float_vector_strarr(char** result, float* vector, int length);

extern bool strarr_float_vector(float* vector, char** strarr, int amount);

extern bool strarr_strarr_indexes(int* indexes, char* strarr1[], int amount1, char* strarr2[], int amount2);

extern void string_array_tokens(char*** tokens, int* width, int* length, char** strarr, int amount, const char delim[]);

extern int strarr_single_strings(char** result, char** strarr, int amount1, int length);

// String Matrix 

extern char*** create_string_matrix(int height, int width, int length);

extern void free_string_matrix(char**** strmat, int height, int width, int length);

extern char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length);

extern char*** duplic_string_matrix(char*** strmat, int height, int width, int length);

extern bool alloc_strmat_column(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column);

extern bool float_matrix_strmat(char*** result, float** matrix, int height, int width);

extern bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width);

extern char*** merge_strmat_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2);

extern char*** remove_strmat_column(char*** result, char*** strmat, int height, int width, int length, int column);

extern int strmat_header_index(char*** strmat, int height, int width, const char header[]);

extern bool strmat_index_filter(char*** result, char*** strmat, int height, int width, int length, const int indexes[], int amount);

extern bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column);

#endif
