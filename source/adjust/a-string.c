#include "../adjust.h"

char* create_char_string(int length)
{
  if(length < 0) return NULL;

  char* string = malloc(sizeof(char) * length);

  if(string == NULL) return NULL;

  memset(string, '\0', sizeof(char) * length);

  return string;
}

void free_char_string(char** string, int length)
{
  free(*string);
  *string = NULL;
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
