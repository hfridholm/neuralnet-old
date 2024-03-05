#include "../secure.h"

bool float_matrix_filter_index(float** result, float** matrix, int height, int width, const int indexes[], int amount)
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

bool float_matrix_column_vector(float* vector, float** matrix, int height, int width, int column)
{
  if(vector == NULL || matrix == NULL) return false;

  if(column < 0 || column >= width) return false;

  for(int index = 0; index < height; index += 1)
  {
    vector[index] = matrix[index][column];
  }
  return true;
}

float** float_matrix_create(int height, int width)
{
  if(height < 0 || width < 0) return NULL;

  float** matrix = malloc(sizeof(float*) * height);

  if(matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    matrix[hIndex] = float_vector_create(width);
  }
  return matrix;
}

void float_matrix_free(float*** matrix, int height, int width)
{
  if(*matrix == NULL) return;

  for(int index = 0; index < height; index += 1)
  {
    float_vector_free((*matrix) + index, width);
  }
  free(*matrix);
  *matrix = NULL;
}

float** float_matrix_random_create(int height, int width, float minimum, float maximum)
{
  float** matrix = float_matrix_create(height, width);

  return float_matrix_random_fill(matrix, height, width, minimum, maximum);
}

float** float_matrix_random_fill(float** matrix, int height, int width, float minimum, float maximum)
{
  if(matrix == NULL) return NULL;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    float_vector_random_fill(matrix[hIndex], width, minimum, maximum);
  }
  return matrix;
}

float** float_matrix_transp(float** transp, float** matrix, int height, int width)
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

float** float_matrix_scale_multi(float** result, float** matrix, int height, int width, float scalor)
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

float** float_matrix_scale_addit(float** result, float** matrix, int height, int width, float scalor)
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

float** float_matrix_elem_multi(float** result, float** matrix1, float** matrix2, int height, int width)
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

float** float_matrix_elem_addit(float** result, float** matrix1, float** matrix2, int height, int width)
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

float** float_matrix_vector_addit(float** result, float** matrix, float* vector, int height, int width)
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

bool float_matrix_dotprod(float** result, float** matrix1, int height1, int width1, float** matrix2, int height2, int width2)
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

bool float_matrix_vector_dotprod(float* result, float** matrix, int height, int width, float* vector, int length)
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

float** float_vector_cnvrt_matrix(float** matrix, float* vector, int length)
{
  if(matrix == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    matrix[index][0] = vector[index];
  }
  return matrix;
}

float** float_matrix_cnvrt_vector(float* vector, float** matrix, int height, int width)
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

float** float_matrix_duplic(float** matrix, int height, int width)
{
  if(matrix == NULL) return NULL;

  float** duplic = float_matrix_create(height, width);

  return float_matrix_copy(duplic, matrix, height, width);
}

float** float_matrix_copy(float** destin, float** matrix, int height, int width)
{
  if(destin == NULL || matrix == NULL) return NULL;

  for(int index = 0; index < height; index += 1)
  {
    float_vector_copy(destin[index], matrix[index], width);
  }
  return destin;
}

bool float_matrix_print(float** matrix, int height, int width)
{
  if(matrix == NULL) return false;

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    float_vector_print(matrix[hIndex], width);
  }
  return true;
}
