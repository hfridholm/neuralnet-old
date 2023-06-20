#include "../adjust.h"

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

char*** copy_string_matrix(char*** destin, char*** strmat, int height, int width, int length)
{
  if(destin == NULL || strmat == NULL) return NULL;

  for(int index = 0; index < height; index += 1)
  {
    copy_string_array(destin[index], strmat[index], width, length);
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

bool float_matrix_strmat(char*** result, float** matrix, int height, int width)
{
  if(result == NULL || matrix == NULL) return false;

  for(int index = 0; index < height; index += 1)
  {
    if(!float_vector_strarr(result[index], matrix[index], width)) return false;
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

bool strmat_index_filter(char*** result, char*** strmat, int height, int width, int length, const int indexes[], int amount)
{
  if(result == NULL || strmat == NULL || indexes == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    int wIndex = indexes[index];

    if(wIndex < 0 || wIndex >= width) return false;

    for(int hIndex = 0; hIndex < height; hIndex += 1)
    {
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
