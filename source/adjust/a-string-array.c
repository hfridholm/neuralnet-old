#include "../adjust.h"

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

char** copy_string_array(char** destin, char** strarr, int amount, int length)
{
  if(destin == NULL || strarr == NULL) return NULL;
 
  for(int index = 0; index < amount; index += 1)
  {
    copy_char_string(destin[index], strarr[index], length);
  }
  return destin;
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

bool strarr_float_vector(float* vector, char** strarr, int amount)
{
  if(vector == NULL || strarr == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    sscanf(strarr[index], "%f", &vector[index]);
  }
  return true;
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
