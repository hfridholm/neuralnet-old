#include "../header/engine-include-header.h"

float create_random_float(float minimum, float maximum)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (maximum - minimum) + minimum);
}

float* create_float_vector(int length)
{
  float* vector = malloc(sizeof(float) * length);

  for(int index = 0; index < length; index += 1)
  {
    vector[index] = 0.0f;
  }
  return vector;
}

float** create_float_matrix(int height, int width)
{
  float** matrix = malloc(sizeof(float*) * height);

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    matrix[hIndex] = create_float_vector(width);
  }
  return matrix;
}

float*** create_fmatrix_array(int amount, int height, int width)
{
  float*** matrixArray = malloc(sizeof(float**) * amount);

  for(int index = 0; index < amount; index += 1)
  {
    matrixArray[index] = create_float_matrix(height, width);
  }
  return matrixArray;
}

void free_float_vector(float* vector, int length) {free(vector);}

void free_float_matrix(float** matrix, int height, int width)
{
  for(int index = 0; index < height; index += 1)
  {
    free(matrix[index]);
  }
  free(matrix);
}

void free_fmatrix_array(float*** matrixArray, int amount, int height, int width)
{
  for(int index = 0; index < amount; index += 1)
  {
    free_float_matrix(matrixArray[index], height, width);
  }
  free(matrixArray);
}

float*** fill_fmatarr_random(float*** matrixArray, int amount, int height, int width, float minimum, float maximum)
{
  for(int index = 0; index < amount; index += 1)
  {
    fill_fmatrix_random(matrixArray[index], height, width, minimum, maximum);
  }
  return matrixArray;
}

float** fill_fmatrix_random(float** matrix, int height, int width, float minimum, float maximum)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    fill_fvector_random(matrix[hIndex], width, minimum, maximum);
  }
  return matrix;
}

float* fill_fvector_random(float* vector, int length, float minimum, float maximum)
{
  for(int index = 0; index < length; index += 1)
  {
    vector[index] = create_random_float(minimum, maximum);
  }
  return vector;
}

float** transp_float_matrix(float** transp, float** matrix, int height, int width)
{
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
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix[hIndex][wIndex] * scalor);
    }
  }
  return result;
}

float* multi_scale_fvector(float* result, float* vector, int length, float scalor)
{
  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector[index] * scalor);
  }
  return result;
}

float** addit_scale_fmatrix(float** result, float** matrix, int height, int width, float scalor)
{
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
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix1[hIndex][wIndex] * matrix2[hIndex][wIndex]);
    }
  }
  return result;
}

float* multi_elem_fvector(float* result, float* vector1, float* vector2, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] * vector2[index]);
  }
  return result;
}

float** addit_elem_fmatrix(float** result, float** matrix1, float** matrix2, int height, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = (matrix1[hIndex][wIndex] + matrix2[hIndex][wIndex]);
    }
  }
  return result;
}

float* addit_elem_fvector(float* result, float* vector1, float* vector2, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] + vector2[index]);
  }
  return result;
}

float*** addit_elem_fmatarr(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width)
{
  for(int index = 0; index < amount; index += 1)
  {
    addit_elem_fmatrix(result[index], matarr1[index], matarr2[index], height, width);
  }
  return result;
}

float*** multi_scale_fmatarr(float*** result, float*** matarr, int amount, int height, int width, float scalor)
{
  for(int index = 0; index < amount; index += 1)
  {
    multi_scale_fmatrix(result[index], matarr[index], height, width, scalor);
  }
  return result;
}

float** addit_fmatrix_rvect(float** result, float** matrix, float* vector, int height, int width)
{
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

float** dotprod_float_vector(float** result, float* vector1, int length1, float* vector2, int length2)
{
  for(int hIndex = 0; hIndex < length1; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < length2; wIndex += 1)
    {
      result[hIndex][wIndex] = (vector1[hIndex] * vector2[wIndex]);
    }
  }
  return result;
}

float** cnvrt_fvector_fmatrix(float** matrix, float* vector, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    matrix[index][0] = vector[index];
  }
  return matrix;
}

float** cnvrt_fmatrix_fvector(float* vector, float** matrix, int height, int width)
{
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
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      result[hIndex][wIndex] = float_action_funct(matrix[hIndex][wIndex]);
    }
  }
  return result;
}

float* fvector_elem_action(float* result, float* vector, int length, float (*float_action_funct)(float))
{
  for(int index = 0; index < length; index += 1)
  {
    result[index] = float_action_funct(vector[index]);
  }
  return result;
}

float* duplic_float_vector(float* vector, int length)
{
  float* duplic = create_float_vector(length);

  return copy_float_vector(duplic, vector, length);
}

float** duplic_float_matrix(float** matrix, int height, int width)
{
  float** duplic = create_float_matrix(height, width);

  return copy_float_matrix(duplic, matrix, height, width);
}

float** copy_float_matrix(float** destin, float** matrix, int height, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      destin[hIndex][wIndex] = matrix[hIndex][wIndex];
    }
  }
  return destin;
}

float* copy_float_vector(float* destin, float* vector, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    destin[index] = vector[index];
  }
  return destin;
}

float vector_maximum_float(float* vector, int length)
{
  float maxValue = 0;

  for(int index = 0; index < length; index += 1)
  {
    if(vector[index] > maxValue) maxValue = vector[index];
  }
  return maxValue;
}

float float_vector_total(float* vector, int length)
{
  float vecTotal = 0;

  for(int index = 0; index < length; index += 1)
  {
    vecTotal += vector[index];
  }
  return vecTotal;
}

void print_fmatrix_array(float*** matrixArray, int amount, int height, int width)
{
  for(int index = 0; index < amount; index += 1)
  {
    print_float_matrix(matrixArray[index], height, width);
  
    printf("\n");
  }
}

void print_float_matrix(float** matrix, int height, int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    print_float_vector(matrix[hIndex], width);
  }
}

void print_float_vector(float* vector, int length)
{
  for(int index = 0; index < length; index += 1)
  {
    printf("%+04.8f ", vector[index]);
  }
  printf("\n");
}