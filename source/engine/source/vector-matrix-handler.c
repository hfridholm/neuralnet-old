#include "../engine.h"

bool float_vector_minmax(float* minValue, float* maxValue, float* vector, int length)
{
  if(length <= 0) return false;

  *minValue = vector[0]; *maxValue = vector[0];

  for(int index = 1; index < length; index += 1)
  {
    if(vector[index] > *maxValue) *maxValue = vector[index];

    if(vector[index] < *minValue) *minValue = vector[index];
  }
  return true;
}

float create_random_float(float minimum, float maximum)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (maximum - minimum) + minimum);
}

int create_random_integ(int minimum, int maximum)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (maximum - minimum) + minimum);
}

float* create_float_vector(int length)
{
  if(length < 0) return NULL;

  float* vector = malloc(sizeof(float) * length);

  if(vector == NULL) return NULL;

  memset(vector, 0.0f, sizeof(float) * length);

  return vector;
}

int* create_integ_array(int length)
{
  if(length < 0) return NULL;

  int* array = malloc(sizeof(int) * length);

  if(array == NULL) return NULL;

  memset(array, 0, sizeof(int) * length);

  return array;
}

void free_integ_array(int** array, int length)
{
  free(*array);
  *array = NULL;
}

int* random_indexes_array(int* array, int length)
{
  if(array == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    array[index] = index;
  }
  return shuffle_integ_array(array, length);
}

static int* switch_array_ints(int* array, int index1, int index2)
{
  int temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;

  return array; 
}

int* shuffle_integ_array(int* array, int length)
{
  if(array == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    int randIndex = create_random_integ(0, length - 1);

    switch_array_ints(array, index, randIndex);
  }
  return array;
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

float*** create_fmatrix_array(int amount, int height, int width)
{
  if(amount < 0 || height < 0 || width < 0) return NULL;
 
  float*** matarr = malloc(sizeof(float**) * amount);

  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    matarr[index] = create_float_matrix(height, width);
  }
  return matarr;
}

void free_float_vector(float** vector, int length)
{
  free(*vector);
  *vector = NULL;
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

void free_fmatrix_array(float**** matarr, int amount, int height, int width)
{
  if(*matarr == NULL) return;

  for(int index = 0; index < amount; index += 1)
  {
    free_float_matrix((*matarr) + index, height, width);
  }
  free(*matarr);
  *matarr = NULL;
}

float*** fill_fmatarr_random(float*** matarr, int amount, int height, int width, float minimum, float maximum)
{
  if(matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    fill_fmatrix_random(matarr[index], height, width, minimum, maximum);
  }
  return matarr;
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

float* fill_fvector_random(float* vector, int length, float minimum, float maximum)
{
  if(vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    vector[index] = create_random_float(minimum, maximum);
  }
  return vector;
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

float* multi_scale_fvector(float* result, float* vector, int length, float scalor)
{
  if(result == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector[index] * scalor);
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

float* multi_elem_fvector(float* result, float* vector1, float* vector2, int length)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] * vector2[index]);
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

float* addit_elem_fvector(float* result, float* vector1, float* vector2, int length)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] + vector2[index]);
  }
  return result;
}

float*** addit_elem_fmatarr(float*** result, float*** matarr1, float*** matarr2, int amount, int height, int width)
{
  if(result == NULL || matarr1 == NULL || matarr2 == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    addit_elem_fmatrix(result[index], matarr1[index], matarr2[index], height, width);
  }
  return result;
}

float*** multi_scale_fmatarr(float*** result, float*** matarr, int amount, int height, int width, float scalor)
{
  if(result == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    multi_scale_fmatrix(result[index], matarr[index], height, width, scalor);
  }
  return result;
}

float** addit_fmatrix_rvect(float** result, float** matrix, float* vector, int height, int width)
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

float** dotprod_float_vector(float** result, float* vector1, int length1, float* vector2, int length2)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

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

float* fvector_elem_action(float* result, float* vector, int length, float (*float_action_funct)(float))
{
  if(result == NULL || vector == NULL) return NULL;
 
  for(int index = 0; index < length; index += 1)
  {
    result[index] = float_action_funct(vector[index]);
  }
  return result;
}

float* duplic_float_vector(float* vector, int length)
{
  if(vector == NULL) return NULL;

  float* duplic = create_float_vector(length);

  return copy_float_vector(duplic, vector, length);
}

float** duplic_float_matrix(float** matrix, int height, int width)
{
  if(matrix == NULL) return NULL;

  float** duplic = create_float_matrix(height, width);

  return copy_float_matrix(duplic, matrix, height, width);
}

float*** copy_fmatrix_array(float*** destin, float*** matarr, int amount, int height, int width)
{
  if(destin == NULL || matarr == NULL) return NULL;

  for(int index = 0; index < amount; index += 1)
  {
    copy_float_matrix(destin[index], matarr[index], height, width);
  }
  return destin;
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

float* copy_float_vector(float* destin, float* vector, int length)
{
  if(destin == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    destin[index] = vector[index];
  }
  return destin;
}

float vector_maximum_float(float* vector, int length)
{
  if(vector == NULL) return 0;

  float maxValue = 0;

  for(int index = 0; index < length; index += 1)
  {
    if(vector[index] > maxValue) maxValue = vector[index];
  }
  return maxValue;
}

float float_vector_total(float* vector, int length)
{
  if(vector == NULL) return 0;

  float vecTotal = 0;

  for(int index = 0; index < length; index += 1)
  {
    vecTotal += vector[index];
  }
  return vecTotal;
}

bool print_fmatrix_array(float*** matarr, int amount, int height, int width)
{
  if(matarr == NULL) return false;

  for(int index = 0; index < amount; index += 1)
  {
    if(!print_float_matrix(matarr[index], height, width)) return false;

    printf("\n");
  }
  return true;
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

bool print_float_vector(float* vector, int length)
{
  if(vector == NULL) return false;

  for(int index = 0; index < length; index += 1)
  {
    printf("%+04.8f ", vector[index]);
  }
  printf("\n");
  return true;
}
