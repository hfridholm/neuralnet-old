#ifndef ADJUST_H
#define ADJUST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// String

extern int string_trim_spaces(char* result, const char string[], int length);

extern char* string_copy(char* destin, char* string, int length);

extern char* string_create(int length);

extern void string_free(char** string, int length);

extern int string_split_tokens(char** tokens, int* length, const char string[], const char delim[]);

// String Array

extern char** strarr_create(int amount, int length);

extern void strarr_free(char*** strarr, int amount, int length);

extern char** strarr_copy(char** destin, char** strarr, int amount, int length);

extern bool float_vector_strarr(char** result, float* vector, int length);

extern bool strarr_float_vector(float* vector, char** strarr, int amount);

extern bool strarr_strarr_indexes(int* indexes, char* strarr1[], int amount1, char* strarr2[], int amount2);

extern void strarr_split_tokens(char*** tokens, int* width, int* length, char** strarr, int amount, const char delim[]);

extern int strarr_unique_strings(char** result, char** strarr, int amount1, int length);

// String Matrix 

extern char*** strmat_create(int height, int width, int length);

extern void strmat_free(char**** strmat, int height, int width, int length);

extern char*** strmat_copy(char*** destin, char*** strmat, int height, int width, int length);

extern char*** strmat_duplic(char*** strmat, int height, int width, int length);

extern bool strmat_column_alloc(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column);

extern bool float_matrix_strmat(char*** result, float** matrix, int height, int width);

extern bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width);

extern char*** strmats_add_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2);

extern char*** strmat_column_remove(char*** result, char*** strmat, int height, int width, int length, int column);

extern int strmat_header_index(char*** strmat, int height, int width, const char header[]);

extern bool strmat_filter_index(char*** result, char*** strmat, int height, int width, int length, const int indexes[], int amount);

extern bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column);

#endif
