#ifndef ARRAY_STRING_HANDLER_H
#define ARRAY_STRING_HANDLER_H

extern char** create_string_array(int amount, int length);

extern char*** create_string_matrix(int height, int width, int length);



extern void free_string_array(char** strArray, int amount, int length);

extern void free_string_matrix(char*** strMatrix, int height, int width, int length);



extern char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length);

extern char** copy_string_array(char** destin, char** strarr, int amount, int length);

extern char* copy_char_string(char* destin, char* string, int length);



extern char*** duplic_string_matrix(char*** strmat, int height, int width, int length);



extern bool alloc_strmat_column(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column);



extern bool float_matrix_strmat(char*** result, float** matrix, int height, int width);

extern bool float_vector_strarr(char** result, float* vector, int length);



extern bool strarr_float_vector(float* vector, char** strarr, int amount);

extern bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width);



extern int trim_string_spaces(char* result, const char string[], int length);



extern bool strarr_strarr_indexis(int* indexis, char* strarr1[], int amount1, char* strarr2[], int amount2);



extern char*** merge_strmat_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2);



extern int strarr_single_strings(char** result, char** strarr, int amount1, int length);



extern char*** remove_strmat_column(char*** result, char*** strmat, int height, int width, int length, int column);



extern int strmat_header_index(char*** strmat, int height, int width, const char header[]);



extern int split_string_tokens(char** tokens, int* length, const char string[], const char delim[]);

extern void string_array_tokens(char*** tokens, int* width, int* length, char** strArray, int strAmount, const char delim[]);



extern bool strmat_index_filter(char*** result, char*** strMatrix, int height, int width, int length, const int indexis[], int amount);



extern bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column);

#endif

