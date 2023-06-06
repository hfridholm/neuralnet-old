#include "../header/engine-include-header.h"

bool count_file_lines(int* amount, const char filePath[])
{
  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;
  
  char buffer[256]; int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;
  }
  fclose(filePointer);

  *amount = index; return true;
}

bool prepare_strmat_data(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* onehotHeaders[], int onehotAmount, char* nrmlizHeaders[], int nrmlizAmount)
{
  if(!onehot_strmat_headers(result, newWidth, strmat, height, width, length, onehotHeaders, onehotAmount)) return false;

  return nrmliz_strmat_headers(result, result, height, *newWidth, length, nrmlizHeaders, nrmlizAmount);
}

char* copy_char_string(char* destin, char* string, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    destin[index] = string[index];
  }
  return destin;
}

bool alloc_strmat_column(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column)
{
  if(column < 0 || column >= width) return false;

  copy_string_matrix(result, strmat, height, width, length1);

  for(int index = 0; index < height; index += 1)
  {
    copy_char_string(result[index][column], strarr[index], length2);
  }
  return true;
}

bool float_vector_strarr(char** result, float* vector, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    sprintf(result[index], "%f", vector[index]);
  }
  return true;
}

bool float_matrix_strmat(char*** result, float** matrix, int height, int width)
{
  for(int index = 0; index < height; index += 1)
  {
    if(!float_vector_strarr(result[index], matrix[index], width)) return false;
  }
  return true;
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

  
  free_float_vector(vector, height - 1);


  alloc_strmat_column(result, strmat, height, width, length, strarr, length, headerIndex);

  
  free_string_array(strarr, height, length);

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

bool extract_file_lines(char** fileLines, int* amount, FILE* filePointer)
{
  char buffer[256]; int index = 0;

  for(index = 0; !feof(filePointer); index += 1)
  {
    if(fgets(buffer, sizeof(buffer), filePointer) == NULL) break;

    sscanf(buffer, "%[^\n]%*c", fileLines[index]);
  }
  *amount = index; return true;
}

bool extract_text_file(char** fileLines, int* amount, const char filePath[])
{
  FILE* filePointer = fopen(filePath, "r");

  if(filePointer == NULL) return false;

  bool result = extract_file_lines(fileLines, amount, filePointer);

  fclose(filePointer); return result;
}

char** create_string_array(int amount, int length)
{
  char** strArray = malloc(sizeof(char*) * amount);

  for(int index = 0; index < amount; index += 1)
  {
    strArray[index] = malloc(sizeof(char) * length);

    memset(strArray[index], '\0', sizeof(char) * length);
  }
  return strArray;
}

char*** create_string_matrix(int height, int width, int length)
{
  char*** strMatrix = malloc(sizeof(char**) * height);

  for(int index = 0; index < height; index += 1)
  {
    strMatrix[index] = create_string_array(width, length);
  }
  return strMatrix;
}

void free_string_array(char** strArray, int amount, int length)
{
  for(int index = 0; index < amount; index += 1) 
  {
    free(strArray[index]);
  }
  free(strArray);
}

void free_string_matrix(char*** strMatrix, int height, int width, int length)
{
  for(int index = 0; index < height; index += 1)
  {
    free_string_array(strMatrix[index], width, length);
  }
  free(strMatrix);
}

int trim_string_spaces(char* result, const char string[], int length)
{
  int start = 0;
  while(isspace(string[start]) && start < length) start += 1;

  int stop = length - 1;
  while(isspace(string[stop]) && stop > start) stop -= 1;

  int newLength = (stop - start + 1);

  for(int index = 0; index < newLength; index += 1)
  {
    result[index] = string[index + start];
  }
  result[newLength] = '\0'; return newLength;
 }

int split_string_tokens(char** tokens, int* length, const char string[], const char delim[])
{
  char strCopy[256]; strcpy(strCopy, string);

  char* tempToken = strtok(strCopy, delim);

  int amount;

  for(amount = 0; tempToken != NULL; amount += 1)
  {
    trim_string_spaces(tokens[amount], tempToken, strlen(tempToken));

    int strLength = strlen(tokens[amount]) + 1;

    if(strLength > *length) *length = strLength;

    tempToken = strtok(NULL, delim);
  }
  return amount;
}

void string_array_tokens(char*** tokens, int* width, int* length, char** strArray, int strAmount, const char delim[])
{
  *width = 0; *length = 0;

  for(int index = 0; index < strAmount; index += 1)
  {
    int tempAmount = split_string_tokens(tokens[index], length, strArray[index], delim);

    if(tempAmount > *width) *width = tempAmount;
  }
}

bool strarr_float_vector(float* vector, char** strarr, int amount)
{
  for(int index = 0; index < amount; index += 1)
  {
    sscanf(strarr[index], "%f", &vector[index]);
  }
  return true;
}

bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width)
{
  for(int index = 0; index < height; index += 1)
  {
    if(!strarr_float_vector(matrix[index], strmat[index], width)) return false;
  }
  return true;
}

bool strmat_index_filter(char*** result, char*** strmat, int height, int width, int length, const int indexis[], int amount)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int index = 0; index < amount; index += 1)
    {
      int wIndex = indexis[index];

      if(wIndex < 0 || wIndex >= width) return false;

      copy_char_string(result[hIndex][index], strmat[hIndex][wIndex], length);
    }
  }
  return true;
}

bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column)
{
  if(column < 0 || column >= width) return false;
 
  for(int index = 0; index < height; index += 1)
  {
    copy_char_string(strarr[index], strmat[index][column], length);
  }
  return true;
}

char** copy_string_array(char** destin, char** strarr, int amount, int length)
{
  for(int index = 0; index < amount; index += 1)
  {
    copy_char_string(destin[index], strarr[index], length);
  }
  return destin;
}

char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length)
{
  for(int index = 0; index < height; index += 1)
  {
    copy_string_array(destin[index], strmat[index], width, length);
  }
  return destin;
}

int strmat_header_index(char*** strmat, int height, int width, const char header[])
{
  if(height < 1) return -1;

  for(int index = 0; index < width; index += 1)
  {
    if(!strcmp(strmat[0][index], header)) return index;
  }
  return -1;
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

  free_string_matrix(tempStrmat, height, width, length);


  free_string_matrix(addStrmat, height, singleAmount, length);

  free_string_matrix(newStrmat, height - 1, singleAmount, length);

  free_string_array(singleStrarr, height - 1, length);

  free_string_array(columnStrarr, height, length);

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

char*** duplic_string_matrix(char*** strmat, int height, int width, int length)
{
  char*** duplic = create_string_matrix(height, width, length);

  return copy_string_matrix(duplic, strmat, height, width, length);
}

char*** remove_strmat_column(char*** result, char*** strmat, int height, int width, int length, int column)
{
  int rWidthIndex = 0;

  for(int wIndex = 0; wIndex < width; wIndex += 1)
  {
    if(wIndex == column) continue;

    for(int hIndex = 0; hIndex < height; hIndex += 1)
    {
      copy_char_string(result[hIndex][rWidthIndex], strmat[hIndex][wIndex], length);
    }
    rWidthIndex += 1;
  }
  return result;
}

int strarr_single_strings(char** result, char** strarr, int amount1, int length)
{
  int amount2 = 0;

  for(int index1 = 0; index1 < amount1; index1 += 1)
  {
    bool exists = false;

    for(int index2 = 0; index2 < amount2; index2 += 1)
    {
      if(!strcmp(strarr[index1], result[index2]))
      {
        exists = true; break;
      }
    }

    if(!exists)
    {
      copy_char_string(result[amount2], strarr[index1], length);
      amount2 += 1;
    }
  }
  return amount2;
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

char*** merge_strmat_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width1; wIndex += 1)
    {
      copy_char_string(result[hIndex][wIndex], strmat1[hIndex][wIndex], length1);
    }
    for(int wIndex = 0; wIndex < width2; wIndex += 1)
    {
      copy_char_string(result[hIndex][wIndex + width1], strmat2[hIndex][wIndex], length2);
    }
  }
  return result;
}

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount)
{
  char*** inputTokens = create_string_matrix(height, width, length);
  char*** targetTokens = create_string_matrix(height, width, length);

  if(!strmat_index_filter(inputTokens, tokens, height, width, length, inputIndexis, inputAmount));
  if(!strmat_index_filter(targetTokens, tokens, height, width, length, targetIndexis, targetAmount));

  strmat_float_matrix(inputs, inputTokens, height, inputAmount);
  strmat_float_matrix(targets, targetTokens, height, targetAmount);

  free_string_matrix(inputTokens, height, width, length);
  free_string_matrix(targetTokens, height, width, length);

  return true;
}

bool text_file_tokens_t(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[], char** strArray)
{
  if(!extract_text_file(strArray, height, filePath)) return false;

  string_array_tokens(tokens, width, length, strArray, *height, delim);

  return true;
}

bool text_file_tokens(char*** tokens, int* height, int* width, int* length, const char filePath[], const char delim[])
{
  char** strArray = create_string_array(256, 256);

  bool result = text_file_tokens_t(tokens, height, width, length, filePath, delim, strArray);

  free_string_array(strArray, 256, 256); return result;
}

bool csv_indexis_inptrgs_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens)
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

bool csv_indexis_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_indexis_inptrgs_t(inputs, targets, height, inputIndexis, inputAmount, targetIndexis, targetAmount, filePath, tokens);

  free_string_matrix(tokens, 100, 10, 10); return result;
}

bool csv_headers_inptrgs_t(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens)
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

  if(!strarr_strarr_indexis(inputIndexis, tokens[0], tWidth, inputHeaders, inputAmount))
  {
    free(inputIndexis); free(targetIndexis); return false;
  }

  if(!strarr_strarr_indexis(targetIndexis, tokens[0], tWidth, targetHeaders, targetAmount))
  {
    free(inputIndexis); free(targetIndexis); return false;
  }

  bool result = tokens_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, tLength, inputIndexis, inputAmount, targetIndexis, targetAmount);

  free(inputIndexis);
  free(targetIndexis);

  return result;
}

bool strarr_strarr_indexis(int* indexis, char* strarr1[], int amount1, char* strarr2[], int amount2)
{
  for(int index2 = 0; index2 < amount2; index2 += 1)
  {
    bool exists = false;

    for(int index1 = 0; index1 < amount1; index1 += 1)
    {
      if(!strcmp(strarr1[index1], strarr2[index2]))
      {
        indexis[index2] = index1; exists = true;
      }
    }
    if(!exists) return false;
  }
  return true;
}

bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_headers_inptrgs_t(inputs, targets, height, inputHeaders, inputAmount, targetHeaders, targetAmount, filePath, tokens);

  free_string_matrix(tokens, 100, 10, 10); return result;
}
