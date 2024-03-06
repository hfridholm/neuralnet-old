#include "../persue.h"

/*
 * Read the lines of the inputted stream
 *
 * RETURN
 * - int amount | The amount of read lines
static int stream_lines_read(char (*lines)[256], FILE* stream)
{
  char buffer[256];
  int index = 0;

  for(index = 0; !feof(stream); index++)
  {
    if(fgets(buffer, sizeof(buffer), stream) == NULL) break;

    memset(lines[index], '\0', sizeof(lines[index]));

    sscanf(buffer, "%[^\n]%*c", lines[index]);
  }
  return index;
}
*/

/*
 * Read the lines of the inputted filepath
 *
 * RETURN
 * - SUCCESS | The amount of read lines
 * - ERROR   | -1
static int filepath_lines_read(char (*lines)[256], const char* filepath)
{
  if(lines == NULL  || filepath == NULL) return -1;

  FILE* stream = fopen(filepath, "r");

  if(stream == NULL) return -1;

  int amount = stream_lines_read(lines, stream);

  fclose(stream);

  return amount;
}
*/

/*
 * Fix: Change to returning status codes
 *
 * RETURN
 * - 0 | Success!
 * - 1 | Failed to read filepath lines
bool fpath_tokens(char*** tokens, int* height, int* width, int* length, const char filepath[], const char delim[])
{
  char strarr[256][256];

  int lines = filepath_lines_read(strarr, filepath);

  if(lines < 0) return false; // 1

  *height = lines;

  int status = strarr_split_tokens(tokens, width, length, (char**) strarr, *height, delim);

  return (status == 0) ? true : false; // 0
}
*/
/*

bool datset_header_nrmliz(char*** result, char*** strmat, int height, int width, int length, const char header[])
{
  int headerIndex = strmat_header_index(strmat, height, width, header);

  if(headerIndex < 0) return false;  

  char** strarr = strarr_create(height, length);

  strmat_column_strarr(strarr, strmat, height, width, length, headerIndex);

  float* vector = float_vector_create(height - 1);

  strarr_float_vector(vector, strarr + 1, height - 1);


  float minValue, maxValue;

  float_vector_minmax(&minValue, &maxValue, vector, height - 1);
  
  for(int index = 0; index < height - 1; index += 1)
  {
    vector[index] = (vector[index] - minValue) / (maxValue - minValue);
  }

  float_vector_strarr(strarr + 1, vector, height - 1);

  
  float_vector_free(&vector, height - 1);


  strmat_column_alloc(result, strmat, height, width, length, strarr, length, headerIndex);

  
  strarr_free(&strarr, height, length);

  return true;
}

bool datset_headers_nrmliz(char*** result, char*** strmat, int height, int width, int length, char* headers[], int amount)
{
  if(amount <= 0) return false;

  datset_header_nrmliz(result, strmat, height, width, length, headers[0]);

  for(int index = 1; index < amount; index += 1)
  {
    datset_header_nrmliz(result, result, height, width, length, headers[index]);
  }
  return true;
}

bool strarrs_onehot_matrix(char*** result, char** strarr1, int height, char** strarr2, int width)
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

bool datset_header_onehot(char*** result, int* newWidth, char*** strmat, int height, int width, int length, const char header[])
{
  int headerIndex = strmat_header_index(strmat, height, width, header);

  if(headerIndex < 0) return false;


  char** columnStrarr = strarr_create(height, length); 

  strmat_column_strarr(columnStrarr, strmat + 1, height - 1, width, length, headerIndex);


  char** singleStrarr = strarr_create(height - 1, length);

  int singleAmount = strarr_unique_strings(singleStrarr, columnStrarr, height - 1, length);

  
  char*** newStrmat = strmat_create(height - 1, singleAmount, length);

  strarrs_onehot_matrix(newStrmat, columnStrarr, height - 1, singleStrarr, singleAmount);


  char*** addStrmat = strmat_create(height, singleAmount, length);

  strarr_copy(addStrmat[0], singleStrarr, singleAmount, length);
  
  strmat_copy(addStrmat + 1, newStrmat, height - 1, singleAmount, length);

  *newWidth = width - 1 + singleAmount;


  char*** tempStrmat = strmat_create(height, width, length);

  strmat_column_remove(tempStrmat, strmat, height, width, length, headerIndex); 

  strmats_add_columns(result, tempStrmat, height, width - 1, length, addStrmat, singleAmount, length);

  strmat_free(&tempStrmat, height, width, length);


  strmat_free(&addStrmat, height, singleAmount, length);

  strmat_free(&newStrmat, height - 1, singleAmount, length);

  strarr_free(&singleStrarr, height - 1, length);

  strarr_free(&columnStrarr, height, length);

  return true;
}

bool datset_headers_onehot(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* headers[], int amount)
{
  if(amount <= 0) return false;

  if(!datset_header_onehot(result, newWidth, strmat, height, width, length, headers[0])) return false; 

  for(int index = 1; index < amount; index += 1)
  {
    //char*** strmatCopy = strmat_duplic(result, height, *newWidth, 10);

    if(!datset_header_onehot(result, newWidth, result, height, *newWidth, length, headers[index])) return false; 

    //strmat_free(strmatCopy, height, *newWidth, 10);
  }
  return true;
}

bool datset_indexes_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount)
{
  char*** inputTokens = strmat_create(height, width, length);
  char*** targetTokens = strmat_create(height, width, length);

  if(!strmat_filter_index(inputTokens, tokens, height, width, length, inputIndexis, inputAmount));
  if(!strmat_filter_index(targetTokens, tokens, height, width, length, targetIndexis, targetAmount));

  strmat_float_matrix(inputs, inputTokens, height, inputAmount);
  strmat_float_matrix(targets, targetTokens, height, targetAmount);

  strmat_free(&inputTokens, height, width, length);
  strmat_free(&targetTokens, height, width, length);

  return true;
}

bool datset_headers_inpts_trgts(float** inputs, float** targets, char*** tokens, int height, int width, int length, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount)
{
  int* inputIndexis = malloc(sizeof(int) * targetAmount);
  int* targetIndexis = malloc(sizeof(int) * targetAmount);

  if(!strarr_strarr_indexes(inputIndexis, tokens[0], width, inputHeaders, inputAmount))
  {
    index_array_free(&inputIndexis, inputAmount);
    index_array_free(&targetIndexis, targetAmount);
    return false;
  }

  if(!strarr_strarr_indexes(targetIndexis, tokens[0], width, targetHeaders, targetAmount))
  {
    index_array_free(&inputIndexis, inputAmount);
    index_array_free(&targetIndexis, targetAmount);
    return false;
  }

  bool result = datset_indexes_inpts_trgts(inputs, targets, tokens + 1, height - 1, width, length, inputIndexis, inputAmount, targetIndexis, targetAmount);

  index_array_free(&inputIndexis, inputAmount);
  index_array_free(&targetIndexis, targetAmount);

  return result;
}

static bool fpath_indexes_inpts_trgts_body(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!fpath_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) return false;

  *height = tHeight - 1;

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }
  return datset_indexes_inpts_trgts(inputs, targets, tokens + 1, tHeight - 1, tWidth, tLength, inputIndexis, inputAmount, targetIndexis, targetAmount);
}

bool fpath_indexes_inpts_trgts(float** inputs, float** targets, int* height, const int inputIndexis[], int inputAmount, const int targetIndexis[], int targetAmount, const char filePath[])
{
  char*** tokens = strmat_create(100, 10, 10);

  bool result = fpath_indexes_inpts_trgts_body(inputs, targets, height, inputIndexis, inputAmount, targetIndexis, targetAmount, filePath, tokens);

  strmat_free(&tokens, 100, 10, 10); return result;
}

static bool fpath_headers_inpts_trgts_body(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[], char*** tokens)
{
  int tWidth = 0, tHeight = 0, tLength = 0;

  if(!fpath_tokens(tokens, &tHeight, &tWidth, &tLength, filePath, ",")) return false;

  *height = tHeight - 1;

  for(int hIndex = 0; hIndex < tHeight; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < tWidth; wIndex += 1)
    {
      if(wIndex == tWidth - 1) printf("%s\n", tokens[hIndex][wIndex]);
      else printf("%s | ", tokens[hIndex][wIndex]);
    }
  }
  return datset_headers_inpts_trgts(inputs, targets, tokens, tHeight, tWidth, tLength, inputHeaders, inputAmount, targetHeaders, targetAmount);
}

bool fpath_headers_inpts_trgts(float** inputs, float** targets, int* height, char* inputHeaders[], int inputAmount, char* targetHeaders[], int targetAmount, const char filePath[])
{
  char*** tokens = strmat_create(100, 10, 10);

  bool result = fpath_headers_inpts_trgts_body(inputs, targets, height, inputHeaders, inputAmount, targetHeaders, targetAmount, filePath, tokens);

  strmat_free(&tokens, 100, 10, 10); return result;
}

bool datset_headers_prepare(char*** result, int* newWidth, char*** strmat, int height, int width, int length, char* onehotHeaders[], int onehotAmount, char* nrmlizHeaders[], int nrmlizAmount)
{
  if(!datset_headers_onehot(result, newWidth, strmat, height, width, length, onehotHeaders, onehotAmount)) return false;

  return datset_headers_nrmliz(result, result, height, *newWidth, length, nrmlizHeaders, nrmlizAmount);
}
*/
