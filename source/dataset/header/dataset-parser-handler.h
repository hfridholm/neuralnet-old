#ifndef DATASET_PARSER_HANDLER_H
#define DATASET_PARSER_HANDLER_H

extern bool prepare_strmat_data(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* onehotHeaders[], int onehotAmount, char* nrmlizHeaders[], int nrmlizAmount);



extern bool nrmliz_strmat_headers(char*** result, char*** strmat, int height, int width, int length, char* headers[], int amount);

extern bool nrmliz_strmat_header(char*** result, char*** strmat, int height, int width, int length, const char header[]);



extern bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount);



extern bool text_file_tokens(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[]);

extern bool csv_indexis_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[]);

extern bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[]);

extern bool onehot_string_matrix(char*** result, char** strarr1, int height, char** strarr2, int width);

extern bool onehot_strmat_header(char*** result, int* newWidth, char*** strmat, int height, int width, int length, const char header[]);

extern bool onehot_strmat_headers(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* headers[], int amount);

#endif
