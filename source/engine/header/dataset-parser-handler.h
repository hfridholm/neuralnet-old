#ifndef DATASET_PARSER_HANDLER_H
#define DATASET_PARSER_HANDLER_H

bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer);

bool extract_text_file(char** fileLines, int* amount, const char filePath[]);

char** create_string_array(int amount, int length);

char*** create_string_matrix(int height, int width, int length);

void free_string_array(char** strArray, int amount, int length);

void free_string_matrix(char*** strMatrix, int height, int width, int length);

int trim_string_spaces(char* result, const char string[], int length);

int split_string_tokens(char** tokens, const char string[], const char delim[]);

int string_array_tokens(char*** tokens, char** strArray, int strAmount, const char delim[]);

float** tokens_float_matrix(float** matrix, char*** tokens, int height, int width);

bool strmat_index_filter(char*** result, char*** strMatrix, int height, int width, const int indexis[], int amount);

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount);

bool text_file_tokens_t(char*** tokens, int* height, int* width, const char filePath[], const char delim[], char** strArray);

bool text_file_tokens(char*** tokens, int* height, int* width, const char filePath[], const char delim[]);

bool csv_indexis_inptrgs_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens);

bool csv_indexis_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[]);

bool strarr_strarr_indexis(int* indexis, char* strarr1[], int amount1, char* strarr2[], int amount2);

bool csv_headers_inptrgs_t(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens);

bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[]);

#endif
