#include "../secure.h"

int create_random_integ(int minimum, int maximum)
{
  float fraction = ((float) rand() / (float) RAND_MAX);

  return (fraction * (maximum - minimum) + minimum);
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
