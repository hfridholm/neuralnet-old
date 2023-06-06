#ifndef DATASET_PARSER_HANDLER_H
#define DATASET_PARSER_HANDLER_H

bool count_file_lines(int* amount, const char filePath[]);

bool prepare_strmat_data(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* onehotHeaders[], int onehotAmount, char* nrmlizHeaders[], int nrmlizAmount);

bool alloc_strmat_column(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column);

bool float_vector_strarr(char** result, float* vector, int length);

bool nrmliz_strmat_headers(char*** result, char*** strmat, int height, int width, int length, char* headers[], int amount);

bool nrmliz_strmat_header(char*** result, char*** strmat, int height, int width, int length, const char header[]);

bool float_matrix_strmat(char*** result, float** matrix, int height, int width);

bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer);

bool extract_text_file(char** fileLines, int* amount, const char filePath[]);

char** create_string_array(int amount, int length);

char*** create_string_matrix(int height, int width, int length);

void free_string_array(char** strArray, int amount, int length);

void free_string_matrix(char*** strMatrix, int height, int width, int length);

int trim_string_spaces(char* result, const char string[], int length);

int split_string_tokens(char** tokens, int* length, const char string[], const char delim[]);

void string_array_tokens(char*** tokens, int* width, int* length, char** strArray, int strAmount, const char delim[]);

bool strarr_float_vector(float* vector, char** strarr, int amount);

bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width);

bool strmat_index_filter(char*** result, char*** strMatrix, int height, int width, int length, const int indexis[], int amount);

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount);

bool text_file_tokens_t(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[], char** strArray);

bool text_file_tokens(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[]);

bool csv_indexis_inptrgs_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens);

bool csv_indexis_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[]);

bool strarr_strarr_indexis(int* indexis, char* strarr1[], int amount1, char* strarr2[], int amount2);

bool csv_headers_inptrgs_t(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens);

bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[]);

bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column);

char*** merge_strmat_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2);

bool onehot_string_matrix(char*** result, char** strarr1, int height, char** strarr2, int width);

int strarr_single_strings(char** result, char** strarr, int amount1, int length);

bool onehot_strmat_header(char*** result, int* newWidth, char*** strmat, int height, int width, int length, const char header[]);

char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length);

char** copy_string_array(char** destin, char** strarr, int amount, int length);

int strmat_header_index(char*** strmat, int height, int width, const char header[]);

char*** remove_strmat_column(char*** result, char*** strmat, int height, int width, int length, int column);

bool onehot_strmat_headers(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* headers[], int amount);

char*** duplic_string_matrix(char*** strmat, int height, int width, int length);

#endif
