#include "../secure.h"

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

float* create_float_vector(int length)
{
  if(length < 0) return NULL;

  float* vector = malloc(sizeof(float) * length);

  if(vector == NULL) return NULL;

  memset(vector, 0.0f, sizeof(float) * length);

  return vector;
}

void free_float_vector(float** vector, int length)
{
  free(*vector);
  *vector = NULL;
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

float* multi_scale_fvector(float* result, float* vector, int length, float scalor)
{
  if(result == NULL || vector == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector[index] * scalor);
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

float* addit_elem_fvector(float* result, float* vector1, float* vector2, int length)
{
  if(result == NULL || vector1 == NULL || vector2 == NULL) return NULL;

  for(int index = 0; index < length; index += 1)
  {
    result[index] = (vector1[index] + vector2[index]);
  }
  return result;
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
