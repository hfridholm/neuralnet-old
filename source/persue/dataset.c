#include "../persue.h"

static bool text_file_tokens_t(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[], char** strArray)
{
  if(!extract_text_file(strArray, height, filePath)) return false;

  string_array_tokens(tokens, width, length, strArray, *height, delim);

  return true;
}

bool text_file_tokens(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[])
{
  char** strArray = create_string_array(256, 256);

  bool result = text_file_tokens_t(tokens, height, width, length, filePath, delim, strArray);

  free_string_array(&strArray, 256, 256); return result;
}

bool nrmliz_strmat_header(char*** result, char*** strmat, int height, int width, int length, const char header[])
{
  int headerIndex = strmat_header_index(strmat, height, width, header);

  if(headerIndex < 0) return false;  

  char** strarr = create_string_array(height, length);

  strmat_column_strarr(strarr, strmat, height, width, length, headerIndex);

  float* vector = create_float_vector(height - 1);

  strarr_float_vector(vector, strarr + 1, height - 1);


  float minValue, maxValue;

  float_vector_minmax(&minValue, &maxValue, vector, height - 1);
  
  for(int index = 0; index < height - 1; index += 1)
  {
    vector[index] = (vector[index] - minValue) / (maxValue - minValue);
  }

  float_vector_strarr(strarr + 1, vector, height - 1);

  
  free_float_vector(&vector, height - 1);


  alloc_strmat_column(result, strmat, height, width, length, strarr, length, headerIndex);

  
  free_string_array(&strarr, height, length);

  return true;
}

bool nrmliz_strmat_headers(char*** result, char*** strmat, int height, int width, int length, char* headers[], int amount)
{
  if(amount <= 0) return false;

  nrmliz_strmat_header(result, strmat, height, width, length, headers[0]);

  for(int index = 1; index < amount; index += 1)
  {
    nrmliz_strmat_header(result, result, height, width, length, headers[index]);
  }
  return true;
}

bool onehot_string_matrix(char*** result, char** strarr1, int height, char** strarr2, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      if(!strcmp(strarr1[hIndex], strarr2[wIndex]))
      {
        strcpy(result[hIndex][wIndex], "1");
      }
      else strcpy(result[hIndex][wIndex], "0");
    }
  }
  return result;
}

bool onehot_strmat_header(char*** result, int* newWidth, char*** strmat, int height, int width, int length, const char header[])
{
  int headerIndex = strmat_header_index(strmat, height, width, header);

  if(headerIndex < 0) return false;


  char** columnStrarr = create_string_array(height, length); 

  strmat_column_strarr(columnStrarr, strmat + 1, height - 1, width, length, headerIndex);


  char** singleStrarr = create_string_array(height - 1, length);

  int singleAmount = strarr_single_strings(singleStrarr, columnStrarr, height - 1, length);

  
  char*** newStrmat = create_string_matrix(height - 1, singleAmount, length);

  onehot_string_matrix(newStrmat, columnStrarr, height - 1, singleStrarr, singleAmount);


  char*** addStrmat = create_string_matrix(height, singleAmount, length);

  copy_string_array(addStrmat[0], singleStrarr, singleAmount, length);
  
  copy_string_matrix(addStrmat + 1, newStrmat, height - 1, singleAmount, length);

  *newWidth = width - 1 + singleAmount;


  char*** tempStrmat = create_string_matrix(height, width, length);

  remove_strmat_column(tempStrmat, strmat, height, width, length, headerIndex); 

  merge_strmat_columns(result, tempStrmat, height, width - 1, length, addStrmat, singleAmount, length);

  free_string_matrix(&tempStrmat, height, width, length);


  free_string_matrix(&addStrmat, height, singleAmount, length);

  free_string_matrix(&newStrmat, height - 1, singleAmount, length);

  free_string_array(&singleStrarr, height - 1, length);

  free_string_array(&columnStrarr, height, length);

  return true;
}

bool onehot_strmat_headers(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* headers[], int amount)
{
  if(amount <= 0) return false;

  if(!onehot_strmat_header(result, newWidth, strmat, height, width, length, headers[0])) return false; 

  for(int index = 1; index < amount; index += 1)
  {
    //char*** strmatCopy = duplic_string_matrix(result, height, *newWidth, 10);

    if(!onehot_strmat_header(result, newWidth, result, height, *newWidth, length, headers[index])) return false; 

    //free_string_matrix(strmatCopy, height, *newWidth, 10);
  }
  return true;
}

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount)
{
  char*** inputTokens = create_string_matrix(height, width, length);
  char*** targetTokens = create_string_matrix(height, width, length);

  if(!strmat_index_filter(inputTokens, tokens, height, width, length, inputIndexis, inputAmount));
  if(!strmat_index_filter(targetTokens, tokens, height, width, length, targetIndexis, targetAmount));

  strmat_float_matrix(inputs, inputTokens, height, inputAmount);
  strmat_float_matrix(targets, targetTokens, height, targetAmount);

  free_string_matrix(&inputTokens, height, width, length);
  free_string_matrix(&targetTokens, height, width, length);

  return true;
}

static bool csv_indexes_inptrgs_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) return false;

  *height = tHeight - 1;

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }

  return tokens_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, tLength, inputIndexis, inputAmount, targetIndexis, targetAmount);
}

bool csv_indexes_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_indexes_inptrgs_t(inputs, targets, height, inputIndexis, inputAmount, targetIndexis, targetAmount, filePath, tokens);

  free_string_matrix(&tokens, 100, 10, 10); return result;
}

static bool csv_headers_inptrgs_t(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) return false;

  *height = tHeight - 1;

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }

  int* inputIndexis = malloc(sizeof(int) * inputAmount);
  int* targetIndexis = malloc(sizeof(int) * targetAmount);

  if(!strarr_strarr_indexes(inputIndexis, tokens[0], tWidth, inputHeaders, inputAmount))
  {
    free_integ_array(&inputIndexis, inputAmount);
    free_integ_array(&targetIndexis, targetAmount);
    return false;
  }

  if(!strarr_strarr_indexes(targetIndexis, tokens[0], tWidth, targetHeaders, targetAmount))
  {
    free_integ_array(&inputIndexis, inputAmount);
    free_integ_array(&targetIndexis, targetAmount);
    return false;
  }

  bool result = tokens_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, tLength, inputIndexis, inputAmount, targetIndexis, targetAmount);

  free_integ_array(&inputIndexis, inputAmount);
  free_integ_array(&targetIndexis, targetAmount);

  return result;
}

bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_headers_inptrgs_t(inputs, targets, height, inputHeaders, inputAmount, targetHeaders, targetAmount, filePath, tokens);

  free_string_matrix(&tokens, 100, 10, 10); return result;
}

bool prepare_strmat_data(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* onehotHeaders[], int onehotAmount, char* nrmlizHeaders[], int nrmlizAmount)
{
  if(!onehot_strmat_headers(result, newWidth, strmat, height, width, length, onehotHeaders, onehotAmount)) return false;

  return nrmliz_strmat_headers(result, result, height, *newWidth, length, nrmlizHeaders, nrmlizAmount);
}