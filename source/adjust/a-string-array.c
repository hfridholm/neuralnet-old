#include "../adjust.h"

char** strarr_create(int amount, int length)
{
  if(amount < 0 || length < 0) return NULL;
 
  char** strarr = malloc(sizeof(char*) * amount);

  if(strarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    strarr[index] = string_create(length); 
  }
  return strarr;
}

void strarr_free(char*** strarr, int amount, int length)
{
  if(*strarr == NULL) return;

  for(int index = 0; index < amount; index += 1) 
  {
    string_free((*strarr) + index, length);
  }
  free(*strarr);
  *strarr = NULL;
}

char** strarr_copy(char** destin, char** strarr, int amount, int length)
{
  if(destin == NULL || strarr == NULL) return NULL;
 
  for(int index = 0; index < amount; index += 1)
  {
    string_copy(destin[index], strarr[index], length);
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

int strarr_unique_strings(char** result, char** strarr, int amount1, int length)
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
      string_copy(result[amount2], strarr[index1], length);
      amount2 += 1;
    }
  }
  return amount2;
}

void strarr_split_tokens(char*** tokens, int* width, int* length, char** strarr, int amount, const char delim[])
{
  //if(tokens == NULL || width == NULL || length == NULL || strarr == NULL || delim == NULL);

  *width = 0; *length = 0;

  for(int index = 0; index < amount; index += 1)
  {
    int tempAmount = string_split_tokens(tokens[index], length, strarr[index], delim);

    if(tempAmount > *width) *width = tempAmount;
  }
}
