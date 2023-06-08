#include "../dataset.h"

char* create_char_string(int length)
{
  if(length < 0) return NULL;

  char* string = malloc(sizeof(char) * length);

  if(string == NULL) return NULL;

  memset(string, '\0', sizeof(char) * length);

  return string;
}

char** create_string_array(int amount, int length)
{
  if(amount < 0 || length < 0) return NULL;
 
  char** strarr = malloc(sizeof(char*) * amount);

  if(strarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    strarr[index] = create_char_string(length); 
  }
  return strarr;
}

char*** create_string_matrix(int height, int width, int length)
{
  if(height < 0 || width < 0 || length < 0) return NULL;
  
  char*** strmat = malloc(sizeof(char**) * height);

  if(strmat == NULL) return NULL;

  for(int index = 0; index < height; index += 1)
  {
    strmat[index] = create_string_array(width, length);
  }
  return strmat;
}



void free_char_string(char** string, int length)
{
  free(*string);
  *string = NULL;
}

void free_string_array(char*** strarr, int amount, int length)
{
  if(*strarr == NULL) return;

  for(int index = 0; index < amount; index += 1) 
  {
    free_char_string((*strarr) + index, length);
  }
  free(*strarr);
  *strarr = NULL;
}

void free_string_matrix(char**** strmat, int height, int width, int length)
{
  if(*strmat == NULL) return;

  for(int index = 0; index < height; index += 1)
  {
    free_string_array((*strmat) + index, width, length);
  }
  free(*strmat);
  *strmat = NULL;
}



char** copy_string_array(char** destin, char** strarr, int amount, int length)
{
  if(destin == NULL || strarr == NULL) return NULL;
 
  for(int index = 0; index < amount; index += 1)
  {
    copy_char_string(destin[index], strarr[index], length);
  }
  return destin;
}

char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length)
{
  if(destin == NULL || strmat == NULL) return NULL;

  for(int index = 0; index < height; index += 1)
  {
    copy_string_array(destin[index], strmat[index], width, length);
  }
  return destin;
}

char* copy_char_string(char* destin, char* string, int length)
{
  if(destin == NULL || string == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    destin[index] = string[index];
  }
  return destin;
}



char*** duplic_string_matrix(char*** strmat, int height, int width, int length)
{
  if(strmat == NULL) return NULL;

  char*** duplic = create_string_matrix(height, width, length);

  return copy_string_matrix(duplic, strmat, height, width, length);
}



bool alloc_strmat_column(char*** result, char*** strmat, int height, int width, int length1, char** strarr, int length2, int column)
{
  if(result == NULL || strmat == NULL) return false;

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
  if(result == NULL || vector == NULL) return false;

  for(int index = 0; index < length; index += 1)
  {
    sprintf(result[index], "%f", vector[index]);
  }
  return true;
}

bool float_matrix_strmat(char*** result, float** matrix, int height, int width)
{
  if(result == NULL || matrix == NULL) return false;

  for(int index = 0; index < height; index += 1)
  {
    if(!float_vector_strarr(result[index], matrix[index], width)) return false;
  }
  return true;
}



bool strarr_float_vector(float* vector, char** strarr, int amount)
{
  if(vector == NULL || strarr == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    sscanf(strarr[index], "%f", &vector[index]);
  }
  return true;
}

bool strmat_float_matrix(float** matrix, char*** strmat, int height, int width)
{
  if(matrix == NULL || strmat == NULL) return false;

  for(int index = 0; index < height; index += 1)
  {
    if(!strarr_float_vector(matrix[index], strmat[index], width)) return false;
  }
  return true;
}



int trim_string_spaces(char* result, const char string[], int length)
{
  //if(result == NULL || string == NULL);

  int start = 0;
  while(isspace(string[start]) && start < length) start += 1;

  int stop = length - 1;
  while(isspace(string[stop]) && stop > start) stop -= 1;

  int newLength = (stop - start + 1);

  for(int index = 0; index < newLength; index += 1)
  {
    result[index] = string[index + start];
  }
  result[newLength] = '\0';
  return newLength;
}

bool strarr_strarr_indexes(int* indexes, char* strarr1[], int amount1, char* strarr2[], int amount2)
{
  //if(indexes == NULL || strarr1 == NULL || strarr2 == NULL);

  for(int index2 = 0; index2 < amount2; index2 += 1)
  {
    bool exists = false;

    for(int index1 = 0; index1 < amount1; index1 += 1)
    {
      if(!strcmp(strarr1[index1], strarr2[index2]))
      {
        indexes[index2] = index1; exists = true;
      }
    }
    if(!exists) return false;
  }
  return true;
}

char*** merge_strmat_columns(char*** result, char*** strmat1, int height, int width1, int length1, char*** strmat2, int width2, int length2)
{
  if(result == NULL || strmat1 == NULL || strmat2 == NULL) return NULL;
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

int strarr_single_strings(char** result, char** strarr, int amount1, int length)
{
  //if(result == NULL || strarr == NULL);

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

char*** remove_strmat_column(char*** result, char*** strmat, int height, int width, int length, int column)
{
  if(result == NULL || strmat == NULL) return NULL;

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



int strmat_header_index(char*** strmat, int height, int width, const char header[])
{
  if(strmat == NULL) return -1;

  if(height < 1) return -1;

  for(int index = 0; index < width; index += 1)
  {
    if(!strcmp(strmat[0][index], header)) return index;
  }
  return -1;
}

int split_string_tokens(char** tokens, int* length, const char string[], const char delim[])
{
  //if(tokens == NULL || length == NULL || string == NULL || delim == NULL);

  char strCopy[256];
  strcpy(strCopy, string);

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

void string_array_tokens(char*** tokens, int* width, int* length, char** strarr, int amount, const char delim[])
{
  //if(tokens == NULL || width == NULL || length == NULL || strarr == NULL || delim == NULL);

  *width = 0; *length = 0;

  for(int index = 0; index < amount; index += 1)
  {
    int tempAmount = split_string_tokens(tokens[index], length, strarr[index], delim);

    if(tempAmount > *width) *width = tempAmount;
  }
}



bool strmat_index_filter(char*** result, char*** strmat, int height, int width, int length, const int indexes[], int amount)
{
  if(result == NULL || strmat == NULL || indexes == NULL) return false;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int index = 0; index < amount; index += 1)
    {
      int wIndex = indexes[index];

      if(wIndex < 0 || wIndex >= width) return false;

      copy_char_string(result[hIndex][index], strmat[hIndex][wIndex], length);
    }
  }
  return true;
}

bool strmat_column_strarr(char** strarr, char*** strmat, int height, int width, int length, int column)
{
  if(strarr == NULL || strmat == NULL) return false;
 
  if(column < 0 || column >= width) return false;
 
  for(int index = 0; index < height; index += 1)
  {
    copy_char_string(strarr[index], strmat[index][column], length);
  }
  return true;
}
