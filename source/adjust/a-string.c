#include "../adjust.h"

/*
 * Create string allocated on the HEAP using malloc
 * Also clean the memory using memset
 *
 * RETURN
 * - SUCCESS | char* string
 * - ERROR   | NULL
 */
char* string_create(size_t length)
{
  char* string = malloc(sizeof(char) * length);

  if(string == NULL) return NULL;

  memset(string, '\0', sizeof(char) * length);

  return string;
}

/*
 * Free string from the HEAP using free
 * Also assigns NULL to pointer
 */
void string_free(char** string, size_t length)
{
  free(*string);

  *string = NULL;
}

/*
 * Copy string from source to destin using memmove
 *
 * RETURN
 * - SUCCESS | char* destin
 * - ERROR   | NULL
 */
char* string_copy(char* destin, const char* source, size_t length)
{
  if(destin == NULL || source == NULL) return NULL;

  return memmove(destin, source, sizeof(char) * length);
}

/*
 * Trip spaces from both the start and the end of the inputted string
 * The new length of the trimmed string is returned
 *
 * RETURN
 * - size_t newLength
 */
size_t string_trim_spaces(char* result, const char* string, size_t length)
{
  if(result == NULL || string == NULL) return length;

  size_t start = 0;
  while(isspace(string[start]) && start < length) start++;

  size_t stop = (length - 1);
  while(isspace(string[stop]) && stop > start) stop--;

  int newLength = (stop - start + 1);

  memmove(result, string + start, sizeof(char) * newLength);

  result[newLength] = '\0';

  return newLength;
}

/*
 * Split the inputted string with delim and then trim the tokens
 * If the user wants, he can pass a poitner to the max token length
 *
 * RETURN
 * - SUCCESS | size_t amount
 * - ERROR   | 0
 */
size_t string_split_tokens(char** tokens, size_t* length, const char* string, const char* delim)
{
  if(tokens == NULL || string == NULL || delim == NULL) return 0;

  char strCopy[256];

  strcpy(strCopy, string);

  char* token = strtok(strCopy, delim);

  size_t amount;

  for(amount = 0; token != NULL; amount++)
  {
    size_t strLength = string_trim_spaces(tokens[amount], token, strlen(token));

    // Only assign the max length if it is wanted (not NULL)
    if(length != NULL && strLength > *length) *length = strLength;

    token = strtok(NULL, delim);
  }
  return amount;
}
