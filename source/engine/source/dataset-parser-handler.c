#include "../header/engine-include-header.h"

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

int split_string_tokens(char** tokens, const char string[], const char delim[])
{
  char strCopy[256]; strcpy(strCopy, string);

  char* tempToken = strtok(strCopy, delim);

  int amount;

  for(amount = 0; tempToken != NULL; amount += 1)
  {
    trim_string_spaces(tokens[amount], tempToken, strlen(tempToken));

    tempToken = strtok(NULL, delim);
  }
  return amount;
}

int string_array_tokens(char*** tokens, char** strArray, int strAmount, const char delim[])
{
  int tokenAmount = 0;

  for(int index = 0; index < strAmount; index += 1)
  {
    int tempAmount = split_string_tokens(tokens[index], strArray[index], delim);

    if(tempAmount > tokenAmount) tokenAmount = tempAmount;
  }
  return tokenAmount;
}

float** tokens_float_matrix(float** matrix, char*** tokens, int height, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      sscanf(tokens[hIndex][wIndex], "%f", &matrix[hIndex][wIndex]);
    }
  }
  return matrix;
}

bool strmat_index_filter(char*** result, char*** strMatrix, int height, int width, const int indexis[], int amount)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int index = 0; index < amount; index += 1)
    {
      int wIndex = indexis[index];

      if(wIndex >= width) return false;

      strcpy(result[hIndex][index], strMatrix[hIndex][wIndex]);
    }
  }
  return true;
}

bool tokens_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount)
{
  char*** inputTokens = create_string_matrix(height, width, 10);
  char*** targetTokens = create_string_matrix(height, width, 10);

  if(!strmat_index_filter(inputTokens, tokens, height, width, inputIndexis, inputAmount));
  if(!strmat_index_filter(targetTokens, tokens, height, width, targetIndexis, targetAmount));

  tokens_float_matrix(inputs, inputTokens, height, inputAmount);
  tokens_float_matrix(targets, targetTokens, height, targetAmount);

  free_string_matrix(inputTokens, height, width, 10);
  free_string_matrix(targetTokens, height, width, 10);

  return true;
}

bool text_file_tokens_t(char*** tokens, int* height, int* width, const char filePath[], const char delim[], char** strArray)
{
  if(!extract_text_file(strArray, height, filePath)) return false;

  *width = string_array_tokens(tokens, strArray, *height, delim);

  return true;
}

bool text_file_tokens(char*** tokens, int* height, int* width, const char filePath[], const char delim[])
{
  char** strArray = create_string_array(256, 256);

  bool result = text_file_tokens_t(tokens, height, width, filePath, delim, strArray);

  free_string_array(strArray, 256, 256); return result;
}

bool csv_indexis_inptrgs_t(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, filePath, ",")) return false;

  *height = tHeight - 1;

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }

  return tokens_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, inputIndexis, inputAmount, targetIndexis, targetAmount);
}

bool csv_indexis_inptrgs(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_indexis_inptrgs_t(inputs, targets, height, inputIndexis, inputAmount, targetIndexis, targetAmount, filePath, tokens);

  free_string_matrix(tokens, 100, 10, 10); return result;
}

bool csv_headers_inptrgs_t(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0;

  if(!text_file_tokens(tokens, &tHeight, &tWidth, filePath, ",")) return false;

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

  strarr_strarr_indexis(inputIndexis, tokens[0], tWidth, inputHeaders, inputAmount);
  strarr_strarr_indexis(targetIndexis, tokens[0], tWidth, targetHeaders, targetAmount);

  bool result = tokens_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, inputIndexis, inputAmount, targetIndexis, targetAmount);

  free(inputIndexis);
  free(targetIndexis);

  return result;
}

bool strarr_strarr_indexis(int* indexis, char* strarr1[], int amount1, char* strarr2[], int amount2)
{
  for(int index2 = 0; index2 < amount2; index2 += 1)
  {
    for(int index1 = 0; index1 < amount1; index1 += 1)
    {
      if(!strcmp(strarr1[index1], strarr2[index2]))
      {
        indexis[index2] = index1;
      }
    }
  }
  return true;
}

bool csv_headers_inptrgs(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[])
{
  char*** tokens = create_string_matrix(100, 10, 10);

  bool result = csv_headers_inptrgs_t(inputs, targets, height, inputHeaders, inputAmount, targetHeaders, targetAmount, filePath, tokens);

  free_string_matrix(tokens, 100, 10, 10); return result;
}
