#include "../secure.h"

bool float_vector_minmax(float* minimum, float* maximum, float* vector, int length)
{
  if(length <= 0) return false;

  *minimum = vector[0]; *maximum = vector[0];

  for(int index = 1; index < length; index += 1)
  {
    if(vector[index] > *maximum) *maximum = vector[index];

    if(vector[index] < *minimum) *minimum = vector[index];
  }
  return true;
}

float float_random_create(float minimum, float maximum)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (maximum - minimum) + minimum);
}

float* float_vector_create(int length)
{
  if(length < 0) return NULL;

  float* vector = malloc(sizeof(float) * length);

  if(vector == NULL) return NULL;

  memset(vector, 0.0f, sizeof(float) * length);

  return vector;
}

void float_vector_free(float** vector, int length)
{
  free(*vector);
  *vector = NULL;
}

float* float_vector_random_fill(float* vector, int length, float minimum, float maximum)
{
  if(vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    vector[index] = float_random_create(minimum, maximum);
  }
  return vector;
}

float* float_vector_scale_multi(float* result, float* vector, int length, float scalor)
{
  if(result == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector[index] * scalor);
  }
  return result;
}

float* float_vector_elem_multi(float* result, float* vector1, float* vector2, int length)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] * vector2[index]);
  }
  return result;
}

float* float_vector_elem_addit(float* result, float* vector1, float* vector2, int length)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] + vector2[index]);
  }
  return result;
}

float** float_vector_dotprod(float** result, float* vector1, int length1, float* vector2, int length2)
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

float* float_vector_duplic(float* vector, int length)
{
  if(vector == NULL) return NULL;

  float* duplic = float_vector_create(length);

  return float_vector_copy(duplic, vector, length);
}

float* float_vector_copy(float* destin, float* vector, int length)
{
  if(destin == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    destin[index] = vector[index];
  }
  return destin;
}

float float_vector_maximum(float* vector, int length)
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

bool float_vector_print(float* vector, int length)
{
  if(vector == NULL) return false;

  for(int index = 0; index < length; index += 1)
  {
    printf("%+04.8f ", vector[index]);
  }
  printf("\n");
  return true;
}
