#include "../secure.h"

bool matrix_index_filter(float** result, float** matrix, int height, int width, const int indexes[], int amount)
{
  if(result == NULL || matrix == NULL || indexes == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    int wIndex = indexes[index];

    if(wIndex < 0 || wIndex >= width) return false;

    for(int hIndex = 0; hIndex < height; hIndex += 1)
    {
      result[hIndex][index] = matrix[hIndex][wIndex];
    }
  }
  return true;
}

bool matrix_column_vector(float* vector, float** matrix, int height, int width, int column)
{
  if(vector == NULL || matrix == NULL) return false;

  if(column < 0 || column >= width) return false;

  for(int index = 0; index < height; index += 1)
  {
    vector[index] = matrix[index][column];
  }
  return true;
}

float** create_float_matrix(int height, int width)
{
  if(height < 0 || width < 0) return NULL;

  float** matrix = malloc(sizeof(float*) * height);

  if(matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    matrix[hIndex] = create_float_vector(width);
  }
  return matrix;
}

void free_float_matrix(float*** matrix, int height, int width)
{
  if(*matrix == NULL) return;

  for(int index = 0; index < height; index += 1)
  {
    free_float_vector((*matrix) + index, width);
  }
  free(*matrix);
  *matrix = NULL;
}

float** create_random_fmatrix(int height, int width, float minimum, float maximum)
{
  float** matrix = create_float_matrix(height, width);

  return fill_fmatrix_random(matrix, height, width, minimum, maximum);
}

float** fill_fmatrix_random(float** matrix, int height, int width, float minimum, float maximum)
{
  if(matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    fill_fvector_random(matrix[hIndex], width, minimum, maximum);
  }
  return matrix;
}

float** transp_float_matrix(float** transp, float** matrix, int height, int width)
{
  if(transp == NULL || matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      transp[wIndex][hIndex] = matrix[hIndex][wIndex];
    }
  }
  return transp;
}

float** multi_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor)
{
  if(result == NULL || matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix[hIndex][wIndex] * scalor);
    }
  }
  return result;
}

float** addit_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor)
{
  if(result == NULL || matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix[hIndex][wIndex] + scalor);
    }
  }
  return result;
}

float** multi_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width)
{
  if(result == NULL || matrix1 == NULL || matrix2 == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix1[hIndex][wIndex] * matrix2[hIndex][wIndex]);
    }
  }
  return result;
}

float** addit_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width)
{
  if(result == NULL || matrix1 == NULL || matrix2 == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix1[hIndex][wIndex] + matrix2[hIndex][wIndex]);
    }
  }
  return result;
}

float** addit_fmatrix_vector(float** result, float** matrix, float* vector, int height, int width)
{
  if(result == NULL || matrix == NULL || vector == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix[hIndex][wIndex] + vector[wIndex]);
    }
  }
  return result;
}

bool dotprod_float_matrix(float** result, float** matrix1, int height1, int width1, float** matrix2, int height2, int width2)
{
  if(result == NULL || matrix1 == NULL || matrix2 == NULL) return false;

  if(width1 != height2) return false;

  for(int hIndex = 0; hIndex < height1; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width2; wIndex += 1)
    {
      for(int index = 0; index < width1; index += 1)
      {
        result[hIndex][wIndex] += (matrix1[hIndex][index] * matrix2[index][wIndex]);
      }
    }
  }
  return true;
}

bool dotprod_fmatrix_vector(float* result, float** matrix, int height, int width, float* vector, int length)
{
  if(result == NULL || matrix == NULL || vector == NULL) return false;
 
  if(width != length) return false;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex] += (matrix[hIndex][wIndex] * vector[wIndex]);
    }
  }
  return true;
}

float** cnvrt_fvector_fmatrix(float** matrix, float* vector, int length)
{
  if(matrix == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    matrix[index][0] = vector[index];
  }
  return matrix;
}

float** cnvrt_fmatrix_fvector(float* vector, float** matrix, int height, int width)
{
  if(vector == NULL || matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      vector[hIndex * width + wIndex] = matrix[hIndex][wIndex];
    }
  }
  return matrix;
}

float** fmatrix_elem_action(float** result, float** matrix, int height, int width, float (*float_action_funct)(float))
{
  if(result == NULL || matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = float_action_funct(matrix[hIndex][wIndex]);
    }
  }
  return result;
}

float** duplic_float_matrix(float** matrix, int height, int width)
{
  if(matrix == NULL) return NULL;

  float** duplic = create_float_matrix(height, width);

  return copy_float_matrix(duplic, matrix, height, width);
}

float** copy_float_matrix(float** destin, float** matrix, int height, int width)
{
  if(destin == NULL || matrix == NULL) return NULL;

  for(int index = 0; index < height; index += 1)
  {
    copy_float_vector(destin[index], matrix[index], width);
  }
  return destin;
}

bool print_float_matrix(float** matrix, int height, int width)
{
  if(matrix == NULL) return false;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    if(!print_float_vector(matrix[hIndex], width)) return false;
  }
  return true;
}
